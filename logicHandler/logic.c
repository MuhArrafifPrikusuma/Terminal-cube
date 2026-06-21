#include "logic.h"

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// TODO: tweak this later to make sure it feels just like the geoDash
// TODO: if a block is gone from view then NULL everything it has and also don't
// forget to make sure blocks doesn't spawn too close to each other
#define GRAVITY 0.12
#define JUMP_FORCE -1.5
#define FLOOR_Y 20
#define SCROLL_SPEED 0.4
#define MAX_O 10

// update player state and position
void updatePlayer(Player *p, int ch) {
  if (p->state.is_grounded &&
      (ch == ' ' || ch == 'k' || ch == 'w' || ch == 10)) {
    p->velocity_y = JUMP_FORCE;
    p->state.is_grounded = false;
  }

  if (!p->state.is_grounded)
    p->velocity_y += GRAVITY;
  else
    p->velocity_y = 0;

  p->y += p->velocity_y;

  if (p->y >= FLOOR_Y) {
    p->y = FLOOR_Y;
    p->velocity_y = 0;
    p->state.is_grounded = true;
  }
}

static void drawBlock(Object *o) {
  int ix = (int)o->x;
  int iy = (int)o->y;

  if (ix + o->width < 0 || ix > 90)
    return;

  mvhline(iy, ix + 1, ACS_HLINE, o->width - 2);
  mvhline(iy + o->height - 1, ix + 1, ACS_HLINE, o->width - 2);

  mvvline(iy + 1, ix, ACS_VLINE, o->height - 2);
  mvvline(iy + 1, ix + o->width - 1, ACS_VLINE, o->height - 2);

  mvaddch(iy, ix, ACS_ULCORNER);
  mvaddch(iy, ix + o->width - 1, ACS_URCORNER);
  mvaddch(iy + o->height - 1, ix, ACS_LLCORNER);
  mvaddch(iy + o->height - 1, ix + o->width - 1, ACS_LRCORNER);
}

static void spawnObj(Object *o) {
  srand(time(NULL));
  for (int i = 0; i < MAX_O; i++) {
    if (o[i].width == 0 || o[i].x < -5) {

      int type_roll = rand() % 4;
      o[i].x = 90;
      o[i].y = 20;
      switch (type_roll) {
      case 0:
        o[i].height = 3;
        o[i].width = 5;
        o[i].type = BLOCK;
        break;
      default:
        break;
      }
    }
  }
}

static void updateObj(Object *o) {
  for (int i = 0; i < MAX_O; i++) {
    if (o[i].width > 0) {
      o[i].x -= SCROLL_SPEED;
    }
  }
}

void handleObj(Object *o) {
  spawnObj(o);
  updateObj(o);

  for (int i = 0; i < MAX_O; i++) {
    if (o[i].width > 0) {
      switch ((int)o[i].type) {
      case BLOCK:
        drawBlock(&o[i]);
        break;
      default:
        o[i].width = 0;
        break;
      }
    }
  }
}

static bool checkCollision(Player *p, Object *o) {
  double pLeft = p->x;
  double pRight = p->x + p->width;
  double pTop = p->y;
  double pBot = p->y + p->height;

  double oLeft = o->x;
  double oRight = o->x + o->width;
  double oTop = o->y;
  double oBot = o->y + o->height;

  if (pRight <= oLeft || pLeft >= oRight || pBot <= oTop || pTop >= oBot) {
    return false;
  }
  return true;
}

void handleCollision(Player *p, Object *o) {
  bool found_Platform = false;

  if (p->y >= FLOOR_Y) {
    p->y = FLOOR_Y;
    p->velocity_y = 0;
    p->state.is_grounded = true;
    return;
  }

  for (int i = 0; i < MAX_O; i++) {
    if (o[i].width == 0 || o[i].x < -5)
      continue;
    double pRight = p->x + p->width;
    double prev_block_Left = o[i].x + SCROLL_SPEED;
    if (checkCollision(p, &o[i])) {
      // if (pRight > prev_block_Left && p->x < prev_block_Left) {
      //   p->state.is_dead = true;
      //   continue;
      // }
      double player_bottom = p->y + p->height;
      double previous_bottom_position = player_bottom - p->velocity_y;

      switch ((int)o[i].type) {
      case BLOCK:
        // FIX: make it so that it dies when it touches the side of a block
        // instead of just passing through and only died when you jump
        if (p->velocity_y >= 0 && previous_bottom_position <= o[i].y + 1) {
          p->y = o[i].y - p->height;

          p->velocity_y = 0;
          found_Platform = true;
        } else
          p->state.is_dead = true;
      }
    }
  }
  p->state.is_grounded = found_Platform;
}

// erase and redraw everything
void render(Player *p, Object *o) {
  erase();

  mvhline(22, 0, '-', 81);

  handleObj(o);

  mvwin(p->win, (int)p->y, p->x);

  box(p->win, 0, 0);
  refresh();
  wrefresh(p->win);
}
