#pragma once
#include "Song.h"
#include <vector>
#include <string>
#include "configs.h"
#include "MediaList.h"

using namespace std;

/// @brief Playlist is a MediaList that get song from a.txt file in app data.
/// Playlists are user-deined.
/// Have the ability to add/remove song, change name
class Playlist : public MediaList {
private:
    string name;
    bool changed = false;  // set changed = true when data of the Playlist change by addSong, deleteSong methods
    bool fetchSong = false; 
public:
    bool newCreated = false;
    Playlist(string name);

    /*
        Songs of each playlist are stored in a .txt file in .data/playlist_name with "playlist_name" is name of playlist
        Initialize data for songs then add them to the songList vector
        Then this->fetchSong = true
    */
    Playlist& initialize();

    string getName();

    bool isAlreadyInPlist(string path);

    /*
        add a Song to playlist
        some case of input: 
            + absolute_path is not found
            + the song has been already in the playlist
    */
    Playlist& addSong(string absolute_path);

    Playlist& deleteSong(int index);

    int rename(const string& newName);
    
    /*
        Call this method at the end of program if data of Playlist change (changed = true)
    */
    void updateDataToFile();
};
