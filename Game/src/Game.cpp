//
// Created by Serg on 10.10.2022.
//
#include "Game.h"
Game::Game(){
    Player person;
    game_end = false;
    Field game1( 15, 10);
    game = game1;
    game_interface = GameView();
    Start(game);
}


void Game::Over(){
    game_end = true;
    time(&end);
    //Вывести конеч игры
    timeout = difftime(end,start);
}


void Game::Start(Field& game) {
    srand(time(NULL));
    game.MakeInOut();
    game.MakeObjects();
    person.SetLocal(game.GetIn().x,game.GetIn().y);
    person.SetCountKeys(game.MakeItems());
    game_interface.PrintMenu();
   FieldView(game, person).Print();
   time(&start);
    while(game_interface.Goon() && !game_end){
        Coordinates motion = game_interface.GameInput();
        if (motion.x == 0 && motion.y == 0) {
           Over();
            return;
        }
        if (GameMove(motion)) FieldView(game, person).Print();
    }
}


bool Game::GameMove(Coordinates motion) {
    if (game.WithinField({person.GetLocal().x + motion.x,person.GetLocal().y + motion.y}))
        person.SetLocal(person.GetLocal().x + motion.x,person.GetLocal().y + motion.y);
    switch (game.GetField()[person.GetLocal().y][person.GetLocal().x].GetType()) {
        case OUT: {
            if (person.Done()){
                Over();
                return false;
            }
            else ;//Вывести что не достаточчно ключей
        }
            break;
        case PASSABLE: {

            if (game.GetField()[person.GetLocal().y][person.GetLocal().x].GetObject() == BOX){
                if (game.GetField()[person.GetLocal().y][person.GetLocal().x].GetKey()){
                    person.Key();
                    //Вывести ключ есьт
                } else {
                   //Вывести тут нет ключа std::cout << "No!" << std::endl;
                }
                game.GetField()[person.GetLocal().y][person.GetLocal().x].SetObject(NONE);
            }

        }
            break;
    }
    return true;
}
