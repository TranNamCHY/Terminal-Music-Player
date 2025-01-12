#include "USBDetect.h"
#include <filesystem>
namespace fs = std::filesystem;
//Constructor
USBMonitor::USBMonitor() : status(0), udev(nullptr), mon(nullptr), running(false) {
    udev = udev_new();
    if (!udev) {
        std::cerr << "Can't create udev\n";
    } else {
        mon = udev_monitor_new_from_netlink(udev, "udev");
        if (!mon) {
            std::cerr << "Can't create udev monitor\n";
            udev_unref(udev);
        } else {
            udev_monitor_filter_add_match_subsystem_devtype(mon, "usb", "usb_device");
            udev_monitor_enable_receiving(mon);
        }
    }
    USBPortAddress="";
}

//Destructor
USBMonitor::~USBMonitor() {
    stopMonitoring();
    if (mon) {
        udev_monitor_unref(mon);
    }
    if (udev) {
        udev_unref(udev);
    }
}

//Start USB Detect
void USBMonitor::startMonitoring() {
    running = true;
    monitorThread = std::thread(&USBMonitor::DetectUSBEvents, this);
}

//Stop USB Detect
void USBMonitor::stopMonitoring() {
    running = false;
    if (monitorThread.joinable()) {
        monitorThread.join();
    }
}

//Get USB Status, 1 is Connect, 0 is not
int USBMonitor::USBGetStatus() const {
    return status;
}

//USB Detect Loop Function
void USBMonitor::DetectUSBEvents() {
    if (!udev || !mon) return;

    int fd = udev_monitor_get_fd(mon);

    while (running) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(fd, &fds);

        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        USBPortAddress=find_usb_serial_device();
        // std::cout << "USB Inserted Port: "<< USBPortAddress << std::endl;
        int ret = select(fd + 1, &fds, nullptr, nullptr, &timeout);
        if (ret > 0 && FD_ISSET(fd, &fds)) {
            struct udev_device* dev = udev_monitor_receive_device(mon);
            if (dev) {
                const char* action = udev_device_get_action(dev);

                if (action) {
                    if (strcmp(action, "add") == 0) {
                        std::cout << "USB Inserted" << std::endl;
                        status = 1;
                        setUserPath();
                    } else if (strcmp(action, "remove") == 0) {
                        std::cout << "USB Removed" << std::endl;
                        status = 0;
                        clearUserPath();
                        USBPortAddress="";
                    }
                }
                udev_device_unref(dev);
            }
        }
    }
}

//Set User USB Path when USB Connect
void USBMonitor::setUserPath() {
    char* username = getlogin();
    if (username != nullptr) {
        UserPath = "/media/" + std::string(username);
    } else {
        UserPath = "/media/unknown";
    }
}

//Clear User USB Path when USB Connect
void USBMonitor::clearUserPath() {
    UserPath = "";
}

//Get USB User Path
std::string USBMonitor::getUserPathValue() const {
    return UserPath;
}

std::vector<std::string> USBMonitor::getSubdirectories(const std::string& parentPath) {
    std::vector<std::string> subdirectories;

    try {
        for (const auto& entry : fs::directory_iterator(parentPath)) {
            if (entry.is_directory()) {
                subdirectories.push_back(entry.path().string());
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "General error: " << e.what() << std::endl;
    }
    return subdirectories;
}


std::string USBMonitor::getUSBPort()
{
    return USBPortAddress;
}

std::string USBMonitor::find_usb_serial_device() {
    struct udev *udev;
    struct udev_enumerate *enumerate;
    struct udev_list_entry *devices, *dev_list_entry;
    struct udev_device *dev;
    std::string device_path;

    udev = udev_new();
    if (!udev) {
        printf("Can't create udev\n");
        return NULL;
    }

    enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "tty");
    udev_enumerate_scan_devices(enumerate);
    devices = udev_enumerate_get_list_entry(enumerate);

    udev_list_entry_foreach(dev_list_entry, devices) {
        const char *path;

        path = udev_list_entry_get_name(dev_list_entry);
        dev = udev_device_new_from_syspath(udev, path);

        if (udev_device_get_devnode(dev) && 
            udev_device_get_property_value(dev, "ID_VENDOR_ID") && 
            udev_device_get_property_value(dev, "ID_MODEL_ID")) {

            device_path = strdup(udev_device_get_devnode(dev));
            udev_device_unref(dev);
            break;
        }

        udev_device_unref(dev);
    }

    udev_enumerate_unref(enumerate);
    udev_unref(udev);

    return device_path;
}