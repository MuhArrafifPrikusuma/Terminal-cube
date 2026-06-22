#include "logic.h"

#include "../object/mainObject.h"
#include <ncurses.h>
#include <stdbool.h>
#include <unistd.h>

// TODO: tweak this later to make sure it feels just like the geoDash
// TODO: if a block is gone from view then NULL everything it has and also don't
// forget to make sure blocks doesn't spawn too close to each other
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
void render(Player *p, Object *o) {
  erase();

  mvhline(22, 0, '-', 81);

  handleObj(o);

  mvwin(p->win, (int)p->y, p->x);

  box(p->win, 0, 0);
  refresh();
  wrefresh(p->win);
}
