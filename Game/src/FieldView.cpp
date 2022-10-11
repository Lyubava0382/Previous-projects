#include "FieldView.h"
#include <cmath>
FieldView::FieldView(Field& one, Player& character): GameField(one), hero(character){}

void FieldView::PrintBorder() const {
    for (int i = 0; i < round(GameField.GetWidth()/3) + 1; i++)
        std::cout <<  "--";
    std::cout << '-' << std::endl;
}

void FieldView::Print() const {
    PrintBorder();
    int numberY_1 = 0;
    int numberY = round(round(GameField.GetHeight()/3)/2);
    int numberX_1 = 0;
    int numberX = round(round(GameField.GetWidth()/3)/2);
    if (hero.GetLocal().x - numberX > 0){
        numberX_1 = hero.GetLocal().x - numberX;
    }
    if (hero.GetLocal().y - numberY > 0){
        numberY_1 = hero.GetLocal().y - numberY;
    }
    for (int i = numberY_1; i < numberY_1 + numberY*2 && i < GameField.GetHeight(); i++){
        std::cout <<  "| ";
        for (int j = numberX_1; j < numberX_1 + numberX*2 && j < GameField.GetWidth(); j++) {
            std::cout << CelluleView(GameField.GetField()[i][j], hero).GetView() << ' ';
        }

        std::cout << '|' << std::endl;
    }
    PrintBorder();
}
FieldView::~FieldView(){};
