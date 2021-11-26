
#include "ExitDoorPrint.h"
ExitDoorPrint::ExitDoorPrint() {}
void ExitDoorPrint::KeyPrint(){
    std::cout << "Oh no! The door is locked.\n";
    std::cout << "Please get the key and come back here!" << std::endl;
}
void ExitDoorPrint::CoinsPrint(){
    std::cout << "You don't have enough money to pass.\n"
                 "Earn in the battle with the monster and come back when you can pay" << std::endl;
}
void ExitDoorPrint::HealthPrint(){
    std::cout << "You're too weak to be able to get out.\n"
                 "Find the medicine chest and come back"<< std::endl;
}
void ExitDoorPrint::OpenPrint(){
    std::cout << "Congratulations! You completed the game" << std::endl;
}