#include "Handler.h"
#include "PlaylistView.h"
#include "Model.h"
#include <string>
#include <stack>
#include "Controller.h"
#include "ChooseSongsHandler.h"
#include "display.h"
#include "PlayHandler.h"
#include "commonFunc.h"
#include "Playlist.h"
#include "EditPlaylistHandler.h"
#include "Command.h"

int ChooseSongsHandler::currentPage = 0;
ChooseSongsHandler::ChooseSongsHandler() : model(Model::getInstance()) {
    changeHandelCallback = Controller::changeHandler;
    popCallback = Controller::PopHandler;
};

ChooseSongsHandler* ChooseSongsHandler::getInstance() {
    static ChooseSongsHandler pl;
    return &pl;
}

void ChooseSongsHandler::onStart(void* passData) {
    (void)passData;
    // this->model.mediaManager.setActiveLibrary();
    vector<Song> songs = this->model.mediaManager.getPageOfSong(0);
    ChooseSongsHandler::currentPage = 0;
    this->view.displaySongs(songs, 0, this->model.mediaManager.getNumberofSong());
}

void ChooseSongsHandler::handle(string command) {
    try {
        /* Clear cin buffer */
        // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (songListhandle(command, ChooseSongsHandler::currentPage)) {
            this->view.displayBottom();
        } else {
            // cout << "Choose index to add to playlist. Press \"d\" to done adding" << endl;
            // if(command == GO_BACK) {
            //     this->model.mediaManager.setActivePList(this->model.mediaManager.getActivePListIndex());
            //     this->selfPop();
            // }
            // else {
                int pos = stoi(command) - 1;
                Song& song = (*this->model.mediaManager.getCurSongList())[pos];
                this->model.mediaManager.getActivePlaylist().addSong(song.getPath());
                cout << "Song added: " << song.getTitle() << endl;
            // }
        }
    } catch (out_of_range &e) {
        cout << "Choose song error: " << e.what() << endl;
    } catch (runtime_error& e) {
        cout << "Choose song error: " << e.what() << endl;
    }
};

void ChooseSongsHandler::leavePage() {
    this->model.mediaManager.setActivePList(this->model.mediaManager.getActivePListIndex());
    this->selfPop();
}