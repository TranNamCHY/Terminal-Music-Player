#include "Handler.h"
#include "PlaylistView.h"
#include "Model.h"
#include <string>
#include "display.h"

int songListhandle(string command, int& currentPage) {
    Model &model = Model::getInstance();
    if (command == PREVIOUS_PAGE) {
        vector<Song> songs = model.mediaManager.getPageOfSong(currentPage - 1);
        currentPage--;
        View::displaySongs(songs, currentPage, model.mediaManager.getNumberofSong(), 0);
    } else if (command == NEXT_PAGE) {
        vector<Song> songs = model.mediaManager.getPageOfSong(currentPage + 1);
        currentPage++;
        View::displaySongs(songs, currentPage, model.mediaManager.getNumberofSong(), 0);
    } else if (command == SORT_BY_ARTIST) {
        model.mediaManager.sortCurList(SORT_ARTIST);
        vector<Song> songs = model.mediaManager.getPageOfSong(currentPage);
        View::displaySongs(songs, currentPage, model.mediaManager.getNumberofSong(), 0);
    } else if (command == SORT_BY_NAME) {
        static bool az = true;
        if (az) {
            model.mediaManager.sortCurList(SORT_AZ);
            az = false;
        } else {
            model.mediaManager.sortCurList(SORT_ZA);
            az = true;
        }
        vector<Song> songs = model.mediaManager.getPageOfSong(currentPage);
        View::displaySongs(songs, currentPage, model.mediaManager.getNumberofSong(), 0);
    } else {
        return 0;
    }
    return 1;
}
