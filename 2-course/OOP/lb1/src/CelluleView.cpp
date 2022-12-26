#include "CelluleView.h"

     CelluleView::CelluleView(Cellule& one) {
        switch (one.GetType())
        {
            case PASSABLE:
                this->view = ' ';
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
    }

    char CelluleView::GetView() const {
        return this->view;
    }
    CelluleView ::~CelluleView(){};
