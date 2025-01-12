#pragma once
#include "View.h"
#include <iostream>
#include <vector>
#include "Song.h"
#include <iomanip>
#include <sstream>

using namespace std;

class EditPlaylistView : public View {
public:
    string displayBottom();
    void displaySongs(vector<Song> songs, int pageNumn, int size);
    int line = 0;
};
