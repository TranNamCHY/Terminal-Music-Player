#pragma once
#include <iostream>
#include <filesystem>
#include "HomeView.h"
#include <termios.h>
#include <unistd.h>
#include <vector>
#include "Handler.h"
#include "ExtraVariableType.h"
#include "View.h"
using namespace std;
class SkeletonController {
    public:
        static SkeletonController* getInstance();
        static void changeHandler(Handler* handler, void* trashPara);
        //SkeletonController(const SkeletonController&  obj) = delete;
        void SetHandler(Handler* handler);
        void run();
        void decreaseCurrLine();
        void increaseCurrLine();
        void GetInputCmd();
        void display();
        void redisplay();
        static Handler* currentHandler;
        static Handler* previousHandler;
    private:
        static SkeletonController* instance;
        void backward();
        string InputCmd;
        int CurrLine;
        vector<MultiType> DisplayList;
        SkeletonController(){}
        void enableRawMode();
        void disableRawMode();
};