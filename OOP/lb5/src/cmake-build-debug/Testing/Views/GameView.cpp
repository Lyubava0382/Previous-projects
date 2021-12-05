//
// Created by Любава on 05.12.2021.
//

#include "GameView.h"
GameView::GameView(){
    right = 'd';
    left ='a';
    up = 'w';
    down = 's';
    going = true;
}

void GameView::PrintMenu(){
    std::cout << "Hi, stranger... Welcome to the wonderful game\nRead this instruction carefully\n"<<
    "To read the detailed rules, click - [r]\n"
    "__________________________________________\n"
    "To move around the map, use these keys:\n"
    "Up - [w]\nLeft - [a]\nDown - [s]\nRight - [d]\n"
    "__________________________________________\n"
    "To exit the game, click - [x]\n"
    "To change the control keys, press - [k]\n"
    "To read the menu again, press - [m]\n";
    //GameInput();
}
Coordinates GameView::GameInput(){
char command = '0';
    std::cin >> command;
    if (command == right){
        return {1,0};
    }
    else if (command == left){
        return {-1,0};
    }
    else if (command == down){
        return {0,1};
    }
    else if (command == up){
        return {0,-1};
    }
    else if (command == 'x'){
        //Game over
        LeaveGame();
        going = false;
    }
    else if (command == 'm'){
        PrintMenu();
        return GameInput();
    }
    else if (command == 'k'){
        ChangeControlKeys();
        std::cout << "Now go on!\n";
        return GameInput();
    }
    else std::cout << "Didn't they teach you how to follow the rules?\n";
    return {0,0};
}

void GameView::ChangeControlKeys(){

    std::cout << "Enter the key to step [up]:\n";
    std::cin >> up;
    std::cout << "Enter the key for the step to the [right]\n";
    std::cin >> right;
    std::cout << "Enter the key to step [down]:\n";
    std::cin >> down;
    std::cout << "Enter the key for the step to the [left]\n";
    std::cin >> left;

}

void GameView::LeaveGame(){
    std::cout << "See you later, player!"<< std::endl;
}

void GameView::GameOver(){
std::cout << "--------GAME OVER--------\n"
"Don't give up - it's better to try again." << std::endl;
}

bool GameView::Goon(){
return this->going;
}