#pragma once
#include "Handler.h"
#include "PlaylistView.h"
#include "Model.h"
#include "string"
#include "ExtraVariableType.h"
class PlaylistHandler : public Handler {
private:
    PlaylistView view;
    Model& model;
    PlaylistHandler();
public:
    vector<MultiType> getGraphic();
    static PlaylistHandler* getInstance();
    void onStart(void* passData = nullptr);
    void handle(string command);
    void leavePage(){} 
    void reloadDisplay(int line);
};
