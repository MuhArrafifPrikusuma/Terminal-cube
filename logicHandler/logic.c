#include "logic.h"
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// TODO: tweak this later to make sure it feels just like the geoDash
#define GRAVITY 0.15
#define JUMP_FORCE -1.2
#define FLOOR_Y 20
#define SCROLL_SPEED 0.1
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

  mvhline(iy, ix + 1, ACS_HLINE, 5);
  mvhline(iy + o->height - 1, ix + 1, ACS_HLINE, 5);

  mvvline(iy + 1, ix, ACS_VLINE, 3);
  mvvline(iy + 1, ix + o->width - 1, ACS_VLINE, 3);

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
        o->type = BLOCK;
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
  for (int i = 0; i < MAX_O; i++) {
    spawnObj(o);
    updateObj(o);
    if (o[i].width > 0) {
      switch ((int)o[i].type) {
      case 0:
        drawBlock(&o[i]);
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

  if (pRight <= oLeft || pLeft >= oLeft || pBot <= oTop || pTop >= oBot) {
    return false;
  }
  return true;
}

void handleCollision(Player *p, Object *o) {
  for (int i = 0; i < MAX_O; i++) {
    if (o[i].width == 0 || o[i].x < -5)
      continue;
    if (checkCollision(p, &o[i])) {
    }
  }
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
