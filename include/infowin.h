#ifndef _INFOWIN_H_
#define _INFOWIN_H_

#include <ncurses.h>

class InfoWin {
private:
  // getmaxyx(stdscr, y, x);
  WINDOW *infowin;
  int y, x;
  int win_width, win_height;
  int start_y;
  int start_x;

public:
  InfoWin() {
    getmaxyx(stdscr, y, x);
    win_height = y;
    win_width = x / 2;
    start_y = 0;
    start_x = x / 2;
  }

  void createWin() {
    infowin = newwin(win_height, win_width, start_y, start_x);
    wrefresh(infowin);
    refresh();
  }

  void setBox() {
    wborder(infowin, 0, 0, 0, 0, 0, 0, 0, 0);
    wrefresh(infowin);
    refresh();
  }
};

#endif // !_INFOWIN_H_
