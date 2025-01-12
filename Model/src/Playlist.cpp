#include <filesystem>
#include <vector>
#include <string>
#include <fstream>
#include "Song.h"
#include "MediaList.h"
#include "Playlist.h"
#include "configs.h"

using namespace std;
namespace fs = std::filesystem;

Playlist::Playlist(string name) : name(name) {};

/*
    Songs of each playlist are stored in a .txt file in .data/playlist_name with "playlist_name" is name of playlist
    Initialize data for songs then add them to the songList vector
    Then this->fetchSong = true
*/
Playlist& Playlist::initialize() {
    if(!newCreated && !fetchSong) {
        fs::path plist_datafile_path;
        plist_datafile_path.append(PLAYLIST_FILES_DIR).append(this->name + ".txt");

        ifstream file(plist_datafile_path);

        if (!file.is_open()) {
            cout << "Error while opening playlist data file: " << plist_datafile_path.string();
        } else {
            string song_path;
            while (getline(file, song_path)) {
                try {
                    songList.push_back(Song(song_path, true));
                } catch (exception& e) {
                    this->changed = true;
                }
            }
            file.close();
        }

        fetchSong = true;
    }
    return *this;
};

string Playlist::getName() {
    return this->name;
}

bool Playlist::isAlreadyInPlist(string path)  {
    fs::path absolutePath = fs::absolute(fs::path(path).lexically_normal());
    for (int i = 0; i < (int)songList.size(); i++) {
        fs::path songAbsPath = fs::absolute(fs::path(songList[i].getPath()).lexically_normal());
        if (fs::equivalent(absolutePath, songAbsPath)) {
            return true;
        }
    }
    return false;
}

/*
    add a Song to playlist
    some case of input:
        + absolute_path is not found
        + the song has been already in the playlist
*/
Playlist& Playlist::addSong(string absolute_path) {
    bool isExist = false;
    if(this->isAlreadyInPlist(absolute_path)) {
        throw runtime_error("The song has been already in the playlist");
    }
    if (!isExist) {
        songList.push_back(Song(absolute_path, true));
        this->changed = true;
    }
    return *this;
}

Playlist& Playlist::deleteSong(int index) {
    if ((songList.size() > (long unsigned int)index) && (index >= 0)) {
        songList.erase(songList.begin() + index);
        this->changed = true;
        return *this;
    } else {
        throw out_of_range("getSong: song index is out of range\n");
    }
};

int Playlist::rename(const string& newName) {
    fs::path old_path, new_path;
    old_path.append(PLAYLIST_FILES_DIR).append(this->name + ".txt");
    new_path.append(PLAYLIST_FILES_DIR).append(newName + ".txt");
    try {
        fs::rename(old_path, new_path);
        this->name = newName;
    } catch (const fs::filesystem_error& e) {
        throw;
    }
    return 0;
};

/*
    Call this method at the end of program if data of Playlist change (changed = true)
*/
void Playlist::updateDataToFile() {
    if (!this->newCreated) {
        if (this->fetchSong == false && (this->songList.size() > 0 || this->newCreated || this->changed)) {
            throw runtime_error("Modified playlist data before initialize:" + this->name);
        }
    }

    if (this->newCreated || this->changed) {
        fs::path plPath(PLAYLIST_FILES_DIR);
        plPath.append(this->name + ".txt");
        ofstream file(plPath.string());
        if (!file.is_open()) {
            cout << "Error while trying to write data to file: " << plPath.string() << endl;
        }
        for (Song s : this->songList) {
            file << s.getPath() << endl;
        }
        file.close();
    }
}
