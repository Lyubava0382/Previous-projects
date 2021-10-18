#include "Field.h"
#include <cmath>
     Field::Field(int w, int h){
        width = w;
        height = h;
        field = new Cellule*[height];
        for (int i = 0; i < height; i++){
            field[i] = new Cellule[width];
            for (int j = 0; j < width; j++){
                field[i][j].SetPoint(j, i);
            }
        }
    }
   Field:: ~Field() {
        for (int i = 0; i < height; i++) {
            delete[] field[i];
        }
        delete[] field;
    }

    Field::Field(const Field& other) : width(other.width), height(other.height),
                                in(other.in), out(other.out), field(new Cellule*[height]) { // Конструктор копирования
        for (int i = 0; i < height; i++) {
            field[i] = new Cellule[width];
            for (int j = 0; j < width; j++){
                field[i][j] = other.field[i][j];
            }
        }
    }

     Field & Field:: operator = (const Field &other) { // Оператор присваивания копированием
        if (this != &other){
            for (int i = 0; i < height; i ++){
                delete[] field[i];
            }
            delete[] field;
            width = other.width;
            height = other.height;
            in = other.in;
            out = other.out;
            field = new Cellule* [height];
            for (int i = 0; i < height; i++) {
                field[i] = new Cellule[width];
                for (int j = 0; j < width; j++){
                    field[i][j] = other.field[i][j];
                }
            }
        }
        return* this;
    }

    Field::Field(Field&& other) { // Конструктор перемещения
        std::swap(this->width, other.width);
        std::swap(this->height, other.height);
        std::swap(this->field, other.field);
        std::swap(this->in, other.in);
        std::swap(this->out, other.out);
    }

    Field & Field:: operator=(Field&& other) { // Оператор присваивания перемещением
        if (this != &other) {
            std::swap(this->width, other.width);
            std::swap(this->height, other.height);
            std::swap(this->field, other.field);
        std::swap(this->in, other.in);
        std::swap(this->out, other.out);
        }
        return* this;
    }

    void Field::MakeInOut() {
        in = {rand() % width, rand() % height};
        field[in.y][in.x].SetType(IN);
        out = {rand() % width, rand() % height};
        while (abs(out.x - in.x) < std::round(0.2 * width) || abs(out.y - in.y) < std::round(0.2 * height) ){

            out = {rand() % width, rand() % height};
        }
        field[out.y][out.x].SetType(OUT);
    }

    Coordinates Field::GetIn() {
        return this->in;
    }

    void Field::MakeObjects() {
        int chance;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                Coordinates any = {j, i};
                chance = rand() % 100 + 1;
                if ((chance <= 10) && (field[any.y][any.x].GetType() != IN) && (field[any.y][any.x].GetType() != OUT)) //10% chance
                    field[any.y][any.x].SetType(NOPASS);
            }
        }
    }

    void Field::PrintBorder() const {
        for (int i = 0; i < width + 1; i++)
            std::cout <<  "--";
        std::cout << '-' << std::endl;
    }

    void Field::Print() const {
        PrintBorder();
        for (int i = 0; i < height; i++){
            std::cout <<  "| ";
            for (int j = 0; j < width; j++) {
                std::cout << CelluleView(this->field[i][j]).GetView() << ' ';
            }

            std::cout << '|' << std::endl;
        }
        PrintBorder();
    }

    void Field::Start() {
        srand(time(NULL));
        MakeInOut();
        MakeObjects();
        Print();
    }

