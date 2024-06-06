#ifndef _READ_H_
#define _READ_H_

#include "infowin.h"
#include "win.h"

#include <algorithm>
#include <boost/filesystem.hpp>
#include <boost/filesystem/directory.hpp>
#include <codecvt>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include <vector>

#include "readinfo.h"

class FileRead {
private:
  NcursesWindow &window;

  std::vector<std::string> files;
  int currentSelection;
  int scrolloffset;
  std::wstring currentPath;
  std::wstring prevPath;
  bool showHidden;

  // display files from vec files
  void displayFiles() {
    window.clearw();
    window.setBox();

    int maxLines = window.getMaxLines();

    for (int i = 0; i < maxLines && i + scrolloffset < files.size(); ++i) {
      int fileIndex = i + scrolloffset;

      std::string filename =
          boost::filesystem::path(files[fileIndex]).filename().string();

      if (boost::filesystem::is_directory(from_utf8(files[fileIndex]))) {
        filename += '/';

        window.print(i + 1, 1, filename.c_str(), fileIndex == currentSelection,
                     false);

      } else {
        window.print(i + 1, 1, filename.c_str(), fileIndex == currentSelection,
                     true);
      }

      window.refreshw();
    }
  }

  // redisplay files
  void refreshD() { displayFiles(); }

public:
  // init
  FileRead(NcursesWindow &win)
      : window(win), currentSelection(0), currentPath(L".") {
    openDir(currentPath);
  }

  // Movement
  void run() {
    int ch;

    while ((ch = window.getInput()) != 'q') {
      switch (ch) {
      case 'k': // UP
        if (currentSelection > 0) {
          --currentSelection;
          if (currentSelection < scrolloffset) {
            --scrolloffset;
            window.refreshw();
            refreshD();
          }
        }
        break;

      case 'j': // Down
        if (currentSelection < files.size() - 1) {
          ++currentSelection;
          if (currentSelection >= scrolloffset + window.getMaxLines()) {
            ++scrolloffset;
            window.refreshw();
            refreshD();
          }
        }
        break;

      case 'l': // open
        if (boost::filesystem::is_directory(
                from_utf8(files[currentSelection]))) {
          openDir(from_utf8(files[currentSelection]));
          window.refreshw();
          refreshD();
        }
        break;

      case 'h': // go back
        prevPath = currentPath + L"/../";
        openDir(prevPath);
        window.refreshw();
        refreshD();
        break;

      case 'c': // hidden files
        if (showHidden == true) {
          showHidden = false;
          openDir(currentPath);

        } else {
          showHidden = true;
          openDir(currentPath);
        }

        openDir(currentPath);
        break;

      case 't': // Usage
        break;

      default:
        break;
      }
      refreshD();
    }
  }

  // open dir
  void openDir(const std::wstring &path) {
    try {
      if (!boost::filesystem::exists(path)) {
        std::wcerr << L"Error: Path does not exist: " << path << std::endl;
        window.deleteWin();
        return;
      }

      if (!boost::filesystem::is_directory(path)) {
        std::wcerr << L"Error: Path is not a directory: " << path << std::endl;
        window.deleteWin();
        return;
      }

      files.clear();
      currentPath = path;
      boost::filesystem::directory_iterator end_itr;

      for (boost::filesystem::directory_iterator itr(path); itr != end_itr;
           ++itr) {
        std::wstring filename = itr->path().filename().wstring();
        if (!showHidden && filename[0] == L'.') {
          continue;
        }
        files.push_back(to_utf8(itr->path().wstring()));
      }

      currentSelection = 0;
      scrolloffset = 0;
      refreshD();

    } catch (const boost::filesystem::filesystem_error &ex) {
      std::wcerr << L"Filesystem error: " << ex.what() << std::endl;
    }
  }

  // convert from utf-8 to wstring
  std::wstring from_utf8(const std::string &str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return std::wstring(converter.from_bytes(str));
  }

  // convert to utf-8 from wstring
  std::string to_utf8(const std::wstring &str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(str);
  }
};
#endif // !_READ_H_
