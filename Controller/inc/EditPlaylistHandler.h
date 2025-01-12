#pragma once
#include "Handler.h"
#include "EditPlaylistView.h"
#include "Model.h"
#include "string"

class EditPlaylistHandler : public Handler {
private:
    EditPlaylistView view;
    Model& model;
    EditPlaylistHandler();
public:
    static EditPlaylistHandler* getInstance();
    void onStart(void* passData = nullptr);
    void handle(string command);
    void reloadDisplay(int line);
};
