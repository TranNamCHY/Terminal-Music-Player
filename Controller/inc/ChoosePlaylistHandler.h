#pragma once
#include "Handler.h"
#include "CreatePlaylistView.h"
#include "Model.h"
#include "string"
#include "SkeletonController.h"
class ChoosePlaylistHandler : public Handler {
private:
    CreatePlaylistView view;
    Model& model;
    ChoosePlaylistHandler();
public:
    static ChoosePlaylistHandler* getInstance();
    void onStart(void* passData = nullptr);
    void handle(string command);
    void reloadDisplay(int line);
    vector<MultiType> getGraphic();
};
