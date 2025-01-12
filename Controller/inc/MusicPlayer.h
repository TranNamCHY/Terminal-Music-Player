#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error number definitions
#include <termios.h> // POSIX terminal control definitions
#include <unistd.h> // UNIX standard function definitions
// #include <algorithm>
// #include <random>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include "Song.h"
#include <mutex>
#include <functional>

class MusicPlayer {
public:
    MusicPlayer();
    ~MusicPlayer();

/// @brief Plays the given song
/// @param song The song to play
    void play(const Song& song);

/// @brief Pauses the currently playing song   
    void pause();

/// @brief Resumes the currently paused song
    void resume();

/// @brief Stops the currently playing song 
    void stop();

/// @brief Plays the next song in the playlist
    void next();

/// @brief Plays the previous song in the playlist    
    void previous();

/// @brief Sets the volume for the music player
/// @param volume The volume level (0-100)
    void setVolume(int volume);

/// @brief Increases the volume by 10, up to a maximum of 100
    void volumeUp();

/// @brief Decreases the volume by 10, down to a minimum of 0
    void volumeDown();

/// @brief Checks if music is currently playing
/// @return True if music is playing, false otherwise
    bool isPlaying() const;

    void shuffle();

/// @brief Sets the playlist of songs
/// @param playlist The playlist to set
    void setPlaylist(std::vector<Song>* playlist);

/// @brief Adds a song to the playlist
/// @param song The song to add
    void addToPlaylist(const Song& song);

/// @brief Clears the playlist 
    void clearPlaylist();

/// @brief Sets the current index in the playlist
/// @param index The index to set
    void setCurrentIndex(const int& index);

/// @brief Gets the current index in the playlist
/// @return The current index
    int getCurrentIndex();

/// @brief Gets the current playback time in "MM:SS" format
/// @return The current playback time as a string
    std::string getCurrentTime();

/// @brief Gets the duration of the currently loaded music file in "MM:SS" format
/// @return The duration of the music file as a string
    std::string getDuration();
    
/// @brief Sets the callback function to be called when a song ends
/// @param callback The callback function
    void setSongEndCallback(std::function<void()> callback);

/// @brief Hides the progress bar by stopping its update thread
    void hiddenProgressBar();

/// @brief Unhides the progress bar by starting its update thread if music is playing
    void unhideProgressBar();
    
    // static void getPort();
    // static void configPort();
    // static void closePort();
    // static int serialPort;

private:
/// @brief The thread function responsible for playing music
    void musicThreadFunc();

/// @brief Plays the current song based on the current index
    void playCurrentSong();

/// @brief Gets the duration of the music file specified by the file path
/// @param filePath The path to the music file
/// @return The duration of the music file in seconds
    int getFileDuration(const std::string& filePath);

/// @brief Gets the elapsed playback time of the current song in seconds
/// @return The elapsed playback time in seconds
    int getElapsedTime();

    std::string currentFile;
    Mix_Music* music;
    std::thread musicThread;
    std::atomic<bool> playing;
    std::atomic<bool> paused;
    std::atomic<int> volume = 50;

    std::vector<Song>* playlist;
    int currentIndex;

    int musicDuration;
    int elapsedTime;
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    std::chrono::time_point<std::chrono::steady_clock> pauseTime;

/// @brief Displays the progress of the current song playback
    void displayProgress();

    std::thread progressThread; // Thêm biến thread cho displayProgress
    std::atomic<bool> stopProgress; // Thêm biến atomic để dừng progressThread
    std::mutex mtx; // Thêm mutex để đảm bảo an toàn trong multi-threading
    std::function<void()> songEndCallback; // Thêm callback

    // void readPort();
    
};

#endif // MUSICPLAYER_H
