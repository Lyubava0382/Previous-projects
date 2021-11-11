#include "CelluleView.h"

     CelluleView::CelluleView(Cellule& one, Player& someone) {
        switch (one.GetType())
        {
            case PASSABLE:
                switch (one.GetObject()) {
                    case BOX: {
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
    CelluleView ::~CelluleView(){};