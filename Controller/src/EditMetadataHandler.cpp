#include "EditMetadataHandler.h"
#include "Handler.h"
#include "HomeView.h"
#include "Model.h"
#include "PlaylistHandler.h"
#include "Controller.h"
#include "EditMetadataHandler.h"
#include "SongListHandler.h"
#include "PlayHandler.h"
#include "Command.h"
#include <algorithm>
#include <cctype>
#include <string>
#include <limits>

EditMetadataHandler* EditMetadataHandler::instancePtr = nullptr;

EditMetadataHandler::EditMetadataHandler() : model(Model::getInstance()){
    changeHandelCallback = Controller::changeHandler;
}

EditMetadataHandler* EditMetadataHandler::getInstance() {
    if (instancePtr == nullptr) {
        EditMetadataHandler* instancePtr = new EditMetadataHandler();
        return instancePtr;
    } else {
        return instancePtr;
    }
}

void EditMetadataHandler::handle(string command) {
    if (command == "z") {
        command = std::to_string(this->view.line % 4 + 1) ;
    }
    if (command == "r") {    
        this->reloadDisplay(command[1]);
    } else {
        try {
            int option = stoi(command);
            std::string input;
            /* Clear cin buffer */
            // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            switch (option) {
                case 1:
                    cout << "Input new Title: " << flush;
                    // std::getline(std::cin, input);
                    input = cmd.getCommand();
                    this->model.mediaManager.getCurSong().setTitle(input);
                    break;
                case 2:
                    cout << "Input new Artist: " << flush;
                    // std::getline(std::cin, input);
                    input = cmd.getCommand();
                    this->model.mediaManager.getCurSong().setArtist(input);
                    break;
                case 3:
                    cout << "Input new Album: " << flush;
                    // std::getline(std::cin, input);
                    input = cmd.getCommand();
                    this->model.mediaManager.getCurSong().setAlbum(input);
                    break;
                case 4:
                    cout << "Input new Year: " << flush;
                    // std::getline(std::cin, input);
                    input = cmd.getCommand();
                    this->model.mediaManager.getCurSong().setYear(stoi(input));
                    break;
                default:
                    break;
            }
        this->onStart();
        } catch (runtime_error& e) {
            cout << "Editmetadata: "<< e.what() << endl;
        }
    }
}

void EditMetadataHandler::onStart(void* passData) {
    (void)passData;
    Song currentSong = this->model.mediaManager.getCurSong();
    this->view.display(currentSong);
}

void EditMetadataHandler::reloadDisplay(int line) {
    (void)line;
    // this->view.line = line;
    this->view.line ++;
    Song currentSong = this->model.mediaManager.getCurSong();
    this->view.display(currentSong);
}
