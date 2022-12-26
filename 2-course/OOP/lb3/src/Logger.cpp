
#include "Logger.h"
Logger::Logger(IObservable& address) {
        if (!outfile.is_open()) outfile.open("Logging.txt");
        streams.first = false;
        streams.second = false;
        address.SetObservable(true);
        address.SetObserver(this);
        char actual_stream = LoggerView().SelectStream();
        //char actual_stream = '2';
        switch (actual_stream) {
            case '2':
                streams.first = true;
                streams.second = true;
                File_Settings();
                break;
            case '1':
                streams.second = true;
                File_Settings();
                break;
            default:
            case '0':
                streams.first = true;
                break;
        }
    }
    void Logger::File_Settings(){
        if (!outfile)
        {
            LoggerView().PrintWarning();
            streams.first = true;
            streams.second = false;
        }

    }

Logger::~Logger(){
        if (outfile.is_open()) outfile.close();
    }

std::ostream& operator<< (std::ostream &out, Player &person)
{
    out << "location    x: " << person.GetLocal().x<< "\ty: " << person.GetLocal().y <<
        "\nKey:\t" << person.GetKey() << "\nCoins:\t" << person.GetCoins() << std::endl<< std::endl;
    return out;
}
std::ostream& operator<< (std::ostream &out, Enemy &monster)
{
    const int enemy_limbs_count = 5;
    out << "Type of the monster:\t"<< monster.GetObject() << "\nHP:\t" << monster.GetHealth()
        << "\nAttack:\t"<< monster.GetAttack()<<"\nVictory reward:\t" << monster.GetReward()
        <<"\nShould the battle continue:\t"<<monster.GetGoing() << "\nAn array of monster vulnerabilities:";
    for (int i = 0; i < enemy_limbs_count; i++)
        out << "\n"<< monster.GetLimb(i) <<" ";
    out << std::endl<< std::endl;
    return out;
}
std::ostream& operator<< (std::ostream &out, Cellule &cell)
{
    out << "Type of cell:\t" << cell.GetType() <<"\nCell coordinate:\tx  "<<cell.GetPoint().x
        << "\ty: " <<cell.GetPoint().y << "\nType of object:\t"
        << cell.GetObject() <<"\nDoes the cage contain a treasure:\t"<<cell.GetKey()
        << "\nDirection of the cell object:\t" << cell.GetStep() <<std::endl<< std::endl;
    return out;
}
std::ostream& operator<< (std::ostream &out, Field &fieldgame)
{
    out << "Height:\t" <<  fieldgame.GetHeight() << "\nWidth:\t" <<fieldgame.GetWidth()
        << "\nEntrance coordination:\tx:  " << fieldgame.GetIn().x << "\ty: " <<fieldgame.GetIn().y
        <<"\nExit coordination:\tx:  " << fieldgame.GetOut().x<< "\ty: " <<fieldgame.GetOut().y
        << "\nNumber of monsters:\t" << fieldgame.GetMonsterCount() << "\nMonsters coordinates";
    for (int i = 0; i < fieldgame.GetMonsterCount(); i++)
        out << "\n"<< i << ".\tx:  "<< fieldgame.GetMonsters()[i].x << "\ty: " <<fieldgame.GetMonsters()[i].y ;
    out << std::endl<< std::endl;
    return out;
    //Cellule** field; &&&

}
std::ostream& operator<< (std::ostream &out, Game &presentgame)
{
    out << "Person address:\t" << presentgame.GetPlayer() <<
        "\nField address:\t" << presentgame.GetField()<<std::endl<< std::endl;
    return out;
}
std::ostream& operator<< (std::ostream &out, Heal &food)
{
    out << "Type:\t" << food.GetObject() << std::endl<< std::endl;
    return out;
}
std::ostream& operator<< (std::ostream &out,  Box &inbox)
{
    out << "Type:\t" << inbox.GetObject() << "\nFull:\t" << inbox.GetFull()<<std::endl<< std::endl;
    return out;
}
std::ostream& operator<< (std::ostream &out, Teleport &teleports)
{
    out << "Type:\t" << teleports.GetObject() << "\nFirst teleport coordination:\tx:  "
        << teleports.GetFirstPlace().x<< "\ty: " << teleports.GetSecondPlace().y<<std::endl<< std::endl;
    return out;
}

void Logger::update(std::string namefunc, Player &person){
    if (streams.first) {
        std::cout <<"Player::\t" << namefunc << ":\n";
        std::cout << person;
    }
    if (streams.second){
        outfile <<"Player::\t"<< namefunc << ":\n";
        outfile << person;
    }
}
void Logger::update(std::string namefunc, Enemy &monster) {
    if (streams.first) {
        std::cout <<"Enemy::\t"<< namefunc << ":\n";
        std::cout << monster;
    }
    if (streams.second){
        outfile <<"Enemy::\t"<< namefunc << ":\n";
        outfile << monster;
    }
}
void Logger::update(std::string namefunc, Cellule &cell) {
    if (streams.first) {
        std::cout <<"Cellule::\t"<< namefunc << ":\n";
        std::cout << cell;
    }
    if (streams.second){
        outfile <<"Cellule::\t"<< namefunc << ":\n";
        outfile << cell;
    }
}
void Logger::update(std::string namefunc, Field &fieldgame) {
    if (streams.first) {
        std::cout <<"Field::\t"<< namefunc << ":\n";
        std::cout << fieldgame;
    }
    if (streams.second){
        outfile <<"Field::\t"<< namefunc << ":\n";
        outfile << fieldgame;
    }
}
void Logger::update(std::string namefunc, Game &presentgame) {
    if (streams.first) {
        std::cout <<"Game::\t"<< namefunc << ":\n";
        std::cout << presentgame;
    }
    if (streams.second){
        outfile <<"Game::\t"<< namefunc << ":\n";
        outfile << presentgame;
    }
}
void Logger::update(std::string namefunc, Heal &food){
    if (streams.first) {
        std::cout <<"Heal::\t"<< namefunc << ":\n";
        std::cout << food;
    }
    if (streams.second){
        outfile <<"Heal::\t"<< namefunc << ":\n";
        outfile << food;
    }
}
void Logger::update(std::string namefunc, Box &inbox) {
    if (streams.first) {
        std::cout <<"Box::\t"<< namefunc << ":\n";
        std::cout << inbox;
    }
    if (streams.second){
        outfile <<"Box::\t"<< namefunc << ":\n";
        outfile << inbox;
    }
}
void Logger::update(std::string namefunc, Teleport &teleports) {
    if (streams.first) {
        std::cout <<"Teleport::\t"<< namefunc << ":\n";
        std::cout << teleports;
    }
    if (streams.second){
        outfile <<"Teleport::\t"<< namefunc << ":\n";
        outfile << teleports;
    }
}
