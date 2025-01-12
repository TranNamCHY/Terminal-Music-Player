#pragma once
#include "View.h"
#include <iostream>
#include <vector>
#include "ExtraVariableType.h"
using namespace std;

class CreatePlaylistView : public View {
public:
    vector<MultiType> display(vector<string> plists);
    string displayBottom();
    int line = 0;
};
