#pragma once
#include "View.h"
#include <iostream>
#include <vector>
#include "Song.h" 
#include "ExtraVariableType.h"
using namespace std;

class PlayView : public View {
public:
    vector<MultiType> display(Song s, vector<Song> songs, int curPos);
    vector<MultiType> newdisplayBottom();
    int line = 0;
};
