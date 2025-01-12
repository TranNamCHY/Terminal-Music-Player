#pragma once
#include "Handler.h"
#include "Model.h"
#include "string"
#include "USBDetect.h"
#include "HomeView.h"
#include "Controller.h"
#include "ChooseUsbView.h"
#include "SongListHandler.h"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <MusicPlayer.h>

class ChooseUsbHandler : public Handler {
private:
    ChooseUsbView view;
    USBMonitor usbMonitor;
    MusicPlayer musicPlayer;
    Model& model;
    std::vector<std::string> usbPath;

    // Private constructor
    ChooseUsbHandler();

public:
    static ChooseUsbHandler* getInstance();

    void onStart(void* passData = nullptr) override;

    void handle(std::string command);

    void leavePage();

    void reloadDisplay(int line);
};
