#include "Controller.h"
#include "MediaManager.h"
#include "MusicPlayer.h"
#include "Playlist.h"

using namespace std;

int main() {
    Controller c;
    // MusicPlayer::configPort();
    c.run();
    // MusicPlayer::closePort();
    return 0;
}