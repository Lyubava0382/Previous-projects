#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

enum TYPE{PASSABLE, NOPASS, IN, OUT};
enum OBJECT{NONE, FOOD, BOX, PORTAL, SMALLMONSTER, MEDIUMMONSTER, LARGEMONSTER};
enum GO{RIGHT, LEFT, UP, DOWN, STOP, START};

struct Coordinates{
    int x;
    int y;
};

class Interior{
public:
    virtual OBJECT GetObject() = 0;
};

class Characters: Interior{
public:
    virtual OBJECT GetObject() = 0;
    virtual void SetHealth(int a) = 0;
    virtual int GetHealth() = 0;
    virtual int GetAttack() = 0;
};

class Player: Characters{
public:
    explicit Player() {
        location = {0,0};
        health = 10;
        key = false;
        attack = 1;
        type = NONE;
    }
    void SetHealth(int a){
        this->health = a;
    }
    int GetHealth() {
        return this->health;
    }
    int GetAttack() {
        return this->attack;
    }
    void SetKey(bool yes) {
        this->key = yes;
    }
    bool GetKey() const{
        return this->key;
    }
    OBJECT GetObject(){
        return this->type;
    }
    void SetLocal(Coordinates place) {
        this->location = place;
    }
    Coordinates GetLocal() {
        return this->location;
    }
    void SetCoins(int number) {
        this->coins += number;
    }
    int GetCoins() {
        return this->coins;
    }

private:
    int health;
    int attack;
    Coordinates location{};
    bool key;
    OBJECT type;
    int coins;
};

class Item: Interior{
public:
    virtual OBJECT GetObject() = 0;
    virtual void interplay(Player& person) = 0;
    virtual ~Item(){};
};
class Heal: public Item{
public:
    Heal(): type(FOOD){}

    void interplay(Player& person) final{
        person.SetHealth(rand() % 10 + person.GetHealth());
    };

    OBJECT GetObject() final{
        return this->type;
    }
private:
    OBJECT type;
};

class Box: public Item{
public:
    Box(bool filled): full(filled), type(BOX){}

    void interplay(Player& person) final{
        if (full && person.GetCoins() > 0){
            person.SetKey(true);
            person.SetCoins(-1);
        }
    };

    OBJECT GetObject() final{
        return this->type;
    }
private:
    OBJECT type;
    bool full;
};

class Teleport: public Item{
public:
    Teleport(Coordinates points[2]): firstplace(points[0]), secondplace(points[1]), type(PORTAL){}

    void interplay(Player& person) final{
        if (person.GetLocal().x == firstplace.x && person.GetLocal().y == firstplace.y)
            person.SetLocal(secondplace);
        else person.SetLocal(firstplace);
    };

    OBJECT GetObject() final{
        return this->type;
    }

private:
    OBJECT type;
    Coordinates firstplace;
    Coordinates secondplace;
};

class Enemy: Characters{
public:
    virtual void fight(Player& hero) = 0;
    virtual void hit(Player& hero) = 0;
    virtual void miss(Player& hero) = 0;
    virtual void SetHealth(int a) = 0;
    virtual int GetHealth() = 0;
    virtual int GetAttack() = 0;
    virtual OBJECT GetObject() = 0;
    virtual ~Enemy() {};
};

class Smonster: public Enemy {
public:
    Smonster(): health(5), attack(1), type(SMALLMONSTER), goon(true){
        for (int i = 0; i < 5; i++) {
            assailable[i] = 1;
        }
        assailable[rand() % 5] = 0;
        int random = rand() % 5;
        while (assailable[random] == 0){
            random = rand() % 5;
        }
        assailable[random] = 0;
    }
    void SetHealth(int a) final{
        this->health = a;
    }
    int GetHealth() final{
        return this->health;
    }
    int GetAttack() final{
        return this->attack;
    }
    OBJECT GetObject() final{
        return this->type;
    }

    void fight(Player& hero){
        int body;
        while (health > 0 && goon){
            char wound;
            std::cout << "Before you is a Monster child." <<std::endl;
            std::cout << "Your HP:   " << hero.GetHealth() << "\t\tHP of the monster:   " << this->health << std::endl;
            std::cout << "Where to shoot?" <<std::endl;
            std::cout << "To the left hand: press 1" <<std::endl;
            std::cout << "To the right hand: press 2" <<std::endl;
            std::cout << "To the left leg: press 3" <<std::endl;
            std::cout << "To the right leg: press 4" <<std::endl;
            std::cout << "To the chest: press 5" <<std::endl;
            std::cout << "Escape: press 0" <<std::endl;
            std::cin >> wound;
            switch (wound) {
                case '0':
                    goon = false;
                    break;
                case '1':
                    body = 0;
                    break;
                case '2':
                    body = 1;
                    break;
                case '3':
                    body = 2;
                    break;
                case '4':
                    body = 3;
                    break;
                case '5':
                    body = 4;
                    break;
                default:
                    body = -1;
                    break;
            }
            if (goon && body >= 0 && assailable[body] == 1) {
                hit(hero);
            }
            else {
                if (goon) miss(hero);
            }
        }
    }
private:
    int health;
    int attack;
    OBJECT type;
    int assailable[5];
    bool goon;

    void hit(Player& hero) {
        this->health = health - hero.GetAttack();

        if (health <= 0){
            goon = false;
            std::cout << "The shot was fatal." << std::endl;
            std::cout << "Who would have thought that such a giant had a weak point?" << std::endl;
            hero.SetCoins(1);
        }
        else {
            std::cout << "You hurt him! Keep it up!" << std::endl;
        }
    }
    void miss(Player& hero){
        std::cout << "You missed." <<std::endl;
        hero.SetHealth(hero.GetHealth() - attack);
        if (hero.GetHealth() < 0){
            goon = false;
            std::cout << "The enemy is stronger than you..." <<std::endl;
            //Game Over
        }
        else
            std::cout << "Try again." <<std::endl;
    }
};

class Mmonster: public Enemy {
public:
    Mmonster(): health(3), attack(2), type(MEDIUMMONSTER), goon(true){
        for (int i = 0; i < 5; i++) {
            assailable[i] = 1;
        }
        assailable[rand() % 5] = 0;
        int random = rand() % 5;
        while (assailable[random] == 0){
            random = rand() % 5;
        }
        assailable[random] = 0;
    }
    void SetHealth(int a) final{
        this->health = a;
    }
    int GetHealth() final{
        return this->health;
    }
    int GetAttack() final{
        return this->attack;
    }
    OBJECT GetObject() final{
        return this->type;
    }

    void fight(Player& hero){
        int body;
        while (health > 0 && goon){
            char wound;
            std::cout << "Before you is a Usual Monster." <<std::endl;
            std::cout << "Your HP:   " << hero.GetHealth() << "\t\tHP of the monster:   " << this->health << std::endl;
            std::cout << "Where to shoot?" <<std::endl;
            std::cout << "To the left hand: press 1" <<std::endl;
            std::cout << "To the right hand: press 2" <<std::endl;
            std::cout << "To the left leg: press 3" <<std::endl;
            std::cout << "To the right leg: press 4" <<std::endl;
            std::cout << "To the chest: press 5" <<std::endl;
            std::cout << "Escape: press 0" <<std::endl;
            std::cin >> wound;
            switch (wound) {
                case '0':
                    goon = false;
                    break;
                case '1':
                    body = 0;
                    break;
                case '2':
                    body = 1;
                    break;
                case '3':
                    body = 2;
                    break;
                case '4':
                    body = 3;
                    break;
                case '5':
                    body = 4;
                    break;
                default:
                    body = -1;
                    break;
            }
            if (goon && body >= 0 && assailable[body] == 1) {
                assailable[body] = 0;
                hit(hero);
                switch (body) {
                    case 0:
                    case 1:
                        std::cout << "This hand is destroyed." << std::endl;
                        break;
                    case 2:
                    case 3:
                        std::cout << "This leg is destroyed." << std::endl;
                        break;
                    case 4:
                        std::cout << "Chest is destroyed." << std::endl;
                        break;
                }

                std::cout << "Now it's useless to shoot at it." << std::endl;
            }
            else {
                if (goon) miss(hero);
            }
        }
    }

private:
    int health;
    int attack;
    OBJECT type;
    int assailable[5];
    bool goon;

    void hit(Player& hero) {
        this->health = health - hero.GetAttack();

        if (health <= 0){
            goon = false;
            std::cout << "The shot was fatal." << std::endl;
            std::cout << "Who would have thought that such a giant had a weak point?" << std::endl;
            hero.SetCoins(1);
        }
    }
    void miss(Player& hero){
        std::cout << "You missed." <<std::endl;
        hero.SetHealth(hero.GetHealth() - attack);
        if (hero.GetHealth() < 0){
            goon = false;
            std::cout << "The enemy is stronger than you..." <<std::endl;
            //Game Over
        }
        else
            std::cout << "Try again." <<std::endl;
    }
};

class Lmonster: public Enemy {
public:
    Lmonster(): health(100), attack(4),  type(LARGEMONSTER),
                goon(true){
        std::cout << health <<std::endl;
        for (int i = 0; i < 3; i++) {
            assailable[i] = 0;
        }
        assailable[rand() % 3] = 1;
    }

    void SetHealth(int a) final{
        this->health = a;
    }
    int GetHealth() final{
        return this->health;
    }
    int GetAttack() final{
        return this->attack;
    }
    OBJECT GetObject() final{
        return this->type;
    }
    void fight(Player& hero){
        int body;
        while (health > 0 && goon){
            char wound;
            std::cout << "Before you is a Big Monster." <<std::endl;
            std::cout << "Your HP:   " << hero.GetHealth() << "\t\tHP of the monster:   " << this->health << std::endl;
            std::cout << "Where to shoot?" <<std::endl;
            std::cout << "To the head: press 1" <<std::endl;
            std::cout << "To the heart: press 2" <<std::endl;
            std::cout << "Into the belly: press 3" <<std::endl;
            std::cout << "Escape: press 0" <<std::endl;
            std::cin >> wound;
            switch (wound) {
                case '0':
                    goon = false;
                    break;
                case '1':
                    body = 0;
                    break;
                case '2':
                    body = 1;
                    break;
                case '3':
                    body = 2;
                    break;
                default:
                    body = -1;
                    break;
            }
            if (goon && body >= 0 && assailable[body] == 1) {
                hit(hero);
            }
            else {
                if (goon) miss(hero);
            }
        }
    }

private:
    int health;
    int attack;
    OBJECT type;
    int assailable[3];
    bool goon;

    void hit(Player& hero){
        this->health = 0;
        goon = false;
        std::cout << "The shot was fatal." << std::endl;
        std::cout << "Who would have thought that such a giant had a weak point?" << std::endl;
        hero.SetCoins(2);
    }
    void miss(Player& hero){
        std::cout << "You missed." <<std::endl;
        hero.SetHealth(hero.GetHealth() - attack);
        if (hero.GetHealth() < 0){
            goon = false;
            std::cout << "The enemy is stronger than you..." <<std::endl;
            //Game Over
        }
        else
            std::cout << "Try again." <<std::endl;
    }
};

class Cell{
public:
    virtual TYPE GetType() = 0;
    virtual void SetType(TYPE t) = 0;
    virtual void SetPoint(int x, int y)=0;
    virtual Coordinates GetPoint() = 0;
    virtual OBJECT GetObject() = 0;
    virtual void SetObject(OBJECT t)=0;
    virtual void SetKey(bool rich) = 0;
    virtual bool GetKey() = 0;
    virtual void SetStep(GO step) = 0;
    virtual GO GetStep( ) = 0;
    virtual ~Cell(){};
};

class Cellule: public Cell{
public:
    Cellule():position({0,0}), type(PASSABLE), occupy(NONE), nextstep(STOP), treasure(false){}

    Cellule(const Cellule& other) : position(other.position), type(other.type),
                                    occupy(other.occupy), nextstep(other.nextstep), treasure(other.treasure){ // Конструктор копирования
    }

    Cellule& operator = (const Cellule& other) { // Оператор присваивания копированием
        if (this != &other){
            position = other.position;
            type = other.type;
            occupy = other.occupy;
            nextstep = other.nextstep;
            treasure = other.treasure;
        }
        return* this;
    }

    Cellule(Cellule&& other) { // Конструктор перемещения
        std::swap(this->position, other.position);
        std::swap(this->type, other.type);
        std::swap(this->occupy, other.occupy);
        std::swap(this->nextstep, other.nextstep);
        std::swap(this->treasure, other.treasure);
    }

    Cellule& operator=(Cellule&& other) { // Оператор присваивания перемещением
        if (this != &other) {
            std::swap(this->position, other.position);
            std::swap(this->type, other.type);
            std::swap(this->occupy, other.occupy);
            std::swap(this->nextstep, other.nextstep);
            std::swap(this->treasure, other.treasure);
        }
        return* this;
    }

    TYPE GetType() final {
        return this->type;
    }

    void SetType(TYPE t) final {
        this->type = t;
    }

    void SetPoint(int a, int b) final {
        this->position.x = a;
        this->position.y = b;
    }
    Coordinates GetPoint() final {
        return this->position;
    }

    OBJECT GetObject() final {
        return this->occupy;
    }

    void SetObject(OBJECT t) final {
        this->occupy = t;
    }
    bool GetKey() final {
        return this->treasure;
    }

    void SetKey(bool rich) final {
        this->treasure = rich;
    }

    GO GetStep() final {
        return this->nextstep;
    }

    void SetStep(GO step) final {
        this->nextstep = step;
    }

private:
    Coordinates position{};
    TYPE type;
    OBJECT occupy;
    bool treasure;
    GO nextstep;
};

class CelluleView {
public:
    explicit CelluleView(Cellule& one, Player& someone) {
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

    char GetView() const {
        return this->view;
    }
private:
    char view;
};

class Field {
public:
    explicit Field(int w = 10, int h = 10){
        width = w;
        height = h;
        monstercount = 0;
        field = new Cellule*[height];
        for (int i = 0; i < height; i ++){
            field[i] = new Cellule[width];
            for (int j = 0; j < width; j ++){
                field[i][j].SetPoint(j, i);
            }
        }
        Monsters = new Coordinates[10];
    }
    ~Field() {
        for (int i = 0; i < height; i ++) {
            delete[] field[i];
        }
        delete[] field;
        delete[] Monsters;
    }

    Field(const Field &other) :  width(other.width), height(other.height),
                                in(other.in), out(other.out), Monsters(new Coordinates[monstercount]), monstercount(other.monstercount), field(new Cellule*[height]) { // Конструктор копирования
        for (int i = 0; i < height; i ++) {
            field[i] = new Cellule[width];
            for (int j = 0; j < width; j ++){
                field[i][j] = other.field[i][j];
            }
        }
        for (int k = 0; k < monstercount; k ++){
            Monsters[k] = other.Monsters[k];
        }
    }

    Field& operator = (const Field &other) { // Оператор присваивания копированием
        if (this != &other){
            for (int i = 0; i < height; i ++){
                delete[] field[i];
            }
            delete[] field;
            delete[] Monsters;
            width = other.width;
            height = other.height;
            in = other.in;
            out = other.out;
            monstercount = other.monstercount;
            field = new Cellule* [height];
            for (int i = 0; i < height; i ++) {
                field[i] = new Cellule[width];
                for (int j = 0; j < width; j ++){
                    field[i][j] = other.field[i][j];
                }
            }
            Monsters = new Coordinates[monstercount];
            for (int k = 0; k < monstercount; k ++){
                Monsters[k] = other.Monsters[k];
            }
        }
        return *this;
    }

    Field(Field&& other){ // Конструктор перемещения
        std::swap(this->width, other.width);
        std::swap(this->height, other.height);
        std::swap(this->in, other.in);
        std::swap(this->out, other.out);
        std::swap(this->Monsters, other.Monsters);
        std::swap(this->monstercount, other.monstercount);
        std::swap(this->field, other.field);
    }

    Field& operator=(Field&& other) { // Оператор присваивания перемещением
        if (this != &other) {
            std::swap(this->width, other.width);
            std::swap(this->height, other.height);
            std::swap(this->in, other.in);
            std::swap(this->out, other.out);
            std::swap(this->Monsters, other.Monsters);
            std::swap(this->monstercount, other.monstercount);
            std::swap(this->field, other.field);
        }
        return *this;
    }
    void MakeInOut() {
        in = {rand() % width, rand() % height};
        field[in.y][in.x].SetType(IN);
        out = {rand() % width, rand() % height};
        while (abs(out.x - in.x) < round(0.2* width) || abs(out.y - in.y) < round(0.2* height) ){

            out = {rand() % width, rand() % height};
        }
        field[out.y][out.x].SetType(OUT);
    }

    Coordinates GetIn() {
        return this->in;
    }

    void MakeObjects() {
        int chance;
        for (int i = 0; i < height; i ++) {
            for (int j = 0; j < width; j ++) {
                Coordinates any = {j, i};
                chance = rand() % 100 + 1;
                if ((chance <= 10) && (field[any.y][any.x].GetType() != IN) && (field[any.y][any.x].GetType() != OUT)) //10% chance
                    field[any.y][any.x].SetType(NOPASS);
            }
        }
    }

    void MakeItems() {
        teleports[0] = {rand() % width, rand() % height};
        while (field[teleports[0].y][teleports[0].x].GetType() != PASSABLE)
            teleports[0] = {rand() % width, rand() % height};
        teleports[1] = {rand() % width, rand() % height};
        while (field[teleports[1].y][teleports[1].x].GetType() != PASSABLE)
            teleports[1] = {rand() % width, rand() % height};

        field[teleports[0].y][teleports[0].x].SetObject(PORTAL);
        field[teleports[1].y][teleports[1].x].SetObject(PORTAL);

        int number = round(0.02 * width * height);
        Coordinates treasure;
        treasure = {rand() % width, rand() % height};
        while (field[treasure.y][treasure.x].GetType() != PASSABLE || field[treasure.y][treasure.x].GetObject() != NONE)
            treasure = {rand() % width, rand() % height};
        field[treasure.y][treasure.x].SetObject(BOX);
        field[treasure.y][treasure.x].SetKey(true);
        for (int i = 0; i < number - 1; i++) {
            treasure = {rand() % width, rand() % height};
            while (field[treasure.y][treasure.x].GetType() != PASSABLE ||
                   field[treasure.y][treasure.x].GetObject() != NONE)
                treasure = {rand() % width, rand() % height};
            field[treasure.y][treasure.x].SetKey(false);
            field[treasure.y][treasure.x].SetObject(BOX);
        }
        Coordinates healing;
        for (int i = 0; i < number; i++) {
            healing = {rand() % width, rand() % height};
            while (field[healing.y][healing.x].GetType() != PASSABLE || field[healing.y][healing.x].GetObject() != NONE)
                healing = {rand() % width, rand() % height};
            field[healing.y][healing.x].SetObject(FOOD);
        }

    }
    void MakeEnemies() {
        Coordinates monster;
        int number;
        OBJECT whichone;
        for (int j = 0; j < 3; j++){
            switch (j) {
                case 0 :
                    number = round(0.02 * width * height);
                    whichone = SMALLMONSTER;
                    break;
                case 1:
                    number = round(0.01 * width * height);
                    whichone = MEDIUMMONSTER;
                    break;
                case 2:
                    number = 1;
                    whichone = LARGEMONSTER;
                    break;
            }
            for (int i=0; i < number; i++) {
                monster = {rand() % width, rand() % height};
                while (field[monster.y][monster.x].GetType() != PASSABLE || field[monster.y][monster.x].GetObject() != NONE)
                    monster = {rand() % width, rand() % height};
                field[monster.y][monster.x].SetStep(START);
                Monsters[monstercount++] = {monster.x, monster.y};
                field[monster.y][monster.x].SetObject(whichone);
            }
        }
        field[0][0].SetObject(MEDIUMMONSTER);
    }

    bool Access(Coordinates presentstate){
        switch (field[presentstate.y][presentstate.x].GetStep()) {
            case RIGHT:
                presentstate.x++;
                break;
            case LEFT:
                presentstate.x--;
                break;
            case UP:
                presentstate.y--;
                break;
            case DOWN:
                presentstate.y++;
                break;
        }
        if ((presentstate.x >= 0) && (presentstate.x < width) &&
        (presentstate.y >= 0) && (presentstate.y < height) &&
        (field[presentstate.y][presentstate.x].GetType() == PASSABLE) && (field[presentstate.y][presentstate.x].GetObject() == NONE))
            return true;
        else return false;
    }


    int GetHeight() {
        return this->height;
    }

    int GetWidth() {
        return this->width;
    }
    int GetMonsterCount() {
        return this->monstercount;
    }

    Cellule** GetField() {
        return this->field;
    }

    Coordinates* GetTeleports() {
        return this->teleports;
    }

    Coordinates* GetMonsters() {
        return this->Monsters;
    }

private:
    Cellule** field;
    int width;
    int height;
    Coordinates in{};
    Coordinates out{};
    Coordinates* Monsters;
    Coordinates teleports[2];
    int monstercount;
};

class FieldView {
public:
    explicit FieldView(Field& one, Player& character): GameField(one), hero(character){}

    void PrintBorder() const {
        for (int i = 0; i < GameField.GetWidth() + 1; i++)
            std::cout <<  "--";
        std::cout << '-' << std::endl;
    }

    void Print() const {
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

    virtual ~FieldView(){};
private:
    Field& GameField;
    Player& hero;
};

class Game {
public:
    explicit Game(){
        Player person;
        Field game( 15, 10);
        Start(game);
    }

    void NextCondition(Cellule& locate, Field& game){
        int constant;
        constant = 3;
        GO array[4] = {RIGHT, DOWN, LEFT, UP};
        switch (locate.GetObject()) {
            case SMALLMONSTER: {
                switch (locate.GetStep()) {
                    case START:
                        for (int i = 0; i <= constant; i++) {
                            locate.SetStep(array[i]);
                            if (game.Access(locate.GetPoint()))
                                break;
                        }
                        if (!game.Access(locate.GetPoint()))
                            locate.SetStep(STOP);
                        break;
                    default:
                        do{
                            for (int i = 0; i <= constant; i++){
                                if (array[i] == locate.GetStep()){
                                    if (i  < constant) locate.SetStep(array[i+1]);
                                    else locate.SetStep(array[i-constant]);
                                    break;
                                }
                            }
                        } while (!game.Access(locate.GetPoint()));
                        break;
                }
            }
            case MEDIUMMONSTER:{
                switch (locate.GetStep()) {
                    case START:
                        for (int i = 0; i <= constant; i += 2) {
                            locate.SetStep(array[i]);
                            if (game.Access(locate.GetPoint()))
                                break;
                        }
                        if (!game.Access(locate.GetPoint()))
                            locate.SetStep(STOP);
                        break;
                    default:
                        if (!game.Access(locate.GetPoint())) {
                            if (locate.GetStep() == array[0])
                                locate.SetStep(array[2]);
                            else if (locate.GetStep() == array[2])
                                locate.SetStep(array[0]);
                        }
                        break;
                }
                break;
            }
            case LARGEMONSTER:{
                if (abs(person.GetLocal().x - locate.GetPoint().x) < abs(person.GetLocal().y - locate.GetPoint().y)){
                    if(person.GetLocal().y > locate.GetPoint().y) locate.SetStep(DOWN);
                    if(person.GetLocal().y < locate.GetPoint().y) locate.SetStep(UP);
                }
                else{
                    if(person.GetLocal().x > locate.GetPoint().x) locate.SetStep(RIGHT);
                    if(person.GetLocal().x < locate.GetPoint().x) locate.SetStep(LEFT);
                }
                if (!game.Access(locate.GetPoint()))
                    locate.SetStep(STOP);
                break;
            }
        }
    }

    void Step(GO side, Coordinates begin, int k, Field& game){
        switch (side) {
            case RIGHT:
                game.GetMonsters()[k] = {begin.x + 1, begin.y};
                break;
            case LEFT:
                game.GetMonsters()[k] = {begin.x - 1, begin.y};
                break;
            case UP:
                game.GetMonsters()[k] = {begin.x, begin.y - 1};
                break;
            case DOWN:
                game.GetMonsters()[k] = {begin.x, begin.y + 1};
                break;
        }
        if (side != START && side != STOP){
            game.GetField()[ game.GetMonsters()[k].y][ game.GetMonsters()[k].x].SetObject(game.GetField()[begin.y][begin.x].GetObject());
            game.GetField()[ game.GetMonsters()[k].y][ game.GetMonsters()[k].x].SetStep(game.GetField()[begin.y][begin.x].GetStep());
            game.GetField()[begin.y][begin.x].SetStep(STOP);
            game.GetField()[begin.y][begin.x].SetObject(NONE);
        }
    }

    void EnemyMove(Field& game)
    {
        for (int k = 0; k < game.GetMonsterCount(); k++) {
            NextCondition(game.GetField()[ game.GetMonsters()[k].y][ game.GetMonsters()[k].x], game);
            Step(game.GetField()[ game.GetMonsters()[k].y][ game.GetMonsters()[k].x].GetStep(),  game.GetMonsters()[k], k, game);
        }
    }

    void GameMove(Field& game) {
        Coordinates back;
        //EnemyMove(game);
        back = person.GetLocal();
        /*
         *
         */
         person.SetLocal({0,0});
        switch (game.GetField()[0][0].GetType()) {
            case NOPASS:
                person.SetLocal(back);
                break;
            case IN:
                person.SetLocal(back);
                break;
            case OUT:
                if (person.GetKey()) {
                    std::cout << "Congratulations! You completed the game" << std::endl;
                }
                else {
                    std::cout << "Oh no! The door is locked.\n";
                    std::cout << "Please get the key and come back here!" << std::endl;
                }
                break;
            case PASSABLE: {
                if (game.GetField()[person.GetLocal().y][person.GetLocal().x].GetObject() != NONE)
                    switch (game.GetField()[person.GetLocal().y][person.GetLocal().x].GetObject()) {
                        case BOX: {
                            Box keybox(game.GetField()[person.GetLocal().y][person.GetLocal().x].GetKey());
                            keybox.interplay(person);
                            game.GetField()[person.GetLocal().y][person.GetLocal().x].SetObject(NONE);
                            game.GetField()[person.GetLocal().y][person.GetLocal().x].SetKey(false);
                            break;
                        }
                        case FOOD: {
                            Heal healing;
                            healing.interplay(person);
                            game.GetField()[person.GetLocal().y][person.GetLocal().x].SetObject(NONE);
                            break;
                        }
                        case PORTAL: {
                            Teleport teleportation(game.GetTeleports());
                            teleportation.interplay(person);
                            break;
                        }
                        case SMALLMONSTER: {
                            Smonster enemy;
                            enemy.fight(person);
                            if(enemy.GetHealth() <= 0) {
                                game.GetField()[person.GetLocal().y][person.GetLocal().x].SetObject(NONE);
                            }
                            break;
                        }
                        case MEDIUMMONSTER: {
                            Mmonster enemy;
                            enemy.fight(person);
                            if(enemy.GetHealth() <= 0) {
                                game.GetField()[person.GetLocal().y][person.GetLocal().x].SetObject(NONE);
                            }
                            break;
                        }
                        case LARGEMONSTER: {
                            Lmonster enemy;
                            enemy.fight(person);
                            if(enemy.GetHealth() <= 0) {
                                game.GetField()[person.GetLocal().y][person.GetLocal().x].SetObject(NONE);
                            }
                            break;
                        }
                    }
            }
                break;
        }
    }

    void Start(Field& game) {
        srand(time(NULL));
        game.MakeInOut();
        game.MakeObjects();
        person.SetLocal(game.GetIn());
        game.MakeItems();
        game.MakeEnemies();
        FieldView(game, person).Print();
       // for (int k = 0; k < 3; k++){
            GameMove(game);
            FieldView(game, person).Print();
        //}
    }
private:
    Field game;
    Player person;
};

int main() {
    Game firstGame;
}
