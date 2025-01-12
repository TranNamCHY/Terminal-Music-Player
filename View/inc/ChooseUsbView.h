#pragma once
#include "View.h"
#include <iostream>
#include <vector>
#include <string>
#include "ExtraVariableType.h"
using namespace std;

class ChooseUsbView : public View {
public:
    //Display multi USB chose
    vector<MultiType> display(vector<string> usbpath);
    int line = 0;
};
