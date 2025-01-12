#pragma once
#include "Handler.h"
#include "SongListView.h"
#include "Model.h"
#include "string"
#include "ExtraVariableType.h"
#include "ExtraVariableType.h"
class SongListHandler : public Handler {
private:
    SongListView view;
    Model& model;
    SongListHandler();
    static int currentPage;
    static int currentSongIndex;
    static int fullPage;
public:
    static SongListHandler* getInstance();
    vector<MultiType> getGraphic();
    void onStart(void* passData = nullptr);
    void handle(string command);
    void leavePage(){}  
    void reloadDisplay(int line);
};
