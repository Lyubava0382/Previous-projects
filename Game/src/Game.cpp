
#include <fstream>
#include "Game.h"
Game::Game(){
    Player person;
    game_end = false;
    double cnt_w,itm_k,itm_b;
    int width, height;
    std::ifstream file("..\\src\\field.txt");
    if (file){
        file >> width;
        file >> height;
        file >> cnt_w;
        file >> itm_k;
        file >> itm_b;
        file.close();
    }
    Field game1( width, height, cnt_w,itm_k, itm_b);
    game = game1;
    game_interface = GameView();
    Start(game);
}


void Game::Over(bool breakEnd){
    game_end = true;
    time(&end);
    timeout = difftime(end,start);
    if (breakEnd);
        else game_interface.GameOver(timeout);
}


void Game::Start(Field& game) {
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
           Over(true);
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
                Over(false);
                return false;
            }
            else game_interface.NeedKey();
        }
            break;
        case PASSABLE: {

            if (game.GetField()[person.GetLocal().y][person.GetLocal().x].GetObject() == BOX){
                if (game.GetField()[person.GetLocal().y][person.GetLocal().x].GetKey()){
                    person.Key();
                    game_interface.Key(true);
                } else {
                    game_interface.Key(false);
                }
                game.GetField()[person.GetLocal().y][person.GetLocal().x].SetObject(NONE);
            }

        }
            break;
    }
    return true;
}
