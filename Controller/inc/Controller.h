#pragma once
#include "Model.h"
#include "Handler.h"
#include "Command.h"
#include <deque>
#include "Command.h"

extern Command cmd;
/// @brief Get user command, manage handlers so that there is a coresponding handler run at a time
class Controller {
private:
    static Model& model;
    static int view_index;
    static deque<Handler*> recentView;
public:
    // static Command cmd;

    Controller();

    /// @brief Pop current handler and return back to previous view
    /// @param paras parameter that current poped view send for previous view 
    static void PopHandler(void* paras = nullptr);


    /// @brief Add new handler and switch view to the new handler's view.
    /// The new handler will then take care of handling input commands 
    /// @param handler new handler
    /// @param paras parameters passed for the new handler
    static void changeHandler(Handler* handler, void* paras = nullptr);

    /// @brief function call before exit program. For update databse, for example.
    /// @return 0 if OK
    int exit();

    /// @brief This function run forever to get input command and pass the command to active handler at that time.
    void run();

    // static void getPort();
    // static void configPort();
    // static void closePort();
    // void readPort();
    // void checkPort();

    // std::thread portThread; // Thêm biến thread cho portProgress
    // std::atomic<bool> running; // Thêm biến atomic để dừng portThread
    // std::mutex mtx; // Thêm mutex để đảm bảo an toàn trong multi-threading
};