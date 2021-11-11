#include "HitMonsterPrint.h"
HitMonsterPrint::HitMonsterPrint(OBJECT monster_size, int monster_health, int shot_limb) {
        if (monster_health <= 0) {
            std::cout << "The shot was fatal." << std::endl;
            std::cout << "Who would have thought that such a giant had a weak point?" << std::endl;
        }
        else {
            std::cout << "You hurt him! Keep it up!" << std::endl;
        }

        if (monster_size == MEDIUMMONSTER){
            switch (shot_limb) {
                case 0:
                case 1:
                    std::cout << "This hand is destroyed." << std::endl;
                    break;
                case 2:
                case 3:
                    std::cout << "This leg is destroyed." << std::endl;
                    break;
                case 4:
                    std::cout << "Chest is destroyed." << std::endl;
                    break;
            }
            std::cout << "Now it's useless to shoot at it." << std::endl;
        }
    }