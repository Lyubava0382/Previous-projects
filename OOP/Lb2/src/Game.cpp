#include "Game.h"
     Game::Game(){
        Player person;
        Field game( 15, 10);
        Start(game);
    }

    void Game::NextCondition(Cellule& locate, Field& game){
        int constant;
        constant = 3;
        GO array[4] = {RIGHT, DOWN, LEFT, UP};
        switch (locate.GetObject()) {
            case SMALLMONSTER: {
                switch (locate.GetStep()) {
                    case START:
                        for (int i = 0; i <= constant; i++) {
                            locate.SetStep(array[i]);
                            if (game.Access(locate.GetPoint()))
                                break;
                        }
                        if (!game.Access(locate.GetPoint()))
                            locate.SetStep(STOP);
                        break;
                    default:
                        do{
                            for (int i = 0; i <= constant; i++){
                                if (array[i] == locate.GetStep()){
                                    if (i  < constant) locate.SetStep(array[i+1]);
                                    else locate.SetStep(array[i-constant]);
                                    break;
                                }
                            }
                        } while (!game.Access(locate.GetPoint()));
                        break;
                }
            }
            case MEDIUMMONSTER:{
                switch (locate.GetStep()) {
                    case START:
                        for (int i = 0; i <= constant; i += 2) {
                            locate.SetStep(array[i]);
                            if (game.Access(locate.GetPoint()))
                                break;
                        }
                        if (!game.Access(locate.GetPoint()))
                            locate.SetStep(STOP);
                        break;
                    default:
                        if (!game.Access(locate.GetPoint())) {
                            if (locate.GetStep() == array[0])
                                locate.SetStep(array[2]);
                            else if (locate.GetStep() == array[2])
                                locate.SetStep(array[0]);
                        }
                        break;
                }
                break;
            }
            case LARGEMONSTER:{
                if (abs(person.GetLocal().x - locate.GetPoint().x) < abs(person.GetLocal().y - locate.GetPoint().y)){
                    if(person.GetLocal().y > locate.GetPoint().y) locate.SetStep(DOWN);
                    if(person.GetLocal().y < locate.GetPoint().y) locate.SetStep(UP);
                }
                else{
                    if(person.GetLocal().x > locate.GetPoint().x) locate.SetStep(RIGHT);
                    if(person.GetLocal().x < locate.GetPoint().x) locate.SetStep(LEFT);
                }
                if (!game.Access(locate.GetPoint()))
                    locate.SetStep(STOP);
                break;
            }
        }
    }

    void Game::Step(GO side, Coordinates begin, int k, Field& game){
        switch (side) {
            case RIGHT:
                game.GetMonsters()[k] = {begin.x + 1, begin.y};
                break;
            case LEFT:
                game.GetMonsters()[k] = {begin.x - 1, begin.y};
                break;
            case UP:
                game.GetMonsters()[k] = {begin.x, begin.y - 1};
                break;
            case DOWN:
                game.GetMonsters()[k] = {begin.x, begin.y + 1};
                break;
        }
        if (side != START && side != STOP){
            game.GetField()[ game.GetMonsters()[k].y][ game.GetMonsters()[k].x].SetObject(game.GetField()[begin.y][begin.x].GetObject());
            game.GetField()[ game.GetMonsters()[k].y][ game.GetMonsters()[k].x].SetStep(game.GetField()[begin.y][begin.x].GetStep());
            game.GetField()[begin.y][begin.x].SetStep(STOP);
            game.GetField()[begin.y][begin.x].SetObject(NONE);
        }
    }

    void Game::EnemyMove(Field& game)
    {
        for (int k = 0; k < game.GetMonsterCount(); k++) {
            NextCondition(game.GetField()[ game.GetMonsters()[k].y][ game.GetMonsters()[k].x], game);
            Step(game.GetField()[ game.GetMonsters()[k].y][ game.GetMonsters()[k].x].GetStep(),  game.GetMonsters()[k], k, game);
        }
    }

    void Game::GameMove(Field& game) {
        Coordinates back;
        EnemyMove(game);
        back = person.GetLocal();
        /*
         *
         */
        switch (game.GetField()[person.GetLocal().y][person.GetLocal().x].GetType()) {
            case NOPASS:
                person.SetLocal(back);
                break;
            case IN:
                person.SetLocal(back);
                break;
            case OUT:
                if (person.GetKey()) {
                    std::cout << "Congratulations! You completed the game" << std::endl;
                }
                else {
                    std::cout << "Oh no! The door is locked.\n";
                    std::cout << "Please get the key and come back here!" << std::endl;
                }
                break;
            case PASSABLE: {
                if (game.GetField()[person.GetLocal().y][person.GetLocal().x].GetObject() != NONE)
                    switch (game.GetField()[person.GetLocal().y][person.GetLocal().x].GetObject()) {
                        case BOX: {
                            Box keybox(game.GetField()[person.GetLocal().y][person.GetLocal().x].GetKey());
                            keybox.interplay(person);
                           if (keybox.GetOpen()){
                                game.GetField()[person.GetLocal().y][person.GetLocal().x].SetObject(NONE);
                                game.GetField()[person.GetLocal().y][person.GetLocal().x].SetKey(false);
                            }
			 break;
                        }
                        case FOOD: {
                            Heal healing;
                            healing.interplay(person);
                            game.GetField()[person.GetLocal().y][person.GetLocal().x].SetObject(NONE);
                            break;
                        }
                        case PORTAL: {
                            Teleport teleportation(game.GetTeleports());
                            teleportation.interplay(person);
                            break;
                        }
                        case SMALLMONSTER: {
                            Smonster enemy;
                            enemy.fight(person);
                            if(enemy.GetHealth() <= 0) {
                                game.GetField()[person.GetLocal().y][person.GetLocal().x].SetObject(NONE);
                            }
                            break;
                        }
                        case MEDIUMMONSTER: {
                            Mmonster enemy;
                            enemy.fight(person);
                            if(enemy.GetHealth() <= 0) {
                                game.GetField()[person.GetLocal().y][person.GetLocal().x].SetObject(NONE);
                            }
                            break;
                        }
                        case LARGEMONSTER: {
                            Lmonster enemy;
                            enemy.fight(person);
                            if(enemy.GetHealth() <= 0) {
                                game.GetField()[person.GetLocal().y][person.GetLocal().x].SetObject(NONE);
                            }
                            break;
                        }
                    }
            }
                break;
        }
    }

    void Game::Start(Field& game) {
        srand(time(NULL));
        game.MakeInOut();
        game.MakeObjects();
        person.SetLocal(game.GetIn());
        game.MakeItems();
        game.MakeEnemies();
        FieldView(game, person).Print();
        for (int k = 0; k < 3; k++){
            GameMove(game);
            FieldView(game, person).Print();
        }
    }
