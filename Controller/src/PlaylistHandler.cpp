#include "Handler.h"
#include "PlaylistView.h"
#include "Model.h"
#include <string>
#include <stack>
#include "Controller.h"
#include "PlaylistHandler.h"
#include "display.h"
#include "SongListHandler.h"
#include "SkeletonController.h"
PlaylistHandler::PlaylistHandler() : model(Model::getInstance()) {
    changeHandelCallback = SkeletonController::changeHandler;
};

PlaylistHandler* PlaylistHandler::getInstance() {
    static PlaylistHandler pl;
    pl.maxLine = 2;
    return &pl;
}

void PlaylistHandler::onStart(void* passData) {
    (void)passData;
    vector<string> plists = this->model.mediaManager.getPlaylistNames();
    this->view.display(plists);
}

void PlaylistHandler::handle(string command) {
    if(command == "z") {
        command = to_string(this->view.line % this->model.mediaManager.getPlaylistNames().size() + 1);
    }

    if (command == "r") {
        this->reloadDisplay(command[1]);
    } else {
        try {
            int plist_num = stoi(command);
            if (plist_num > 0) {
                this->model.mediaManager.setActivePList(plist_num - 1);
                changeHandler(SongListHandler::getInstance());
            }
        } catch (const exception& e) {
            cout << "Pl Handler: No actions or Invalid command" << endl;
        }
    }
}

void PlaylistHandler::reloadDisplay(int line) {
    (void)line;
    // this->view.line = line;
    this->view.line ++;
    vector<string> plists = this->model.mediaManager.getPlaylistNames();
    this->view.display(plists);   
};

vector<MultiType> PlaylistHandler::getGraphic(){
    //(void)line;
    // this->view.line = line;
    //this->view.line ++;
    vector<string> plists = this->model.mediaManager.getPlaylistNames();
    this->view.display(plists);
    return this->view.display(plists);
}
