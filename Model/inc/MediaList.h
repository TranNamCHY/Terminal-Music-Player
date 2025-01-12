#pragma once
#include "Song.h"
#include <vector>
#include "configs.h"
#include "display.h"

/// @brief Manage a vector of songs with method to get data, or process the data like sort method
class MediaList {
protected:
    vector<Song> songList;

private:
    static bool sortByNameAZ(const Song &a, const Song &b);

    static bool sortByNameZA(const Song &a, const Song &b);

    static bool sortByArtist(const Song &a, const Song &b);

public:
    Song& getSong(int index);
    
    vector<Song>& getSongList();

    int getNumberOfSong();
    
    vector<Song>& sort(int option);

    vector<Song> getPageOfSong(int pageNum);
};