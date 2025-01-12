#pragma once
#include "Handler.h"
#include "HomeView.h"
#include "Model.h"
#include <string>
#include "ExtraVariableType.h"
#include <vector>
#include "View.h"
#include "SkeletonController.h"
class HomeHandler : public Handler {
private:
    // view handle UI
    // Model handle backend
    Model& model;
    HomeHandler();
    static HomeHandler* instancePtr;
public:
    vector<MultiType> getGraphic();
    static HomeHandler* getInstance();
    void handle(string command);
    void onStart(void* passData = nullptr);
    void leavePage(){}
    void reloadDisplay(int line); 
    int getMaxLine();
};