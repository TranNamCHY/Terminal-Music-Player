#pragma once
#include "View.h"
#include <iostream>
#include <vector>
#include "Song.h"
#include <iomanip>
#include <sstream>
#include "ExtraVariableType.h"
using namespace std;

class SongListView : public View {
public:
    string displayBottom();
    vector<MultiType> displaySongs(vector<Song> songs, int pageNum, int size);
    int line = 0;
};
