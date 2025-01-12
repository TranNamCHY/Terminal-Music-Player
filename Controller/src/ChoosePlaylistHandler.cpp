#include "Handler.h"
#include "PlaylistView.h"
#include "Model.h"
#include <string>
#include <stack>
#include "Controller.h"
#include "ChoosePlaylistHandler.h"
#include "display.h"
#include "EditPlaylistHandler.h"
#include "Command.h"

ChoosePlaylistHandler::ChoosePlaylistHandler() : model(Model::getInstance()) {
    changeHandelCallback = SkeletonController::changeHandler;
};

ChoosePlaylistHandler* ChoosePlaylistHandler::getInstance() {
    static ChoosePlaylistHandler pl;
    return &pl;
}

void ChoosePlaylistHandler::onStart(void* passData) {
    (void)passData;
    vector<string> plists = this->model.mediaManager.getPlaylistNames();
    this->view.display(plists);
}

void ChoosePlaylistHandler::handle(string command) {
    if (command == "z") {
        command = to_string(this->view.line % this->model.mediaManager.getPlaylistNames().size() + 1);
    } 

    if (command == "r") {
        this->reloadDisplay(command[1]);
    } else {
        try {
            /* Clear cin buffer */
            // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (command == "c") {
                cout << "Enter name of new playlist: " << flush;
                // getline(cin, command);
                command = cmd.getCommand();
                this->model.mediaManager.createPlaylist(command);
                this->onStart();
            }
            else if (command == "d") {
                cout << "Choose index playlist to delete: " << flush;
                // cin >> command;
                command = cmd.getCommand();
                int plist_num = stoi(command);
                if (plist_num > 0) {
                    this->model.mediaManager.deletePlaylist(plist_num - 1);
                }
                this->onStart();
            }
            else {
                int plist_num = stoi(command);
                if (plist_num > 0) {
                    this->model.mediaManager.setActivePList(plist_num - 1);
                    changeHandler(EditPlaylistHandler::getInstance());
                }
            }
        } catch (const exception& e) {
            cout << "Pl Handler: No actions or Invalid command"  << endl;
        }
    }
}

void ChoosePlaylistHandler::reloadDisplay(int line) {
    (void)line;
    this->view.line ++;
    vector<string> plists = this->model.mediaManager.getPlaylistNames();
    this->view.display(plists);
}

vector<MultiType> ChoosePlaylistHandler::getGraphic(){
    vector<string> plists = this->model.mediaManager.getPlaylistNames();
    maxLine = plists.size();
    return this->view.display(plists);
}