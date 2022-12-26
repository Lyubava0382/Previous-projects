#include "Smonster.h"
    Smonster::Smonster(): health(5), attack(1), type(SMALLMONSTER), goon(true){
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
    void Smonster::SetHealth(int a){
        this->health = a;
    }
    int Smonster::GetHealth(){
        return this->health;
    }
    int Smonster::GetAttack(){
        return this->attack;
    }
    OBJECT Smonster::GetObject(){
        return this->type;
    }

    void Smonster::fight(Player& hero){
        int body;
        while (health > 0 && goon){
            char wound;
            std::cout << "Before you is a Monster child." <<std::endl;
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
                hit(hero);
            }
            else {
                if (goon) miss(hero);
            }
        }
    }

    void Smonster::hit(Player& hero) {
        this->health = health - hero.GetAttack();

        if (health <= 0){
            goon = false;
            std::cout << "The shot was fatal." << std::endl;
            std::cout << "Who would have thought that such a giant had a weak point?" << std::endl;
            hero.SetCoins(1);
        }
        else {
            std::cout << "You hurt him! Keep it up!" << std::endl;
        }
    }
    void Smonster::miss(Player& hero){
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
