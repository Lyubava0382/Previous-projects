#include "Enemy.h"
void Enemy::fight(Player& hero){
        int body;
        while (health > 0 && goon){
            char shot = fightView(type, hero.GetHealth(), this->health).GetWound();
            switch (shot) {
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
            notify();
            if (goon && body >= 0 && assailable[body] == 1) {
                if (type == MEDIUMMONSTER) assailable[body] = 0;
                hit(hero);
                HitMonsterPrint(type, health, shot);
            }
            else {
                if (goon) miss(hero);
            }
        }
    }
    void Enemy::hit(Player& hero) {
        this->health = health - hero.GetAttack();
        if (health <= 0){
            goon = false;
            hero.SetCoins(reward);
        }
        notify();
    }
    void Enemy::miss(Player& hero){
        hero.SetHealth(hero.GetHealth() - attack);
        MissMonsterPrint(hero.GetHealth());
        if (hero.GetHealth() <= 0){
            goon = false;
            //Game Over
        }
        notify();
    }