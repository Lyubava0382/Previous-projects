
#include "fightView.h"
fightView::fightView(OBJECT monster_size, int hero_health, int monster_health) {
        switch (monster_size)
        {
            case SMALLMONSTER:
            case MEDIUMMONSTER:
                std::cout << "Before you is a Monster child." <<std::endl;
                std::cout << "Your HP:   " << hero_health << "\t\tHP of the monster:   " << monster_health << std::endl;
                std::cout << "Where to shoot?" <<std::endl;
                std::cout << "To the left hand: press 1" <<std::endl;
                std::cout << "To the right hand: press 2" <<std::endl;
                std::cout << "To the left leg: press 3" <<std::endl;
                std::cout << "To the right leg: press 4" <<std::endl;
                std::cout << "To the chest: press 5" <<std::endl;
                std::cout << "Escape: press 0" <<std::endl;
                std::cin >> wound;
                break;
            case LARGEMONSTER:
                std::cout << "Before you is a Big Monster." <<std::endl;
                std::cout << "Your HP:   " << hero_health << "\t\tHP of the monster:   " << monster_health << std::endl;
                std::cout << "Where to shoot?" <<std::endl;
                std::cout << "To the head: press 1" <<std::endl;
                std::cout << "To the heart: press 2" <<std::endl;
                std::cout << "Into the belly: press 3" <<std::endl;
                std::cout << "Escape: press 0" <<std::endl;
                std::cin >> wound;
                break;
        }
    }

    char fightView::GetWound() const {
        return this->wound;
    }