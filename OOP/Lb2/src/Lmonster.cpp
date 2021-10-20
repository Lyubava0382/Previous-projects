#include "Lmonster.h"
    Lmonster::Lmonster(): health(100), attack(4),  type(LARGEMONSTER),
                goon(true){
        std::cout << health <<std::endl;
        for (int i = 0; i < 3; i++) {
            assailable[i] = 0;
        }
        assailable[rand() % 3] = 1;
    }
    void Lmonster::SetHealth(int a){
        this->health = a;
    }
    int Lmonster::GetHealth(){
        return this->health;
    }
    int Lmonster::GetAttack(){
        return this->attack;
    }
    OBJECT Lmonster::GetObject(){
        return this->type;
    }

    void Lmonster::fight(Player& hero){
        int body;
        while (health > 0 && goon){
            char wound;
            std::cout << "Before you is a Big Monster." <<std::endl;
            std::cout << "Your HP:   " << hero.GetHealth() << "\t\tHP of the monster:   " << this->health << std::endl;
            std::cout << "Where to shoot?" <<std::endl;
            std::cout << "To the head: press 1" <<std::endl;
            std::cout << "To the heart: press 2" <<std::endl;
            std::cout << "Into the belly: press 3" <<std::endl;
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

    void Lmonster::hit(Player& hero){
        this->health = 0;
        goon = false;
        std::cout << "The shot was fatal." << std::endl;
        std::cout << "Who would have thought that such a giant had a weak point?" << std::endl;
        hero.SetCoins(2);
    }
    void Lmonster::miss(Player& hero){
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
