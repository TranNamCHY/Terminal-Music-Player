#include "Song.h"

//#include <MediaInfo/MediaInfo.h> // Thêm thư viện MediaInfo
//#include <taglib/mpegfile.h>

using namespace std;
namespace fs = std::filesystem;

Song::Song(string path, bool getMetadata) : path(path) {
    if (getMetadata) {
        this->getAllMetadata();
    }
}

void Song::convertMP4toMP3(const string& mp4Path, const string& mp3Path) {
    string command = "ffmpeg -i \"" + mp4Path + "\" -b:a 192K -vn \"" + mp3Path + "\"";
    system(command.c_str());
}

void Song::getAllMetadata() {
    if (!fs::exists(this->path)) {
        throw runtime_error("Song's path does not exist: " + this->path);
    }

    fs::path filePath(this->path);
    if (filePath.extension() == ".mp4") {
        fs::path mp3Path = filePath.replace_extension(".mp3");
        if (!fs::exists(mp3Path)) {
            convertMP4toMP3(this->path, mp3Path.string());
        }
        this->path = mp3Path.string();
    }

    if (filePath.extension() == ".mp3") {
    TagLib::FileRef ref(this->path.c_str());
    if (!ref.isNull() && ref.tag()) {
        TagLib::Tag *tag = ref.tag();
        string title = string(tag->title().toCString(true));
        if (title.empty()) {
            fs::path p(this->path);
            this->title = p.stem().string();
        } else {
            this->title = title;
        }
        string artist = string(tag->artist().toCString(true));
        if (artist.empty()) {
            this->artist = "Unknown";
        } else {
            this->artist = artist;
        }
        string album = string(tag->album().toCString(true));
        if (album.empty()) {
            this->album = "Unknown";
        } else {
            this->album = album;
        }
        unsigned int year = tag->year();
        if (year == 0) {
            this->year = "Unknown";
        } else {
            this->year = to_string(year);
        }
        this->duration = to_string(ref.audioProperties()->lengthInSeconds());
    } else {
        throw runtime_error("Failed to read metadata from: " + this->path);
    }
    }
}

// void Song::getAllMetadata() {
//     if (!fs::exists(this->path)) {
//         throw runtime_error("Song's path does not exist: " + this->path);
//     } else {
//         TagLib::FileRef ref(this->path.c_str());
//         if (!ref.isNull() && ref.tag()) {
//             TagLib::Tag *tag = ref.tag();
//             string title = string(tag->title().toCString(true));
//             if (title == "") {
//                 fs::path p(this->path);
//                 this->title = p.stem().string();
//             } else {
//                 this->title = title;
//             }
//             this->artist = string(tag->artist().toCString(true));
//             this->album = string(tag->album().toCString(true));
//             this->year = to_string(tag->year());
//             this->duration = to_string(ref.audioProperties()->lengthInSeconds());
//         }
//     }
// }

void Song::setTitle(const string& newdata) {
    if (!fs::exists(this->path)) {
        throw runtime_error("Song's path does not exist: " + this->path);
    } else {
        TagLib::FileRef ref(this->path.c_str());
        if (!ref.isNull() && ref.tag()) {
            TagLib::Tag *tag = ref.tag();
            tag->setTitle(newdata);
        }
        ref.save();
        this->title = newdata;
    }
}
void Song::setArtist(const string& newdata) {
    if (!fs::exists(this->path)) {
        throw runtime_error("Song's path does not exist: " + this->path);
    } else {
        TagLib::FileRef ref(this->path.c_str());
        if (!ref.isNull() && ref.tag()) {
            TagLib::Tag *tag = ref.tag();
            tag->setArtist(newdata);
        }
        ref.save();
        this->artist = newdata;
    }
}
void Song::setAlbum(const string& newdata) {
    if (!fs::exists(this->path)) {
        throw runtime_error("Song's path does not exist: " + this->path);
    } else {
        TagLib::FileRef ref(this->path.c_str());
        if (!ref.isNull() && ref.tag()) {
            TagLib::Tag *tag = ref.tag();
            tag->setAlbum(newdata);
        }
        ref.save();
        this->album = newdata;
    }
}
void Song::setYear(const unsigned int& newdata) {
    if (!fs::exists(this->path)) {
        throw runtime_error("Song's path does not exist: " + this->path);
    } else {
        TagLib::FileRef ref(this->path.c_str());
        if (!ref.isNull() && ref.tag()) {
            TagLib::Tag *tag = ref.tag();
            tag->setYear(newdata);
        }
        ref.save();
        this->year = to_string(newdata);
    }
}

string Song::getPath() const {
    return path;
}

string Song::getTitle() const {
    return title;
}

string Song::getArtist() const {
    return artist;
}

string Song::getAlbum() const {
    return album;
}

string Song::getYear() const {
    return year;
}

string Song::getDuration() const {
    int totalSeconds = stoi(duration);
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds;
    
    return oss.str();
}
