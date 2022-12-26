
#include "MissMonsterPrint.h"
MissMonsterPrint::MissMonsterPrint(int hero_health) {
    std::cout << "You missed." <<std::endl;
    if (hero_health <= 0) {
        std::cout << "The enemy is stronger than you...\n" <<std::endl;
    }
    else {
        std::cout << "Try again.\n" <<std::endl;
    }
}