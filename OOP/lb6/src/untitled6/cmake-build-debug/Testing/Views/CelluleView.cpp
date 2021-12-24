
#include "CelluleView.h"
#include "../Static_Items/Box.h"
#include "../Static_Items/Heal.h"
CelluleView::CelluleView(Cellule& one, Player& someone) {
    switch (one.GetType())
    {
        case PASSABLE:
            switch (one.GetObject()) {
                case BOX: {
                    //Player person;
                    //dynamic_cast<Box*>(one.GetThing())->interplay(person);
                    //std::cout << typeid(dynamic_cast<Heal*>(one.GetThing())).name() << std::endl;
                    //std::string str1 (typeid(dynamic_cast<Box*>(one.GetThing())).name());
                    //if (str1.compare("class Box *") == 0){
                        //std::cout << dynamic_cast<Box*>(one.GetThing())->GetFull() << std::endl;
                    //}

                   /* std::cout << std::endl << typeid((one.GetObj())).name() << std::endl;
                    std::cout << std::endl << typeid(dynamic_cast<Box*>(one.GetObj())).name() << std::endl;
                    std:: cout << std::endl << one.GetObj()<< std::endl;
                    std::cout << dynamic_cast<Box*>(one.GetObj())->GetFull() << std::endl;
                    */
                    this->view = '$';
                    break;
                }
                case FOOD: {
                    this->view = '+';
                    break;
                }
                case PORTAL: {
                    this->view = '@';
                    break;
                }
                case SMALLMONSTER: {
                    this->view = '1';
                    break;
                }
                case MEDIUMMONSTER: {
                    this->view = '2';
                    break;
                }
                case LARGEMONSTER: {
                    this->view = '3';
                    break;
                }
                case NONE: {
                    this->view = ' ';
                    break;
                }
            }
            break;
        case NOPASS:
            this->view = '/';
            break;
        case OUT:
            this->view = '>';
            break;
        case IN:
            this->view = '^';
            break;
        default:
            this->view = '?';
            break;
    }
    if (someone.GetLocal().x == one.GetPoint().x && someone.GetLocal().y == one.GetPoint().y) this->view = 'F';
}
char CelluleView::GetView() const {
    return this->view;
}