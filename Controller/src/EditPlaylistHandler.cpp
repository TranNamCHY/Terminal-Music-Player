#include "Handler.h"
#include "PlaylistView.h"
#include "Model.h"
#include <string>
#include <stack>
#include "Controller.h"
#include "EditPlaylistHandler.h"
#include "display.h"
#include "PlayHandler.h"
#include "commonFunc.h"
#include "ChooseSongsHandler.h"
#include "Command.h"

EditPlaylistHandler::EditPlaylistHandler() : model(Model::getInstance()) {
    changeHandelCallback = Controller::changeHandler;
    popCallback = Controller::PopHandler;
};

EditPlaylistHandler* EditPlaylistHandler::getInstance() {
    static EditPlaylistHandler pl;
    return &pl;
}

void EditPlaylistHandler::onStart(void* passData) {
    (void)passData;
    try {
        vector<Song> songs = this->model.mediaManager.getPageOfSong(0);
        this->view.displaySongs(songs, 0, this->model.mediaManager.getNumberofSong());
    } catch (out_of_range& e) {
        cout << e.what() << endl;
    }
}

void EditPlaylistHandler::handle(string command) {
    static int currentPage = 0;
    if (command == "z") {
        command = to_string(this->view.line % 4 + 1);
    }

    if (command == "r") {
        this->reloadDisplay(command[1]);
    } else {
        try {
            if (songListhandle(command, currentPage)) {
                this->view.displayBottom();
            } else {
                int option = stoi(command);
                std::string input;
                /* Clear cin buffer */
                // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                Playlist& pl = this->model.mediaManager.getActivePlaylist();
                switch (option)
                {
                case 1:
                    cout << "Input new Name: " << flush;
                    // std::getline(std::cin, input);
                    input = cmd.getCommand();
                    pl.rename(input);
                    this->onStart();
                    break;
                case 2:
                    if (!this->model.mediaManager.getLibrary().isSongFetched()) {
                        this->model.mediaManager.getLibrary().getSongFromCurrentDirs();
                    }
                    this->model.mediaManager.setActiveLibrary();
                    changeHandler(ChooseSongsHandler::getInstance(), (void*)&pl);
                    break;
                case 3:
                    cout << "Input path to your folder: " << flush;
                    // std::getline(std::cin, input);
                    input = cmd.getCommand();
                    this->model.mediaManager.setActiveLibrary();
                    this->model.mediaManager.getLibrary().getSongFromPath(input);
                    changeHandler(ChooseSongsHandler::getInstance(), (void*)&pl);
                    break;
                case 4:
                    cout << "Input song index: " << flush;
                    // std::getline(std::cin, input);
                    input = cmd.getCommand();
                    pl.deleteSong(stoi(input) - 1);
                    this->onStart();
                    break;
                default:
                    break;
                }
            }
        } catch (out_of_range &e) {
            cout << "Edit Plist:" << e.what() << endl;
        } catch (runtime_error& e) {
            cout << "Edit Plist:" << e.what() << endl;
        } catch (const exception& e) {
            cout << "Edit Plist: No actions or Invalid command" << endl;
        }
    }
};

void EditPlaylistHandler::reloadDisplay(int line) {
    (void)line;
    this->view.line ++;
    try {
        vector<Song> songs = this->model.mediaManager.getPageOfSong(0);
        this->view.displaySongs(songs, 0, this->model.mediaManager.getNumberofSong());
    } catch (out_of_range& e) {
        cout << e.what() << endl;
    }
}
