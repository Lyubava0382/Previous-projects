cmake_minimum_required(VERSION 3.21)
project(untitled3)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled3 main.cpp src/Cellule.cpp src/Cellule.h src/structs.h src/Cell.h src/Field.cpp src/Field.h src/CelluleView.cpp src/CelluleView.h src/Player.cpp src/Player.h src/Characters.h src/Interior.h src/Game.cpp src/Game.h src/FieldView.cpp src/FieldView.h src/Item.h src/Box.cpp src/Box.h src/GameView.cpp src/GameView.h)
