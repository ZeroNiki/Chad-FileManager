#ifndef _WIN_H_
#define _WIN_H_

#include <ncurses.h>

class NcursesWindow {
public:
  NcursesWindow();
  void setBox();
  void print(int y, int x, const char *str, bool highlight = false,
             bool isfile = false);

  int getMaxLines() const {
    int y, x;
    getmaxyx(stdscr, y, x);
    return y - 2;
  }

  void refreshw();
  void clearw();
  void deleteWin();
  int getInput() const;

private:
  int y, x;
  WINDOW *filewin;
};

NcursesWindow::NcursesWindow() {
  getmaxyx(stdscr, y, x);

  filewin = newwin(y, x / 2, 0, 0);
  refresh();
}

void NcursesWindow::refreshw() { wrefresh(filewin); }
void NcursesWindow::clearw() { werase(filewin); }

void NcursesWindow::deleteWin() { endwin(); }

void NcursesWindow::setBox() {
  wborder(filewin, 0, 0, 0, 0, 0, 0, 0, 0);
  wrefresh(filewin);
}

void NcursesWindow::print(int yy, int xx, const char *str, bool highlight,
                          bool isfile) {

  start_color();
  use_default_colors();
  init_pair(1, COLOR_BLUE, -1);
  init_pair(2, COLOR_GREEN, -1);

  if (highlight) {
    wattron(filewin, A_STANDOUT);
  }

  if (isfile == false) {
    wattron(filewin, COLOR_PAIR(1));
    mvwprintw(filewin, yy, xx, "%s", str);
    wattroff(filewin, COLOR_PAIR(1));
  } else {
    wattron(filewin, COLOR_PAIR(2));
    mvwprintw(filewin, yy, xx, "%s", str);
    wattroff(filewin, COLOR_PAIR(2));
  }

  if (highlight) {
    wattroff(filewin, A_STANDOUT);
  }
  refreshw();
  refresh();
}

int NcursesWindow::getInput() const { return wgetch(filewin); }

#endif // !_WIN_H_
