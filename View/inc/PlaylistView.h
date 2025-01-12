#pragma once
#include "View.h"
#include <iostream>
#include <vector>
#include <Playlist.h>
#include "ExtraVariableType.h"
using namespace std;

class PlaylistView : public View {
public:
    vector<MultiType> display(vector<string> plists);
    int line = 0;
};
