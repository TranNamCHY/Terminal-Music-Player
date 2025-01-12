#pragma once
#include "Song.h"
#include "MediaList.h"
#include <vector>
#include <string>

using namespace std;

/// @brief Libraly is a MediaList that get song form a directory or multiple diretories
class Library : public MediaList{
private:    
    vector<string> dirPaths;
    bool needToChange = false;
    bool songfetched = false;
    void getMediaFileFromDir(const string& dir);
public:
    Library();

    bool isSongFetched();

    void getSongFromCurrentDirs();

    void getSongFromPath(string path);

    void addPathToCurrentDirs(string path);

    bool isAlreadyInCurDirs(string path);
};