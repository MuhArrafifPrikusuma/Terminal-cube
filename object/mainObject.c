
#include "mainObject.h"
#include "../logicHandler/logic.h"
#include "spike.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

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
    found_Platform = true;
  }

  for (int i = 0; i < MAX_O; i++) {

    if (o[i].width == 0 || o[i].x < -5)
      continue;

    double player_bottom = p->y + p->height;
    double previous_bottom_position = player_bottom - p->velocity_y;

    if (checkCollision(p, &o[i])) {

      switch ((int)o[i].type) {
      case BLOCK:
        if (p->velocity_y >= 0 && previous_bottom_position <= o[i].y + 1) {
          p->y = o[i].y - p->height + 1;

          p->velocity_y = 0;
          found_Platform = true;
        } else
          p->state.is_dead = true;
        break;
      case SPIKE:
        p->state.is_dead = true;
      }
    }
  }
  p->state.is_grounded = found_Platform;
}

static void spawnObj(Object *o) {

  int isDouble = 0;
  int lastSpawn = 0;

  for (int i = 0; i < MAX_O; i++) {
    if (o[i].width == 0 || o[i].x < -5) {
      if (lastSpawn - isDouble < -9)
        return;
      if (rand() % 100 > 2) {
        isDouble++;
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
        break;
      }
    }
    lastSpawn = isDouble;
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
      case SPIKE:
        draw_spike(&o[i]);
        break;
      default:
        o[i].width = 0;
        break;
      }
    }
  }
}
