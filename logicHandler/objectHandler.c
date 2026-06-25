#include "objectHandler.h"

static void space_between_object(Object *o, int i) { o[i + 1].x += o[i].width; }

void object_spawn_logic(Object *o) {

  for (int i = 0; i < MAX_O; i++) {
    if (o[i].x - o[i - 1].x < 10)
      space_between_object(o, i);

    if (o[i].width == 0 || o[i].x < -5) {

      if (rand() % 100 > 2) {
        return;
      }

      int type_roll = rand() % 4;
      o[i].x = 90;

      switch (type_roll) {
      case 0:
        spawnBlock(o, i);
        break;
      case 1:
        spawnSpike(o, i);
        break;
      case 2:
        break;
      default:
        o->width = 0;
        break;
      }
    }
  }
}
