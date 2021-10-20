#include "Mmonster.h"
    Mmonster::Mmonster(): health(3), attack(2), type(MEDIUMMONSTER), goon(true){
        for (int i = 0; i < 5; i++) {
            assailable[i] = 1;
        }
        assailable[rand() % 5] = 0;
        int random = rand() % 5;
        while (assailable[random] == 0){
            random = rand() % 5;
        }
        assailable[random] = 0;
    }
    void Mmonster::SetHealth(int a){
        this->health = a;
    }
    int Mmonster::GetHealth(){
        return this->health;
    }
    int Mmonster::GetAttack(){
        return this->attack;
    }
    OBJECT Mmonster::GetObject(){
        return this->type;
    }

    void Mmonster::fight(Player& hero){
        int body;
        while (health > 0 && goon){
            char wound;
            std::cout << "Before you is a Usual Monster." <<std::endl;
            std::cout << "Your HP:   " << hero.GetHealth() << "\t\tHP of the monster:   " << this->health << std::endl;
            std::cout << "Where to shoot?" <<std::endl;
            std::cout << "To the left hand: press 1" <<std::endl;
            std::cout << "To the right hand: press 2" <<std::endl;
            std::cout << "To the left leg: press 3" <<std::endl;
            std::cout << "To the right leg: press 4" <<std::endl;
            std::cout << "To the chest: press 5" <<std::endl;
            std::cout << "Escape: press 0" <<std::endl;
            std::cin >> wound;
            switch (wound) {
                case '0':
                    goon = false;
                    break;
                case '1':
                    body = 0;
                    break;
                case '2':
                    body = 1;
                    break;
                case '3':
                    body = 2;
                    break;
                case '4':
                    body = 3;
                    break;
                case '5':
                    body = 4;
                    break;
                default:
                    body = -1;
                    break;
            }
            if (goon && body >= 0 && assailable[body] == 1) {
                assailable[body] = 0;
                hit(hero);
                switch (body) {
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
            else {
                if (goon) miss(hero);
            }
        }
    }
    void Mmonster::hit(Player& hero){
        this->health = health - hero.GetAttack();

        if (health <= 0){
            goon = false;
            std::cout << "The shot was fatal." << std::endl;
            std::cout << "Who would have thought that such a giant had a weak point?" << std::endl;
            hero.SetCoins(1);
        }
    }
    void Mmonster::miss(Player& hero){
        std::cout << "You missed." <<std::endl;
        hero.SetHealth(hero.GetHealth() - attack);
        if (hero.GetHealth() < 0){
            goon = false;
            std::cout << "The enemy is stronger than you..." <<std::endl;
            //Game Over
        }
        else
            std::cout << "Try again." <<std::endl;
    }
