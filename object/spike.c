#include "spike.h"
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <wchar.h>

// SP stands for sub pixels and RC is Row & Cols
#define CANVAS_SPR 80
#define CANVAS_SPC 160

bool pixel_grid[CANVAS_SPR][CANVAS_SPC];

static void set_pixel(int y, int x) { pixel_grid[y][x] = true; }

static void render_spike_to_canvas(int startX, int startY) {
  for (int y = 0; y < CANVAS_SPR; y += 4) {
    for (int x = 0; x < CANVAS_SPC; x += 2) {
      int braille_offset = 0;

      // check if set pixel is true on that position
      if (pixel_grid[y + 0][x + 0])
        braille_offset |= 0x01;

      if (pixel_grid[y + 1][x + 0])
        braille_offset |= 0x02;

      if (pixel_grid[y + 2][x + 0])
        braille_offset |= 0x04;

      if (pixel_grid[y + 0][x + 1])
        braille_offset |= 0x08;

      if (pixel_grid[y + 1][x + 1])
        braille_offset |= 0x10;

      if (pixel_grid[y + 2][x + 1])
        braille_offset |= 0x20;

      if (pixel_grid[y + 3][x + 0])
        braille_offset |= 0x40;

      if (pixel_grid[y + 3][x + 1])
        braille_offset |= 0x80;

      // wchar_t is for system characters
      if (braille_offset > 0) {
        /*
         * 0x2800 = 00101000000000 + braille_offset for example
         * 0x2800 + 0x18 = 00101000011010
         * check U+2800 https://unicode-explorer.com/b/2800 for example
         */
        wchar_t braille_char = 0x2800 + braille_offset;
        wchar_t wstr[2] = {braille_char, '\0'};
        mvaddwstr(startY + (y / 4), startX + (x / 2), wstr);
      }
    }
  }
}

void draw_spike(Object *o) {

  int spike_w = 10;
  int spike_h = 11;
  int midX = spike_w / 2;

  for (int y = 0; y < spike_h; y++) {
    double progress = (double)y / (spike_h - 1);
    int halfWidth = (int)(progress * midX);

    int leftBound = midX - halfWidth;
    int rightBound = midX + halfWidth;

    for (int x = leftBound; x <= rightBound; x++) {
      set_pixel(y, x);
    }
  }

  int screenPosX = (int)o->x;
  int screenPosY = 22 - (spike_h / 4);

  render_spike_to_canvas(screenPosX, screenPosY);
}

void spawnSpike(Object *o, int objectIndex) {
  int i = objectIndex;

  o[i].y = 22;
  o[i].height = 1;
  o[i].width = 2;
  o[i].type = SPIKE;
}
