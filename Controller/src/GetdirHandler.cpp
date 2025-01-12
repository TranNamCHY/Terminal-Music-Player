#include "Handler.h"
#include "HomeView.h"
#include "Model.h"
#include "PlaylistHandler.h"
#include "Controller.h"
#include "GetdirHandler.h"
#include "SongListHandler.h"
#include "ChooseUsbHandler.h"
#include "Command.h"

// GetdirHandler* GetdirHandler::instancePtr = nullptr;
// GetdirHandler* GetdirHandler::instancePtr = nullptr;

GetdirHandler::GetdirHandler() : model(Model::getInstance()){
    changeHandelCallback = Controller::changeHandler;
}

GetdirHandler* GetdirHandler::getInstance() {
    static GetdirHandler in;
    return &in;
}

void GetdirHandler::setPath(string path) {
    view.path = path;
}

void GetdirHandler::setUsbPath(string path) {
    view.usbPath = path;
}

extern Command cmd;
void GetdirHandler::handle(string command) {
    if (command == "z") {
        command = std::to_string(this->view.line % 3 + 1);
    }

    if (command == "r") {   
        this->reloadDisplay(command[1]- 48);
    } else {
        try {
            if (command == "1") {
                if(usbmonitor.USBGetStatus()==1)    //da co USB
                {
                    usbmonitor.stopMonitoring();
                    // directory=usbmonitor.getUserPathValue();
                    changeHandler(ChooseUsbHandler::getInstance());
                    // this->model.mediaManager.setActiveLibrary();
                    // this->model.mediaManager.getLibrary().getSongFromPath(directory);
                    // changeHandler(SongListHandler::getInstance());
                }
                else
                {
                    //change_handler(GetdirHandler::getInstance());
                    cout << "Waiting for USB inserted..." << endl;
                    cout << "If USB inserted, press 1 again" << endl;
                    cout << "If USB not detected, remove and insert again" << endl;
                    changeHandler(ChooseUsbHandler::getInstance());
                }

            } else if (command == "2") {
                usbmonitor.stopMonitoring();
                cout <<"Input Directory: " << flush;
                // cin >> directory;
                directory = cmd.getCommand();
                setPath(directory);
                this->model.mediaManager.setActiveLibrary();
                this->model.mediaManager.getLibrary().getSongFromPath(directory);
                if (!this->model.mediaManager.getLibrary().isAlreadyInCurDirs(directory)) {
                    cout << "Do you wanna add this folder to recent dirs? [y/n]: " << flush;
                    string input;
                    // cin >> input;
                    directory = cmd.getCommand();
                    if (input == "y" || input == "Y") {
                        this->model.mediaManager.getLibrary().addPathToCurrentDirs(directory);
                    }
                }
                changeHandler(SongListHandler::getInstance());
            } else if (command == "3") {
                usbmonitor.stopMonitoring();
                this->model.mediaManager.setActiveLibrary();
                this->model.mediaManager.getLibrary().getSongFromPath(view.path);
                changeHandler(SongListHandler::getInstance());
            }
            else {
                cout << "No actions or Invalid command" << endl;
            }
        } catch (runtime_error& e) {
            cout << "Getdir: " << e.what() << endl;
        }
    }
}

void GetdirHandler::onStart(void* passData) {
    (void)passData;
    this->view.display();
    usbmonitor.stopMonitoring();
    usbmonitor.startMonitoring();
}

void GetdirHandler::reloadDisplay(int line) {
    (void)line;
    // this->view.line = line;
    this->view.line ++;
    this->view.display();
}