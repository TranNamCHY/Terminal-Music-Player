#include <iostream>
#include <filesystem>
#include <typeinfo> // For typeid
#include "HomeView.h"
#include <termios.h>
#include <type_traits>
#include <sstream> // Required for std::ostringstream
#include <iomanip> // Required for std::left and std::setw
#include <unistd.h>
#include "SkeletonController.h"
#include "PlayHandler.h"
#include "HomeHandler.h"
#include "PlaylistHandler.h"
#include  "ChoosePlaylistHandler.h"
#include "SongListHandler.h"
using namespace std;
SkeletonController* SkeletonController::instance = nullptr; 
Handler* SkeletonController::currentHandler = nullptr;
Handler* SkeletonController::previousHandler = nullptr;
SkeletonController* SkeletonController::getInstance(){
    if(SkeletonController::instance == nullptr){
        instance =  new SkeletonController();
        instance->SetHandler(HomeHandler::getInstance());
    }
    return instance;
    /* if(instance == nullptr){
        instance = new SkeletonController();
        instance->SetHandler(HomeHandler::getInstance());
    } */
}
void SkeletonController::changeHandler(Handler* handler,void* trashPara){
    SkeletonController::getInstance()->CurrLine = 1;
    SkeletonController::getInstance()->InputCmd = std::to_string(SkeletonController::getInstance()->CurrLine);
    previousHandler = currentHandler;
    currentHandler = handler;
    previousHandler->leavePage();
    currentHandler->onStart(trashPara);
}
void SkeletonController::backward(){
    SkeletonController::getInstance()->CurrLine = 1;
    InputCmd = std::to_string(CurrLine);
    if(typeid(*currentHandler) ==  typeid(PlaylistHandler)){
        changeHandler(HomeHandler::getInstance(), nullptr);
        DisplayList = currentHandler->getGraphic();
    }
    if(typeid(*currentHandler) ==  typeid(SongListHandler) & 
    (typeid(previousHandler) == typeid(PlayHandler) || typeid(previousHandler) == typeid(PlaylistHandler))){
        changeHandler(PlaylistHandler::getInstance(), nullptr);
        DisplayList = currentHandler->getGraphic();
    }
    else {
        changeHandler(HomeHandler::getInstance(), nullptr);
        DisplayList = currentHandler->getGraphic();   
    }
    if(typeid(*currentHandler) ==  typeid(PlayHandler)){
        changeHandler(SongListHandler::getInstance(), nullptr);
        DisplayList = currentHandler->getGraphic();
    }
}
void SkeletonController::SetHandler(Handler* handler){
    SkeletonController::getInstance()->CurrLine = 1; 
    instance->InputCmd = to_string(CurrLine);
    SkeletonController::currentHandler = handler;
    DisplayList = currentHandler->getGraphic();
    redisplay();
}
void SkeletonController::decreaseCurrLine(){
    if(SkeletonController::getInstance()->CurrLine > 1)
        SkeletonController::getInstance()->CurrLine-=1;
    else
        SkeletonController::getInstance()->CurrLine = currentHandler->getMaxLine();
    this->InputCmd = to_string(SkeletonController::getInstance()->CurrLine);
}
void SkeletonController::increaseCurrLine(){
    if(this->SkeletonController::getInstance()->CurrLine == currentHandler->getMaxLine())
        SkeletonController::getInstance()->CurrLine =  1;
    else 
        SkeletonController::getInstance()->CurrLine++;
    this->InputCmd = to_string(SkeletonController::getInstance()->CurrLine);
}
void SkeletonController::GetInputCmd(){
    enableRawMode();
    char c;
    while (true) {
        read(STDIN_FILENO, &c, 1); // Read one character
        if(c == '\n' || c == '>'){
        too_lazy:
            //cout << "Test: " << this->InputCmd;
            currentHandler->handle(this->InputCmd);
            DisplayList = currentHandler->getGraphic();
            system("clear");
            redisplay();
        }
        if (c == 'q') break;
        if (c == 27){
            read(STDIN_FILENO, &c, 1);
            if(c == 91){
                read(STDIN_FILENO, &c, 1);
                    switch (c) {
                        case 65: // Up arrow
                            this->decreaseCurrLine();
                            redisplay();
                            //std::cout << "Up Arrow Pressed\n";
                            break;
                        case 66: // Down arrow
                            this->increaseCurrLine();
                            redisplay();
                            //std::cout << "Down Arrow Pressed\n";
                            break;
                        case 67: // Right arrow
                            //std::cout << "Right Arrow Pressed\n";
                            goto too_lazy;
                            break;
                        case 68: // Left arrow
                            backward();
                            redisplay();
                            break;
                        default:
                            //std::cout << "Unknown key\n";
                            break;
                }   
            }
        }
        if(c == 'd'){
            InputCmd = "d";
            this->currentHandler->handle(InputCmd);
        }
        /* if (c == '\e') { // Escape character (27)
            char seq[2];
            if (read(STDIN_FILENO, &seq[0], 1) == 1 && read(STDIN_FILENO, &seq[1], 1) == 1) {
                if (seq[0] == '[') {
                    if (seq[1] == 'A') {
                        this->decreaseCurrLine();
                        redisplay();
                        //cout << "Tedt" <<  endl;
                        //cout << CurrLine << endl;
                    } else if (seq[1] == 'B') {
                        this->increaseCurrLine();
                        redisplay();
                        //cout << CurrLine << endl;
                    }
                }
            }
        }
        if (c == 224) { // Escape character (27)
            read(STDIN_FILENO, &c, 1);
                    if (c == 75) {
                        backward();
                        redisplay();
                        //cout << "Tedt" <<  endl;
                        //cout << CurrLine << endl;
                    } else if (c == 77) {
                        goto too_lazy;
                        //cout << CurrLine << endl;
                    }
        } */        
    } 
    disableRawMode();
}

void SkeletonController::display(){
    std::cout << "\033[2J\033[1;1H";
    int temptCurrLine = SkeletonController::getInstance()->CurrLine;
    // Iterate through the vector
    for (const auto& item : DisplayList) {
        // Use std::visit to handle different types
        std::visit([temptCurrLine](const auto& value) {
            int idex = 1;
            if constexpr (std::is_same_v<decltype(value), const std::string&>) {
                std::cout << value << endl;
            } else if constexpr (std::is_same_v<decltype(value), const std::vector<std::string>&>) {
                for (const auto& str : value) {
                    if(idex == temptCurrLine)
                        //std::cout << View::highlightLine(str) << endl;
                        View::highlightLine(str);
                    else
                        if(typeid(*currentHandler) !=  typeid(PlayHandler))
                            std::cout << str << endl;
                        else
                            std::cout << str;
                    idex++;
                }
            }
        }, item);
    }
}

/* std::string test(vector<string> value){
    std::ostringstream oss;
    int idex = 1;
    int temptCurrLine = CurrLine; 
    tempt = "";
    for (const auto& str : value) {
        if(idex == temptCurrLine)
            //std::cout << View::highlightLine(str) << endl;
            oss << "\033[30;47m"
                << std::setw(WIDTH) << std::left << str
                << "\033[0m" << std::endl;
        else
            std::cout << str << endl;
            idex++;
        }
} */
void SkeletonController::redisplay(){
    //system("clear");
    std::cout << "\033[2J\033[1;1H";
    int temptCurrLine = CurrLine;
    // Iterate through the vector
    for (const auto& item : DisplayList) {
        // Use std::visit to handle different types
        std::visit([temptCurrLine](const auto& value) {
            int idex = 1;
            if constexpr (std::is_same_v<decltype(value), const std::string&>) {
                std::cout << value << endl;
            } else if constexpr (std::is_same_v<decltype(value), const std::vector<std::string>&>) {
                for (const auto& str : value) {
                    if(idex == temptCurrLine){
                        //std::cout << View::highlightLine(str) << endl;
                        if(typeid(*currentHandler) !=  typeid(PlayHandler))
                            View::highlightLine(str);
                            //cout << endl;
                        else
                            View::highlightObj(View::alignLeft(str, ' ', WIDTH/4));
                    }
                    else
                        if(typeid(*currentHandler) !=  typeid(PlayHandler))
                            std::cout << str << endl;
                        else
                            std::cout << str;
                    idex++;
                }
            }
        }, item);
    }
}
void SkeletonController::run(){
    GetInputCmd();  
}
void SkeletonController::enableRawMode() {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw); // Get current terminal settings
    raw.c_lflag &= ~(ECHO | ICANON); // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); // Apply settings
}

void SkeletonController::disableRawMode() {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag |= (ECHO | ICANON); // Re-enable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); // Apply settings
}
