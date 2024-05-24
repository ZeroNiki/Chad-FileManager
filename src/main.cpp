#include "../include/infowin.h"
#include "../include/read.h"
#include "../include/readinfo.h"
#include "../include/win.h"

#include <boost/filesystem.hpp>
#include <iostream>
#include <locale.h>
#include <ncurses.h>

using namespace std;

int main(int argc, char **argv) {

  setlocale(LC_ALL, "");

  try {
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, true);

    InfoWin info;
    NcursesWindow filewin;

    FileRead read(filewin);
    ReadInfo readInfo(info);

    wstring startPath = L".";
    if (argc > 1) {
      startPath = read.from_utf8(argv[1]);
    }

    read.openDir(startPath);

    read.run();

    endwin();

  } catch (const exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    endwin();
  }

  return 0;
}
