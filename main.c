#include "gameOverScr.h"
#include "logicHandler/logic.h"
#include "object/mainObject.h"
#include "structure.h"
#include <locale.h>
#include <ncurses.h>
#include <panel.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define FRAME_CAP 16667

static void whenAlive(Player *p, Object *o);
static void whenDead(Player *p, Object *o);

int main(int argc, char *argv[]) {
  srand(time(NULL));

  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  curs_set(0);
  setlocale(LC_ALL, ""); // take host local unicode

  Player player;
  player.x = 10.0;
  player.height = 3;
  player.width = 5;
  player.velocity_y = 0;
  player.state.is_dead = false;
  player.state.is_grounded = true;

  player.win =
      newwin(player.height, player.width, (int)player.y, (int)player.x);

  Object object[10] = {0};

  while (1) {
    if (player.state.is_dead)
      erase();
    if (!player.state.is_dead)
      whenAlive(&player, object);
    else
      whenDead(&player, object);
  }

  delwin(player.win);
  erase();
  endwin();

  return 0;
}

static void whenAlive(Player *p, Object *o) {
  int ch = getch();

  updatePlayer(p, ch);

  handleCollision(p, o);
  handleObj(o);

  render(p, o);

  usleep(FRAME_CAP);
}
static void whenDead(Player *p, Object *o) {
  int ch = getch();

  gameOver(ch, p, o);
  refresh();
}
