
#include <fstream>
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
              "To read the detailed rules, click - [" << *instruction<< "]\n"
                                                                        "__________________________________________\n"
                                                                        "To move around the map, use these keys:\n"
                                                                        "Up - [" << up << "]\nLeft - [" << left<< "]"
                                                                                                                  "\nDown - [" << down<< "]\nRight - [" << right<< "]\n"
                                                                                                                                                                   "__________________________________________\n"
                                                                                                                                                                   "To exit the game, click - [" << *exit<< "]\n"
                                                                                                                                                                                                            "To change the control keys, press - []\n"
                                                                                                                                                                                                                                                                      "To read the menu again, press - [" << *menu << "]\n";
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
    else if (command == *exit){
        LeaveGame();
    }
    else if (command == *menu){
        PrintMenu();
        return GameInput();
    }
    else if (command == *records){
        double outt;
        std::ifstream record("..\\src\\new.txt");
        while(record.good()){
            record >> outt;
            std::cout << outt << std::endl;
        }
        record.close();
        return GameInput();
    }
    else if (command == *instruction){
        ReadInstruction();
        return GameInput();
    }
    else std::cout << "Didn't they teach you how to follow the rules?\n";
    return {0,0};
}


void GameView::LeaveGame(){
    std::cout << "See you later, player!"<< std::endl;
    going = false;
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

bool GameView::Goon(){
    return this->going;
}

void GameView::NeedKey(){
 std::cout << "You didn't find all the keys." << std::endl;
}

void GameView::Key(bool key){
    if (key){
        std::cout << "The key is in the treasure." << std::endl;
    } else {
        std::cout << "Oops! .. It's empty." << std::endl;
    }

}

void GameView::GameOver(double sec){
    std::cout << "Congratulations! you have completed the game. Your score:"
    << sec << std::endl;
}