#pragma once
#include "Handler.h"
#include "GetdirView.h"
#include "Model.h"
#include <string>
#include <iostream>
#include <USBDetect.h>

class GetdirHandler : public Handler {
private:
    GetdirView view;
    Model& model;
    GetdirHandler();
    std::string directory;
    USBMonitor usbmonitor;
public:
    static GetdirHandler* getInstance();
    void handle(string command);
    void onStart(void* passData = nullptr);
    void setPath(string path);
    void setUsbPath(string path);
    void leavePage(){}
    void reloadDisplay(int line);
};