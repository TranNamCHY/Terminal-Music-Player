#include "Song.h"
#include <vector>
#include "configs.h"
#include "display.h"
#include <filesystem>
#include "MediaList.h"
#include <algorithm>

namespace fs = std::filesystem;

bool MediaList::sortByNameAZ(const Song &a, const Song &b) {
    return a.getTitle()[0] < b.getTitle()[0];
}

bool MediaList::sortByNameZA(const Song &a, const Song &b) {
    return !MediaList::sortByNameAZ(a, b);
}

bool MediaList::sortByArtist(const Song &a, const Song &b) {
    if (a.getArtist() == b.getArtist()) {
        return MediaList::sortByNameAZ(a, b);
    } else {
        return a.getArtist() < b.getArtist();
    }
}

Song& MediaList::getSong(int index) {
    if ((songList.size() > (long unsigned int)index) && (index >= 0)) {
        return songList[index];
    } else {
        throw out_of_range("getSong: song index is out of range\n");
    }
};

vector<Song>& MediaList::getSongList() {
    return this->songList;
}

int MediaList::getNumberOfSong() {
    return this->songList.size();
}

vector<Song>& MediaList::sort(int option) {
    switch (option) {
        case SORT_AZ:
            std::sort(songList.begin(), songList.end(), MediaList::sortByNameAZ);
            break;
        case SORT_ZA:
            std::sort(songList.begin(), songList.end(), MediaList::sortByNameZA);
            break;
        case SORT_ARTIST:
            std::sort(songList.begin(), songList.end(), MediaList::sortByArtist);
            break;
        default:
            break;
    }
    return songList;
}

vector<Song> MediaList::getPageOfSong(int pageNum) {
    if ((pageNum < 0 || pageNum * MAX_LINES >= this->getNumberOfSong()) && (pageNum != 0)) {
        throw out_of_range("No data " + to_string(pageNum));
    }

    int numberOfSong = this->getNumberOfSong() - MAX_LINES*(pageNum);
    numberOfSong = numberOfSong < MAX_LINES ? numberOfSong : MAX_LINES;
    vector<Song> result;
    // cout << "Number of song " << this->getNumberOfSong() << "  " << numberOfSong << endl;
    for(int i = 0; i < numberOfSong; i++) {
        result.push_back(songList[pageNum * MAX_LINES + i]);
    }
    return result;
}
