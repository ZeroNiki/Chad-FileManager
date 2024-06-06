# Chad File Manager
## About
lib:
  - [ncurses](https://invisible-island.net/ncurses/)
  - [boost](https://www.boost.org/)


Simple CLI file manager for Linux

### Warning
This project is unfinished

## Install (using cmake)
Install lib [ncurses](https://invisible-island.net/ncurses/) and [boost](https://www.boost.org/)

clone the repo:
```bash
git clone https://github.com/ZeroNiki/Chad-FileManage

cd Chad-FileManage
```

Create `build` dir:
```bash
mkdir build

cd build
```

Install:
```bash
cmake ..

cmake --build .
```

## Usage

```bash
./chad path/to/dir
```

