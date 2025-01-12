#include <filesystem>
#include <string>
#include <vector>
#include <fstream>
#include "Song.h"
#include "MediaList.h"
#include "configs.h"
#include "Library.h"

using namespace std;
namespace fs = std::filesystem;

void Library::getMediaFileFromDir(const string& dir) {
    if (!(fs::exists(dir) && fs::is_directory(dir))) {
        throw runtime_error("Can't access media directory: " + dir);
    }
    for (const auto& entry : fs::recursive_directory_iterator(dir)) {
        if (entry.is_regular_file()) {
            auto path = entry.path();
            if (path.extension() == ".mp3" || path.extension() == ".mp4") {
                songList.push_back(Song(path.string(), true));
            }
        }
    }
}

Library::Library() {
    ifstream file(RECENT_PLAYING_DIRS_FILEDATA);
    if (!file.is_open()) {
        cout << "Error while trying to open app data file: " << RECENT_PLAYING_DIRS_FILEDATA;
    } else {
        string dir_path;
        while (getline(file, dir_path)) {
            this->dirPaths.push_back(dir_path);
        }
        file.close();
    }
}

bool Library::isSongFetched(){
    return this->songfetched;
}

void Library::getSongFromCurrentDirs() {
    songList.clear();
    string message = "";
    for (string s: this->dirPaths) {
        try {
            this->getMediaFileFromDir(s);
        } catch (exception& e){
            message += e.what();
            this->needToChange = true;
        }
    }
    this->songfetched = true;
    // if (message != "") {
    //     throw runtime_error(message);
    // }
}

void Library::getSongFromPath(string path) {
    songList.clear();
    this->getMediaFileFromDir(path);
    this->songfetched = true;
}

bool Library::isAlreadyInCurDirs(string path) {
    fs::path absolutePath = fs::absolute(fs::path(path).lexically_normal());
    for (int i = 0; i < (int)dirPaths.size(); i++) {
        fs::path songAbsPath = fs::absolute(fs::path(dirPaths[i]).lexically_normal());
        if (fs::equivalent(absolutePath, songAbsPath)) {
            return true;
        }
    }
    return false;
}

void Library::addPathToCurrentDirs(string path) {
    if (!this->isAlreadyInCurDirs(path)) {
        ofstream myfile(RECENT_PLAYING_DIRS_FILEDATA, std::ios_base::app);
        if (myfile.is_open()) {
            myfile << path + "\n";
            myfile.close();
            this->dirPaths.push_back(path);
        } else {
            throw runtime_error("Error while trying to write to app data file");
        }
    }
}

// int main() {
//     Library l;
//     try {
//         l.getSongFromCurrentDirs();
//     } catch (exception& e) {
//         cout << e.what() << endl;
//     }

//     vector<Song>& songs = l.getSongList();
//     for(Song s: songs) {
//         cout << s.getTitle() << endl;
//     }

//     Song news = l.getSong(2);
//     l.addPathToCurrentDirs("/home/dhtruong/Documents/MediaBrowser/data2");

//     try {
//         l.getSongFromCurrentDirs();
//     } catch (exception& e) {
//         cout << e.what() << endl;
//     }

//     l.getSongFromPath("/home/dhtruong/Documents/MediaBrowser/data");
//     cout << news.getPath() << endl;
//     cout << l.getNumberOfSong() << endl;

//     l.sort(SORT_ZA);
//     songs = l.getSongList();
//     for(Song s: songs) {
//         cout << s.getTitle() << endl;
//     }

//     cout << l.getPageOfSong(0).size();
//     return 0;
// }