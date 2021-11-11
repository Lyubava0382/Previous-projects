#include "MissMonsterPrint.h"
MissMonsterPrint(int hero_health) {
        std::cout << "You missed." <<std::endl;
        if (hero_health <= 0) {
            std::cout << "The enemy is stronger than you..." <<std::endl;
        }
        else {
            std::cout << "Try again." <<std::endl;
        }

    }