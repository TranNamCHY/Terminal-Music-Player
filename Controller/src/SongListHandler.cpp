#include "Handler.h"
#include "PlaylistView.h"
#include "Model.h"
#include <string>
#include <stack>
#include "Controller.h"
#include "SongListHandler.h"
#include "display.h"
#include "PlayHandler.h"
#include "commonFunc.h"
#include "SkeletonController.h"
int SongListHandler::currentPage = 0;
int SongListHandler::currentSongIndex = 0;

SongListHandler::SongListHandler() : model(Model::getInstance()) {
    changeHandelCallback = SkeletonController::changeHandler;
};

SongListHandler* SongListHandler::getInstance() {
    static SongListHandler pl;
    return &pl;
}

void SongListHandler::onStart(void* passData) {
    (void)passData;
    vector<Song> songs = this->model.mediaManager.getCurPageOfSong();
    this->view.displaySongs(songs, 
        this->model.mediaManager.getCurPageOfSongIndex(), 
        this->model.mediaManager.getNumberofSong());
    SongListHandler::currentPage = this->model.mediaManager.getCurPageOfSongIndex();
}

void SongListHandler::handle(string command) {
    if(command == "z") {
        int ln = this->view.line % this->model.mediaManager.getCurPageOfSong().size() + 1 + (MAX_LINES * this->model.mediaManager.getCurPageOfSongIndex());
        // command = to_string(this->view.line % this->model.mediaManager.getNumberofSong() + 1 + MAX_LINES * SongListHandler::currentPage);
        command = to_string(ln);
    }

    if (command == "r") {   
        this->reloadDisplay(command[1]);
    } else {
        try {
            if (songListhandle(command, SongListHandler::currentPage)) {
                this->view.displayBottom();
            } 
            else {
                int selectedSong = stoi(command);
                if (selectedSong >= 1 && selectedSong <= this->model.mediaManager.getNumberofSong()) {
                    SongListHandler::currentSongIndex = selectedSong;
                    this->changeHandler(PlayHandler::getInstance(), (void*)&SongListHandler::currentSongIndex);
                }
            }
        } catch (out_of_range &e) {
            cout << "SongList: " << e.what() << endl;
        } catch (exception& e) {
            cout << "SongList: No actions or Invalid command" << endl;
        }
    }
};

void SongListHandler::reloadDisplay(int line) {
    // this->view.line = line;
    (void)line;
    this->view.line ++;
    vector<Song> songs = this->model.mediaManager.getCurPageOfSong();
    this->view.displaySongs(songs, 
    this->model.mediaManager.getCurPageOfSongIndex(), 
    this->model.mediaManager.getNumberofSong());
    SongListHandler::currentPage = this->model.mediaManager.getCurPageOfSongIndex();
}

vector<MultiType> SongListHandler::getGraphic(){
    maxLine = this->model.mediaManager.getNumberofSong();
    vector<Song> songs = this->model.mediaManager.getCurPageOfSong();
    SongListHandler::currentPage = this->model.mediaManager.getCurPageOfSongIndex();
    return this->view.displaySongs(songs, 
    this->model.mediaManager.getCurPageOfSongIndex(), 
    this->model.mediaManager.getNumberofSong());
}