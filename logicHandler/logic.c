#include "logic.h"
#include <ncurses.h>
#include <stdbool.h>

// TODO: tweak this later to make sure it feels just like the geoDash
#define GRAVITY 0.15
#define JUMP_FORCE -1.2
#define FLOOR_Y 20

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

// erase and redraw everything
void render(Player *p) {
  erase();

  mvhline(22, 0, '-', 81);
  mvwin(p->win, (int)p->y, p->x);

  box(p->win, 0, 0);
  refresh();
  wrefresh(p->win);
}
