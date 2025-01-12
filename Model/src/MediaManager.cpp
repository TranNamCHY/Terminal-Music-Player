#include <filesystem>
#include <vector>
#include "Playlist.h"
#include "configs.h"
#include "display.h"
#include "Library.h"
#include "MediaList.h"
#include "MediaManager.h"

using namespace std;
namespace fs = std::filesystem;

MediaManager::MediaManager() {
    for (const auto& entry : fs::directory_iterator(PLAYLIST_FILES_DIR)) {
        if (entry.is_regular_file()) {
            auto path = entry.path();
            if (path.extension() == ".txt") {
                playlists.push_back(Playlist(path.stem().string()));
            }
        }
    }
}

MediaManager &MediaManager::getInstance() {
    static MediaManager manager;
    return manager;
}

bool MediaManager::isPlaylistActive() {
    return playListActive;
}

int MediaManager::getCurSongIndex() {
    if (playListActive) {
        return curPlistSongIndex;
    } else {
        return curLibSongIndex;
    }
}

void MediaManager::setCurSongIndex(int data) {
    if (playListActive) {
        curPlistSongIndex = data;
    } else {
        curLibSongIndex = data;
    }
}

int MediaManager::getNumberofSong() {
    if (this->currentMediaList != nullptr) {
        return this->currentMediaList->getNumberOfSong();
    } else {
        return 0;
    }
}

void MediaManager::setActivePList(int PlaylistNum) {
    if (PlaylistNum < 0 || (long unsigned int)PlaylistNum >= this->playlists.size()) {
        throw out_of_range("Playlist no." + to_string(PlaylistNum) + "does not exits");
    } else {
        this->curPlistSongIndex = -1;
        this->currentMediaList = &playlists[PlaylistNum].initialize();
        playListActive = true;
        this->activePlistIndex = PlaylistNum;
    }
}

int MediaManager::getActivePListIndex() {
    return this->activePlistIndex;
}

Playlist& MediaManager::getActivePlaylist() {
    return this->playlists[activePlistIndex];
}

void MediaManager::setActiveLibrary() {
    this->currentMediaList = &this->songLib;
    playListActive = false;
}

Library& MediaManager::getLibrary() {
    return this->songLib;
}

vector<string> MediaManager::getPlaylistNames() {
    vector<string> result;
    for(auto p = playlists.begin(); p != playlists.end(); ++p) {
        result.push_back((*p).getName());
    }
    return result;
}

Song &MediaManager::getSong(int index) {
    return this->currentMediaList->getSong(index);
}

Song& MediaManager::getCurSong() {
    return (*this->currentMediaList).getSong(this->getCurSongIndex());
}

int MediaManager::getCurPageOfSongIndex() {
    if(playListActive) {
        return curPlistPageOfSong;
    } else {
        return curLibPageOfSong;
    }
}

vector<Song> MediaManager::getCurPageOfSong() {
    if(playListActive) {
        return this->currentMediaList->getPageOfSong(curPlistPageOfSong);
    } else {
        return this->currentMediaList->getPageOfSong(curLibPageOfSong);
    }
};

vector<Song> MediaManager::getPageOfSong(int pageNum) {
    vector<Song> result = this->currentMediaList->getPageOfSong(pageNum);
    if(playListActive) {
        curPlistPageOfSong = pageNum;
    } else {
        curLibPageOfSong = pageNum;
    }
    return result;
};

vector<Song>& MediaManager::sortCurList(int option) {
    return this->currentMediaList->sort(option);
}

vector<Song>* MediaManager::getCurSongList() {
    return &this->currentMediaList->getSongList();
}

int MediaManager::isExistPlayList(string name) {
    int count = 0;
    for (auto it = playlists.begin(); it != playlists.end(); ++it) {
        if (name == (*it).getName()) {
            return count;
        } else {
            count++;
        }
    }
    return -1;
};

int MediaManager::renamePlaylist(int PlaylistNum, const string& newName) {
    if (this->isExistPlayList(newName) >= 0) {
        throw runtime_error("rename Plist: Plist with name " + newName + "has already exíted\n");
    }

    if (PlaylistNum < 0 || (long unsigned int)PlaylistNum >= this->playlists.size()) {
        throw out_of_range("Playlist rename: Index of playlist out of bound " + to_string(PlaylistNum) + "\n");
    } else {
        return this->playlists[PlaylistNum].rename(newName);
    }
};

void MediaManager::createPlaylist(string name) {
    Playlist playlist(name);
    if (this->isExistPlayList(playlist.getName()) < 0) {
        playlist.newCreated = true;
        this->playlists.push_back(playlist);
    } else {
        throw runtime_error("create Plist: Playlist existed\n");
    }
}

/*
    Remeber to store name to listDeleted to update data when close program
*/
int MediaManager::deletePlaylist(int pos) {
    if (pos >= 0 && (long unsigned int)pos < this->playlists.size()) {
        if (!this->playlists[pos].newCreated) {
            this->listDeleted.push_back(this->playlists[pos].getName());
        }
        this->playlists.erase(this->playlists.begin() + pos);
        return 0;
    } else {
        throw runtime_error("delete Plist: Playlist index out of range\n");
    }
}

/*
    Call this funtion before exit program
*/
void MediaManager::updateDatabase() {
    for (auto it = playlists.begin(); it != playlists.end(); ++it) {
        (*it).updateDataToFile();
    }
    for (auto it = listDeleted.begin(); it != listDeleted.end(); ++it) {
        fs::path plPath(PLAYLIST_FILES_DIR);
        plPath.append(*it + ".txt");
        if (std::remove(plPath.string().c_str()) != 0) {
            cout << "Error while trying to delete data file: " << plPath.string() << endl;
        }
    }
}


// int main() {
//     cout.setf(std::ios::unitbuf);
//     MediaManager m;
//     vector<string> names = m.getPlaylistNames();
//     for (string name: names) {
//         cout << name << " ";
//     }
//     cout << endl;

//     // m.renamePlaylist(1, "Taylor");
//     names = m.getPlaylistNames();
//     for (string name: names) {
//         cout << name << " ";
//     }
//     cout << endl;

//     m.setActivePList(1);
//     Playlist* current = m.getActivePlaylist();
//     (*current).addSong("music/I Knew You Were Trouble - Taylor Swift.mp3");
//     // (*current).deleteSong(0);
//     (*current).addSong("music/Rolling in the Deep - Adele.mp3");
//     // m.deletePlaylist(2);

//     // Playlist p("BlackPink");
//     // p.addSong("music/Teenage Dream.mp3");
//     // m.createPlaylist(p);

//     names = m.getPlaylistNames();
//     for (string name: names) {
//         cout << name << " ";
//     }
//     cout << endl;
//     m.updateDatabase();

//     vector<Song> songs = m.sortCurList(SORT_AZ);
//     cout <<"Sort by name AZ " << songs.size() << "\n";
//     for (Song s: songs) {
//         cout << s.getTitle() << "\n";
//     }
//     cout << endl;

//     m.sortCurList(SORT_ZA);
//     songs = m.getCurSongList();
//     cout <<"Sort by name ZA " << songs.size() << "\n";
//     for (Song s: songs) {
//         cout << s.getTitle() << "\n";
//     }
//     cout << endl;

//     m.sortCurList(SORT_ARTIST);
//     songs = m.getCurSongList();
//     cout <<"Sort by name ARTIST " << songs.size() << "\n";
//     for (Song s: songs) {
//         cout << s.getTitle() << "\n";
//     }
//     cout << endl;

//     m.setActiveLibrary();
//     Library* now = m.getActiveLibrary();
//     (*now).getSongFromPath("music");
//     m.sortCurList(SORT_ZA);
//     songs = m.getPageOfSong(0);
//     for(Song s: songs) {
//         cout << s.getTitle() << endl;
//     }
//     return 0;
// }
