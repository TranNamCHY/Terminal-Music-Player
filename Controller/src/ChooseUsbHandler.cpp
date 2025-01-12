#include "ChooseUsbHandler.h"

ChooseUsbHandler::ChooseUsbHandler() : model(Model::getInstance()) {
    this->changeHandelCallback = Controller::changeHandler;
}

ChooseUsbHandler* ChooseUsbHandler::getInstance() {
    static ChooseUsbHandler instance = ChooseUsbHandler();
    return &instance;
}

void ChooseUsbHandler::onStart(void* passData) {
    (void)passData;
    usbMonitor.setUserPath();
    usbPath = usbMonitor.getSubdirectories(usbMonitor.getUserPathValue());
    this->view.display(usbPath);
}

void ChooseUsbHandler::handle(std::string command) {
    // std::cout << "Vao handle cua chose USB" << std::endl;
    if (command == "z") {
        command = std::to_string(this->view.line % this->usbPath.size() + 1);
    }
    if (command == "r"){   
        this->reloadDisplay(command[1]- 48);
    } else {
        try {
            int cmdIndex = std::stoi(command);
            if (cmdIndex <= (int)usbPath.size() && cmdIndex > 0) {
                this->model.mediaManager.setActiveLibrary();
                std::string path_dir = usbPath[cmdIndex - 1];
                this->model.mediaManager.getLibrary().getSongFromPath(path_dir);
                std::cout << "Using path" << path_dir << std::endl;
                this->changeHandler(SongListHandler::getInstance());
            } else {
                std::cout << "No actions or Invalid command in chosing usb" << std::endl;
            }
        } catch (std::runtime_error& e) {
            std::cout << e.what() << std::endl;
        }
    }
}

void ChooseUsbHandler::leavePage() {
    // Định nghĩa hàm leavePage nếu cần, hoặc để trống nếu chưa sử dụng.
}

void ChooseUsbHandler::reloadDisplay(int line) {
    (void)line;
    // this->view.line = line;
    // usbMonitor.setUserPath();
    // usbPath = usbMonitor.getSubdirectories(usbMonitor.getUserPathValue());
    this->view.line ++;
    this->view.display(usbPath);
}
