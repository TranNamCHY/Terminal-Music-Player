#pragma once
#include <iostream>
#include <functional>
#include "View.h"
// #include "Controller.h"

using namespace std;

/// @brief Handle all possible command that are include in a coresponding view
class Handler {
protected:
    /// @brief Call back function to change to other view
    function<void(Handler*, void*)> changeHandelCallback;

    /// @brief Callback function to pop back itselt from Hanler list
    function<void(void*)> popCallback;
public:
    View* view;
    /// @brief Handler all possible command in a corresponding view
    /// @param command string command that user type
    virtual void handle(string command) = 0;

    /// @brief define what is displayed when switching to this handler  
    /// @param passData data that previous handler give
    virtual void onStart(void* passData = nullptr) = 0;

    /// @brief things to do before leave this handler (to previous/next handler by navigation options, for example)
    virtual void leavePage();

    /// @brief change current handler
    /// @param handler new handler
    /// @param passData data passed tho the new hanler
    void changeHandler(Handler* handler, void* passData = nullptr);

    /// @brief pop itselft form current handlersc
    /// @param passData data passed for previous handler, which become ative
    void selfPop(void* passData = nullptr);


    /// @brief What handler need to done before leave program
    /// @return 0 if OK
    virtual int exit();

    virtual void reloadDisplay(int line);
    virtual vector<MultiType> getGraphic(){}
    int getMaxLine();
    int maxLine;
};
