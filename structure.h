#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <ncurses.h>
#include <stdbool.h>

// will add game mode later right now only cube
typedef enum { MODE_CUBE, MODE_SHIP } GameModes;

typedef struct {
  bool is_dead;
  bool is_grounded;
} PlayerState;

typedef struct {
  double x;
  double y;

  // don't move player horizontally move the object instead
  double velocity_y;

  int width;
  int height;

  PlayerState state;
  WINDOW *win;
} Player;

typedef enum { BLOCK, SPIKE, PLATFORM } ObjectType;

typedef struct Object {
  double x;
  double y;

  int width;
  int height;

  ObjectType type;
} Object;

#endif // !
