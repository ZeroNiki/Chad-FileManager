#ifndef _READINFO_H_
#define _READINFO_H_

#include "infowin.h"

#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <vector>

class ReadInfo {
private:
  InfoWin &info;
  std::vector<std::string> lines;

  void displayInfo() {
    info.createWin();
    info.setBox();
    info.refreshw();

    for (int i = 0; i < lines.size(); ++i) {
      info.printInfo(i + 1, 1, lines[i].c_str());
    }

    info.refreshw();
  }

  void refreshI() { displayInfo(); }

public:
  ReadInfo(InfoWin &infowin) : info(infowin) { readUsageFile(); }

  void readUsageFile() {

    std::ifstream file("../usage.txt");
    std::string line;

    int longest = 0;

    while (std::getline(file, line)) {
      lines.push_back(line);
      if (line.length() > longest) {
        longest = line.length();
      }
    }

    refreshI();
  }

  void ref() { info.clearw(); }
};

#endif // !_READINFO_H_
