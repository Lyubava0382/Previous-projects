
#include "FieldView.h"

FieldView::FieldView(Field& one, Player& character): GameField(one), hero(character){}

    void FieldView::PrintBorder() const {
        for (int i = 0; i < GameField.GetWidth() + 1; i++)
            std::cout <<  "--";
        std::cout << '-' << std::endl;
    }

    void FieldView::Print() const {
        PrintBorder();
        for (int i = 0; i < GameField.GetHeight(); i++){
            std::cout <<  "| ";
            for (int j = 0; j < GameField.GetWidth(); j++) {
                std::cout << CelluleView(GameField.GetField()[i][j], hero).GetView() << ' ';
            }

            std::cout << '|' << std::endl;
        }
        PrintBorder();
    }
