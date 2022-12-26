
#include "Logger.h"
#include "../Moving_objects/Player.h"
#include "../Views/LoggerView.h"
#include "../Gaming_Space/Cellule.h"
#include "../Moving_objects/Enemy.h"
#include "../Gaming_Space/Field.h"
//#include "Game.h"
#include "../Static_Items/Heal.h"
#include "../Static_Items/Box.h"
#include "../Static_Items/Teleport.h"
Logger::Logger(IObservable& address) {
    if (!outfile.is_open()) outfile.open("Testing/Logging/Logging.txt");
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
            <<"\nNext step:\t on x:  " << monster.GetStep().x << "\ton y: " << monster.GetStep().y
        <<"\nShould the battle continue:\t"<<monster.GetGoing() << "\nAn array of monster vulnerabilities:";
    for (int i = 0; i < enemy_limbs_count; i++)
        out << "\n"<< monster.GetLimb(i) <<" ";
    out << std::endl<< std::endl;
    return out;
}
std::ostream& operator<< (std::ostream &out, Cellule &cell)
{
    out << "Type of cell:\t" << cell.GetType() <<"\nCell coordinate:\tx  "<<cell.GetPoint().x
        << "\ty: " <<cell.GetPoint().y << "\nType of object:\t" <<std::endl
          <<"Address of the object:"<<cell.GetObj()  <<std::endl << std::endl;
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

}
std::ostream& operator<< (std::ostream &out, Heal &food)
{
    out << "Type:\t" << food.GetObject() << std::endl <<
    "Is the item disappearing:\t"<< food.remove() <<std::endl<< std::endl;
    return out;
}
std::ostream& operator<< (std::ostream &out,  Box &inbox)
{
    out << "Type:\t" << inbox.GetObject() << "\nFull:\t" << inbox.GetFull()<<std::endl<<
    "Is the item disappearing:\t"<< inbox.remove() <<std::endl<< std::endl;
    return out;
}
std::ostream& operator<< (std::ostream &out, Teleport &teleports)
{
    out << "Type:\t" << teleports.GetObject() << "\nFirst teleport coordination:\tx:  "
        << teleports.GetFirstPlace().x<< "\ty: " << teleports.GetSecondPlace().y<<std::endl<<
         "Is the item disappearing:\t"<< teleports.remove() <<
       std::endl<< std::endl;
    return out;
}
void Logger::update(Player &person, std::string namefunc){
    if (streams.first) {
        std::cout <<"Player::\t" << namefunc << ":\n";
        std::cout << person;
    }
    if (streams.second){
        outfile <<"Player::\t"<< namefunc << ":\n";
        outfile << person;
    }
}
void Logger::update(Enemy &monster,std::string namefunc) {
    if (streams.first) {
        std::cout <<"Enemy::\t"<< namefunc << ":\n";
        std::cout << monster;
    }
    if (streams.second){
        outfile <<"Enemy::\t"<< namefunc << ":\n";
        outfile << monster;
    }
}
void Logger::update(Cellule &cell, std::string namefunc) {
    if (streams.first) {
        std::cout <<"Cellule::\t"<< namefunc << ":\n";
        std::cout << cell;
    }
    if (streams.second){
        outfile <<"Cellule::\t"<< namefunc << ":\n";
        outfile << cell;
    }
}
void Logger::update(Field &fieldgame, std::string namefunc) {
    if (streams.first) {
        std::cout <<"Field::\t"<< namefunc << ":\n";
        std::cout << fieldgame;
    }
    if (streams.second){
        outfile <<"Field::\t"<< namefunc << ":\n";
        outfile << fieldgame;
    }
}
void Logger::update(Heal &food, std::string namefunc){
    if (streams.first) {
        std::cout <<"Heal::\t"<< namefunc << ":\n";
        std::cout << food;
    }
    if (streams.second){
        outfile <<"Heal::\t"<< namefunc << ":\n";
        outfile << food;
    }
}
void Logger::update(Box &inbox,std::string namefunc) {
    if (streams.first) {
        std::cout <<"Box::\t"<< namefunc << ":\n";
        std::cout << inbox;
    }
    if (streams.second){
        outfile <<"Box::\t"<< namefunc << ":\n";
        outfile << inbox;
    }
}
void Logger::update(Teleport &teleports, std::string namefunc) {
    if (streams.first) {
        std::cout <<"Teleport::\t"<< namefunc << ":\n";
        std::cout << teleports;
    }
    if (streams.second){
        outfile <<"Teleport::\t"<< namefunc << ":\n";
        outfile << teleports;
    }
}
