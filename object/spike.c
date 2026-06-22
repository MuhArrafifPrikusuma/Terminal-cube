#include "spike.h"
#include <ncurses.h>

void drawSpike(Object *o) {
  int height = 4;

  for (int i = 1; i < height - 1; i++) {
    mvaddch(o->y + i, o->x - i, '/');
    mvaddch(o->y + i, o->x + i, '\\');
  }

  int base_y = o->y + height - 1;
  int left_x = o->x - height + 1;
  int right_x = o->x + height - 1;

  mvaddch(base_y, left_x, ACS_LLCORNER);
  mvaddch(base_y, right_x, ACS_LRCORNER);

  int base_length = (height * 2) - 3;

  mvhline(base_y, left_x, ACS_HLINE, base_length);
}

void spawnSpike(Object *o, int objectIndex) {
  int i = objectIndex;

  for (int j = 0; j < 1; j++) {

    o[i].y = 19;
    o[i].type = SPIKE;
  }
}
