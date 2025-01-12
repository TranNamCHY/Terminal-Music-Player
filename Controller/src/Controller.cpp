#include <vector>
#include <stack>
#include <string>
#include "Controller.h"
#include "Handler.h"
#include "PlaylistHandler.h"
#include "MusicPlayer.h"
#include <USBDetect.h>
#include "HomeHandler.h"
#include "Model.h"
#include "display.h"
#include "Command.h"

Model& Controller::model = Model::getInstance();
deque<Handler*> Controller::recentView;
int Controller::view_index = 0;

Controller::Controller() {
    Controller::recentView.push_back(HomeHandler::getInstance());
    Controller::recentView[view_index]->onStart();
}

void Controller::PopHandler(void* paras) {
    recentView.pop_back();
    recentView[view_index]->onStart(paras);
}

void Controller::changeHandler(Handler* handler, void* paras) {
    while (recentView.size() > MAX_HISTORY_PAGE - 1)
    {
        recentView.pop_front();
        view_index--;
    }
    int temp = view_index;
    while ((long unsigned int)temp < recentView.size() - 1)
    {
        recentView.pop_back();
    }

    Controller::recentView.push_back(handler);
    recentView[view_index]->leavePage();
    view_index++;
    recentView[view_index]->onStart(paras);
}

int Controller::exit() {
    this->model.mediaManager.updateDatabase();
    // running = false;
    // Controller::closePort();
    return 0;
}
Command cmd;

void Controller::run() {
    // Controller::configPort();
    // running = true;
    // portThread = std::thread(&Controller::checkPort, this); // Bắt đầu thread cho checkPort
    // portThread.detach();

    string command;
    cmd.listen();
    // Command cmd;
    while (true) {
        // cin >> command;
        // cout << endl;
        command = cmd.getCommand();
        // command = Controller::cmd.getCommand();
        if (command == GO_BACK) {
            if (view_index >= 1) {
                recentView[view_index]->leavePage();
                view_index--;
                recentView[view_index]->onStart();
            }
        } else if (command == FORWARD) {
            if (recentView.size() - 1  > (long unsigned int)view_index) {
                recentView[view_index]->leavePage();
                view_index++;
                recentView[view_index]->onStart();
            }
        } else if (command == EXIT) {
            for(Handler* e : recentView) {
                e->exit();
            }
            this->exit();
            // cmd.~Command();
            std::exit(0);
        } else if(command == HOME) {
            Controller::changeHandler(HomeHandler::getInstance());
        } else {
            Controller::recentView[view_index]->handle(command);
        }
    }
}

// void Controller::getPort() {
//     int serialPort = open("/dev/ttyACM0", O_RDWR);
// }

// void Controller::configPort() {
//     int serialPort = open("/dev/ttyACM0", O_RDWR);
//     // Kiểm tra lỗi
//     if (serialPort < 0) {
//         std::cerr << "Error " << errno << " opening " << "/dev/ttyACM0" << ": " << strerror(errno) << std::endl;
//         return;
//     }

//     struct termios tty;
//     if(tcgetattr(serialPort, &tty) != 0) {
//         std::cerr << "Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;
//         std::exit(1);
//     }

//     cfsetispeed(&tty, B115200);
//     cfsetospeed(&tty, B115200);

//     tty.c_cflag &= ~PARENB; // No parity
//     tty.c_cflag &= ~CSTOPB; // 1 stop bit
//     tty.c_cflag &= ~CSIZE;
//     tty.c_cflag |= CS8; // 8 bits per byte
//     tty.c_cflag &= ~CRTSCTS; // No hardware flow control
//     tty.c_cflag |= CREAD | CLOCAL; // Enable receiver, ignore modem control lines

//     tty.c_lflag &= ~ICANON;
//     tty.c_lflag &= ~ECHO; // Disable echo
//     tty.c_lflag &= ~ECHOE; // Disable erasure
//     tty.c_lflag &= ~ECHONL; // Disable new-line echo
//     tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP

//     tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
//     tty.c_iflag &= ~(ICRNL | INLCR); // Disable CR-to-NL mapping

//     tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
//     tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

//     tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds)
//     tty.c_cc[VMIN] = 0;

//     if (tcsetattr(serialPort, TCSANOW, &tty) != 0) {
//         std::cerr << "Error " << errno << " from tcsetattr: " << strerror(errno) << std::endl;
//         std::exit(1);
//     }    
// }

// void Controller::closePort() {
//     int serialPort = open("/dev/ttyACM0", O_RDWR);
//     close(serialPort);
// }

// void Controller::readPort() {
//     int serialPort = open("/dev/ttyACM0", O_RDWR);
//     char read_buf[8];
//     memset(&read_buf, '\0', sizeof(read_buf));
//     int num_bytes = read(serialPort, &read_buf, sizeof(read_buf));

//     if (num_bytes < 0) {
//         std::cerr << "Error reading: " << strerror(errno) << std::endl;
//         // break;
//     }

//     if(num_bytes > 0) {
//         // if(read_buf[0] == 's') {
//         //     std::cout << "\n";
//         //     Controller::recentView[view_index]->handle("2");
//         // }
//         // else if(read_buf[0] == 'r') {
//         //     std::cout << "\n";
//         //     Controller::recentView[view_index]->handle("3");
//         // }
//         // else if(read_buf[0] == 'n') Controller::recentView[view_index]->handle("5");
//         // else if(read_buf[0] == 'p') Controller::recentView[view_index]->handle("6");
//         // else if(read_buf[0] == '9') {
//         //     // string vol = (string)read_buf[0] + (string)read_buf[1];
//         //     std::cout << "\n";
//         //     Controller::recentView[view_index]->handle(read_buf);
//         // }

//         if(read_buf[0] == '3' && read_buf[1] == '1') {
//             // string vol = (string)read_buf[0] + (string)read_buf[1];
//             std::cout << "\n";
//             Controller::recentView[view_index]->handle(read_buf);
//         }
//         else {
//             std::cout << "\n";
//             Controller::recentView[view_index]->handle(read_buf);
//         }
//     }

//     // if (num_bytes > 0) {
//     //     std::cout << "Read " << num_bytes << " bytes. Data: " << read_buf << std::endl;
//     // }
// }

// void Controller::checkPort() {
//     while(running) {
//         readPort();
//     }
//     running = false;
// }