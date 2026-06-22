#include "block.h"

void drawBlock(Object *o) {
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

void spawnBlock(Object *o, int indexPosition) {
  int i = indexPosition;
  // generate how many times
  for (int j = 0; j < 1; j++) {
    int tmpHeight = 0;
    int tmpY = 0;

    // generate height
    for (int k = 0; k < (rand() % 2) + 1; k++) {
      tmpHeight += 3;
      if (k > 0)
        tmpY += 3;
    }
    o[i].y = 20 - tmpY;
    o[i].height = tmpHeight;
    o[i].width = 5;
    o[i].type = BLOCK;
  }
}
