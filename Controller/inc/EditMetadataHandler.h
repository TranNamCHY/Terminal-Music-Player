#pragma once
#include "Handler.h"
#include "EditMetadataView.h"
#include "Model.h"
#include <string>

class EditMetadataHandler : public Handler {
private:
    EditMetadataView view;
    Model& model;
    EditMetadataHandler();
    static EditMetadataHandler* instancePtr;
public:
    static EditMetadataHandler* getInstance();
    void handle(string command);
    void onStart(void* passData = nullptr);
    void leavePage(){}
    void reloadDisplay(int line);
};