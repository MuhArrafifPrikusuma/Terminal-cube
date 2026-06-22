#ifndef LOGIC_H
#define LOGIC_H
#define GRAVITY 0.12
#define JUMP_FORCE -1.5
#define FLOOR_Y 20
#define SCROLL_SPEED 0.5
#define MAX_O 10

#include "../structure.h"

void updatePlayer(Player *p, int ch);
void render(Player *p, Object *o);
#endif // !LOGIC_HLOGIC_H
