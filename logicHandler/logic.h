#ifndef LOGIC_H
#define LOGIC_H

#include "../structure.h"

void updatePlayer(Player *p, int ch);
void render(Player *p, Object *o);
void handleObj(Object *o);
void handleCollision(Player *p, Object *o);
#endif // !LOGIC_HLOGIC_H
