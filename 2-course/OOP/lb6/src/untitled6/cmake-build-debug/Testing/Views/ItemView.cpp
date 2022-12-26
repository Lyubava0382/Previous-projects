//
// Created by Любава on 06.12.2021.
//
#include "../../Info.h"
#include "ItemView.h"
ItemView::ItemView(){}
void ItemView::BoxPrint(bool open, bool key){
    if (open){
        std::cout << "You spent 1 coin and opened the chest.\n";
        if (key){
            std::cout << "The key to the exit has been received!\n";
        }
        else{
            std::cout << "It's empty.\n";
        }
    }
    else {
        std::cout << "You don't have enough coins to open the chest.\n"
                     "Come back later with the money.\n";
    }
}
void ItemView::HealPrint(int health){
    if (health == 10) std::cout << "Your health has been restored to maximum.\n";
    else std::cout << "Received " << health << " HP.\n";
}