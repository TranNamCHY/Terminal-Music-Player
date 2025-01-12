#pragma once
#include <iostream>
#include "View.h"
#include "ExtraVariableType.h"

using namespace std;

class GetdirView : public View {
public:
    vector<MultiType> display();
    string path;
    string usbPath;
    int line = 0;
};