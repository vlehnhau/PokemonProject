cmake_minimum_required(VERSION 3.19)
project(klausur)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
include_directories(copyme/console-window-master)
set (CMAKE_PREFIX_PATH "~/Qt5.12.11/5.12.11/clang_64/lib/cmake")
find_package(Qt5Widgets REQUIRED)
add_executable(klausur
#        copyme/console-window-master/ConsoleDemo.cpp
#        copyme/console-window-master/ConsoleDemo.h
        copyme/console-window-master/ConsoleWindow.cpp
        copyme/console-window-master/ConsoleWindow.h
        gui/Gui.cpp
        gui/Gui.h
        Game/Game.cpp
        Game/Game.h
        Game/Player.cpp
        Game/Player.h
        main.cpp
#        copyme/console-window-master/main.cpp
        )
target_link_libraries(klausur Qt5::Widgets)
