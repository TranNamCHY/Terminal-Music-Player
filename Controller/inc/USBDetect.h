#ifndef USBDETECT_H
#define USBDETECT_H
#pragma once
#include <libudev.h>
#include <iostream>
#include <atomic>
#include <thread>
#include <unistd.h>
#include <string.h>
#include <chrono>
#include <vector>

class USBMonitor {
public:
    USBMonitor();
    ~USBMonitor();
    void startMonitoring();
    void stopMonitoring();
    int USBGetStatus() const;
    void setUserPath();
    void clearUserPath();
    std::string getUserPathValue() const;
    void DetectUSBEvents();
    std::vector<std::string> getSubdirectories(const std::string& parentPath);
    
    std::string getUSBPort();
    static std::string find_usb_serial_device() ;
private:
    
    int status;
    std::string UserPath;
    struct udev* udev;
    struct udev_monitor* mon;
    std::atomic<bool> running;
    std::thread monitorThread;

    std::string USBPortAddress; // Thêm thuộc tính để lưu địa chỉ port USB
};

#endif // USBDETECT_H
