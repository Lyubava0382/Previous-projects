//
// Created by Любава on 13.11.2021.
//

#include "ExitDoorPrint.h"
ExitDoorPrint::ExitDoorPrint(bool open){
        if (open) {
            std::cout << "Congratulations! You completed the game" << std::endl;
        }
        else {
            std::cout << "Oh no! The door is locked.\n";
            std::cout << "Please get the key and come back here!" << std::endl;
        }
    }
