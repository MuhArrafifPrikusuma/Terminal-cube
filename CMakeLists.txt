cmake_minimum_required(VERSION 3.15)
project(tuiDash LANGUAGES C)

set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)
# 1. Combine all source files into one executable (explicit absolute paths)
add_executable(tuiDash
    "${CMAKE_CURRENT_SOURCE_DIR}/main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/logicHandler/logic.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/object/mainObject.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/object/block.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/object/spike.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/gameOverScr.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/logicHandler/objectHandler.c"
)

# 2. Tell CMake precisely where to look for logic.h
target_include_directories(tuiDash PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/logicHandler")
target_include_directories(tuiDash PRIVATE ${CURSES_INCLUDE_DIRS})
# 4. Link the ncurses library to your executable
target_link_libraries(tuiDash PRIVATE ${CURSES_LIBRARIES})
