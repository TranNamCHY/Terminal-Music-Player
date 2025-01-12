#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <taglib/fileref.h>
#include <taglib/tag.h>

using namespace std;

class Song {
private:
    string path;
    string title;
    string artist;
    string album;
    string year;
    string duration;

public:
    /*
        Just initialize path of the song, but metadata
    */
    Song(string path, bool getMetadata=false);

    void getAllMetadata();

    void setTitle(const string& newdata);
    void setArtist(const string& newdata);
    void setAlbum(const string& newdata);
    void setYear(const unsigned int& newdata);

    int setMetadata(const Song& other);

    string getPath() const;

    string getTitle() const;

    string getArtist() const;

    string getAlbum() const;

    string getYear() const;

    string getDuration() const;

    void convertMP4toMP3(const string& mp4Path, const string& mp3Path);
};
