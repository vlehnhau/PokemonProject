cmake_minimum_required(VERSION 3.19)
project(klausur)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
include_directories(.)
set (CMAKE_PREFIX_PATH "~/Qt5.12.11/5.12.11/clang_64/lib/cmake")
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
add_executable(klausur
#        console-window-master/ConsoleDemo.cpp
#        console-window-master/ConsoleDemo.h
        console-window-master/ConsoleWindow.cpp
        console-window-master/ConsoleWindow.h
        gui/Gui.cpp
        gui/Gui.h
        Game/Game.cpp
        Game/Game.h
        Game/Player.cpp
        Game/Player.h
        Game/Monster.cpp
        Game/Monster.h
        main.cpp
#        console-window-master/main.cpp
        )
target_link_libraries(klausur Qt5::Widgets)
