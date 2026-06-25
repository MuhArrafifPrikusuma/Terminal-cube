#include <string.h>
#include <ncurses.h>
#include <stdbool.h>
#include "gameOverScr.h"
#include "logicHandler/logic.h"

char *asciiArt[]= {
" ____    ____  ______    __    __          _______. __    __    ______  __  ___ ",
" \\   \\  /   / /  __  \\  |  |  |  |        /       ||  |  |  |  /      ||  |/  / ",
"  \\   \\/   / |  |  |  | |  |  |  |       |   (----`|  |  |  | |  ,----'|  '  /  ",
"   \\_    _/  |  |  |  | |  |  |  |        \\   \\    |  |  |  | |  |     |   <   ",
"     |  |    |  `--'  | |  `--'  |    .----)   |   |  `--'  | |  `----.|  . \\  ",
"     |__|     \\______/   \\______/     |_______/     \\______/   \\______||__\\__\\ "
};

char *choices[] = {
  "Restart", "Exit"
};

int choicesLen = sizeof(choices) / sizeof(char *);

static void print_menu(WINDOW* w, int hightlight);

void gameOver(int c, Player *p, Object *o){
  WINDOW *menu;
  int hightlight = 1;
  int choice = 0;
  int totalLines = 6;

  int x, y;

  getmaxyx(stdscr, y, x);
  
  int startX = (x /2), startY = (y / 2) ;
  for (int i = 0; i< totalLines; i++) {
    mvprintw((startY - (totalLines / 2) - 10)+ i, startX - 40, "%s", asciiArt[i]);
  }

  menu = newwin(5, 15, startY - 5, startX - 15);
  
  print_menu(menu,  hightlight);

  while (1) {
    c = wgetch(menu);
    switch (c) {
      case 'k':
      if(hightlight == 1)
        hightlight = choicesLen;
      else
       hightlight--;
      break;

      case 'j':
        if(hightlight == choicesLen)
          hightlight = 1;
        else
         hightlight++;
      break;

        case 10:
      choice = hightlight;
      break;
        default:
      break;

    }    
      print_menu(menu, hightlight);
      if(choice == 1){

      memset(p, 0, sizeof(Player));

      p->state.is_dead = false;
      p->height = 3;
      p->width = 5;
      p->velocity_y = 0;
      p->x = 10;
      p->state.is_grounded = true;
      p->win = newwin(p->height, p->width, (int)p->y, (int)p->x);

      for (int i = 0; i < 10; i++) {
      
      memset(&o[i], 0,  sizeof(Object));
      }

          break;
        } else if (choice == 2) {
      endwin();
        } 
  }
  refresh();

}

static void print_menu(WINDOW* w, int hightlight){
int i = 0;
  int x= 6 / 2 + 5;
  int y = 6 / 2 - choicesLen;

  for (i = 0; i < choicesLen; i++) {
    if(hightlight == i + 1){
      wattron(w, A_REVERSE);

      mvwprintw(w, y, x, "%s", choices[i]);
      wattroff(w, A_REVERSE);
    } else
      mvwprintw(w, y, x, "%s", choices[i]);
  
    y++;
  }
  wrefresh(w);
  refresh();
}
