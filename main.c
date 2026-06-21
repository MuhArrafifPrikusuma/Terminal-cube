#include "logicHandler/logic.h"
#include "structure.h"
#include <ncurses.h>
#include <panel.h>
#include <stdbool.h>
#include <unistd.h>

#define FRAME_CAP 16667

int main(int argc, char *argv[]) {
  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  curs_set(0);

  Player player;
  player.x = 10.0;
  player.y = 20.0;
  player.height = 3;
  player.width = 5;
  player.velocity_y = 0;
  player.speed = 0.5;
  player.state.is_dead = false;
  player.state.is_grounded = true;

  player.win =
      newwin(player.height, player.width, (int)player.y, (int)player.x);

  Object object;
  object.width = 5;
  object.height = 3;

  while (!player.state.is_dead) {
    int ch = getch();

    updatePlayer(&player, ch);

    handleObj(&object);
    render(&player, &object);

    usleep(FRAME_CAP);
  }
  getch();
  endwin();
  return 0;
}
