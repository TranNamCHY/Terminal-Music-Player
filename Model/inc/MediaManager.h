#pragma once
#include <vector>
#include "Playlist.h"
#include "configs.h"
#include "display.h"
#include "Library.h"
#include "MediaList.h"

using namespace std;

/// @brief This class aim to manage a MediaList a time,
/// Provide method to process with current active MediaList (a Library/Playlist)
/// Provide method to create, change data of playlist too.
class MediaManager {
private:
    Library songLib;
    vector<Playlist> playlists;
    vector<string> listDeleted;
    MediaList* currentMediaList = nullptr;
    bool playListActive = false;
    int curLibSongIndex = -1;
    int curPlistSongIndex = -1;
    int curLibPageOfSong = 0;
    int curPlistPageOfSong = 0;
    int activePlistIndex = 0;
    MediaManager();
public:
    /// @brief This aim to create only one instance for mediaManager. Because this class may modify app data.
    /// @return A unique instance of MediaManger 
    static MediaManager& getInstance();

    /// @brief Check if playing a playlist
    /// @return true if a playlist is playing
    bool isPlaylistActive();

    /// @brief Select a playlist to play songs
    /// @param PlaylistNum index of the desired playlist
    void setActivePList(int PlaylistNum);

    /// @brief Change to play curret Library
    void setActiveLibrary();

    /// @brief get the Library of the model
    /// @return the Libray of the model
    Library& getLibrary();

    int getCurSongIndex();

    void setCurSongIndex(int data);

    int getNumberofSong();

    int getActivePListIndex();

    Playlist& getActivePlaylist();

    vector<string> getPlaylistNames();

    Song& getSong(int index);
    
    Song& getCurSong();

    int getCurPageOfSongIndex();

    vector<Song> getCurPageOfSong();

    vector<Song> getPageOfSong(int pageNum);

    vector<Song>& sortCurList(int option);

    vector<Song>* getCurSongList();

    int isExistPlayList(string name);

    int renamePlaylist(int PlaylistNum, const string& newName);

    void createPlaylist(string name);

    /*
        Remeber to store name to listDeleted to update data when close program
    */
    int deletePlaylist(int pos);

    /*
        Call this funtion before exit program do update database
    */
    void updateDatabase();
};
