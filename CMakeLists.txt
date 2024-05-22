cmake_minimum_required(VERSION 3.0)
project(FileManger2)


# поиск покетов ncurses
find_package(Curses REQUIRED)

# подключение заголовочных файлов
include_directories(include)

# Указание исходных файлов
set(SOURCE_FILES src/main.cpp)

# Поиск библеотек boost
find_package(Boost REQUIRED COMPONENTS filesystem)

# создание исп. файла 
add_executable(chad ${SOURCE_FILES})

# подключени библеотек
target_link_libraries(chad ${CURSES_LIBRARIES})

# подключени библеотек 2
target_include_directories(chad PRIVATE ${CURSES_INCLUDE_DIRS})

# подключени библеотек 3
target_link_libraries(chad Boost::filesystem)


