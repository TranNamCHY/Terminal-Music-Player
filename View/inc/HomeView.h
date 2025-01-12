#pragma once
#include "View.h"
#include <iostream>
#include <vector>
#include"ExtraVariableType.h"
using namespace std;

class HomeView : public View {
public:
    vector<MultiType> display();
    int line = 0;  
};