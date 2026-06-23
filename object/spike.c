#include "spike.h"
#include <ncurses.h>

void drawSpike(Object *o) {
  int height = 4;

  int spawnPos = 19;
  for (int i = 1; i < height - 1; i++) {
    mvaddch(spawnPos + i, o->x - i, '/');
    mvaddch(spawnPos + i, o->x + i, '\\');
  }

  int base_y = spawnPos + height - 1;
  int left_x = o->x - height + 1;
  int right_x = o->x + height - 1;

  mvaddch(base_y, left_x, ACS_LLCORNER);
  mvaddch(base_y, right_x, ACS_LRCORNER);

  int base_length = (height * 2) - 3;

  mvhline(base_y, left_x, ACS_HLINE, base_length);
}

void spawnSpike(Object *o, int objectIndex) {
  int i = objectIndex;

  o[i].y = 22;
  o[i].height = 1;
  o[i].width = 2;
  o[i].type = SPIKE;
}
