//
// Created by Любава on 05.12.2021.
//

#include "GameView.h"


void GameView::PrintMenu(char command[]){
    std::cout << "Hi, stranger... Welcome to the wonderful game\nRead this instruction carefully\n"<<
    "To read the detailed rules, click - [" << command[6]<< "]\n"
    "__________________________________________\n"
    "To move around the map, use these keys:\n"
    "Up - [" << command[0] << "]\nLeft - [" << command[1]<< "]"
      "\nDown - [" << command[2]<< "]\nRight - [" << command[3]<< "]\n"
    "__________________________________________\n"
    "To exit the game, click - [" << command[4]<< "]\n"
    "To save press - ["<< command[8]<< "]\n"
    "To load game press - ["<< command[9]<< "]\n"
    "To change the control keys, press - [" << command[7]<< "]\n"
    "To read the menu again, press - [" << command[5] << "]\n";
    //GameInput();
}


void GameView::ChangeUP(){
    std::cout << "Enter the key to step [up]:\n";
}
void GameView::ChangeDOWN(){
    std::cout << "Enter the key to step [down]:\n";
}
void GameView::ChangeRIGHT(){
    std::cout << "Enter the key for the step to the [right]\n";
}
void GameView::ChangeLEFT(){
    std::cout << "Enter the key for the step to the [left]\n";
}

void GameView::LeaveGame(){
    std::cout << "See you later, player!"<< std::endl;
}
void GameView::ChangingEnd() {
    std::cout << "Now go on!\n";
}

void GameView::GameOver(){
std::cout << "--------GAME OVER--------\n"
"Don't give up - it's better to try again." << std::endl;
}

void GameView::ReadInstruction(){
    std::cout << "\tYou appear at the entrance cage. Your goal is to find a way out. \n\n"
                 "However, you can open the exit door only if you have a {key} with you.\n"
                 "The {key} is hidden in one of the chests located on the field. \n"
                 "You can open the {chest} (and pick up the key, or leave with nothing) by paying one coin.\n"
                 "You can earn coins by fighting {monsters} along the way.\n"
                 "On the field, you can also pick up {food} that instantly heals health by a random amount.\n"
                 "You can use {portals} to move around the field faster or bypass {monsters}.\n\n"
                 "\tGood luck!\n";
}

void GameView::GameLoading(){
    std::cout << "Do you want to continue the game?\n"
                 "[y] - yes\t[n] - no:" << std::endl;
}
void GameView::Save_Load_text(){
    std::cout << "Enter the name of the save:" << std::endl;
}