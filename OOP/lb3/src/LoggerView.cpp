//
// Created by Любава on 12.11.2021.
//

#include "LoggerView.h"
LoggerView::LoggerView(){}
void LoggerView::PrintWarning() {
    std::cout << "Oh no, file could not be opened for writing!" << std::endl;
    std::cout << "So, the entry is redirected to the console." << std::endl;
}
char LoggerView::SelectStream(){
    char select_stream;
    std::cout << "Please select a stream.\nPress 0 to select console output;\n"
                 "Press 1 to select writing to file;\nPress 2 to select both ways." << std::endl;
    std::cin >> select_stream;
    return select_stream;
}
LoggerView::~LoggerView(){
}