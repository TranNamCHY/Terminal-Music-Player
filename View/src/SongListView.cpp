#include "SongListView.h"
#include <iostream>

string SongListView::displayBottom() {
    string tempt = "";
    string next = "-Next: [";
    next = next + NEXT_PAGE + "]";
    string pre = "Previous: [";
    pre = pre + PREVIOUS_PAGE + "]";
    string sortname = "SortName: [";
    sortname = sortname + SORT_BY_NAME + "]";
    string sortartist = "SortArtist: [";
    sortartist = sortartist + SORT_BY_ARTIST + "]-";
    tempt = tempt + alignLeft("",'-', WIDTH) + "\n";
    tempt = tempt + alignLeft(next,' ', WIDTH/4)
         + alignLeft(pre,' ', WIDTH/4)
         + alignRight(sortname,' ', WIDTH/4)
         + alignRight(sortartist,' ', WIDTH/4)
         + "\n";
    tempt += View::displayBottom();
    return tempt;
}

vector<MultiType> SongListView::displaySongs(vector<Song> songs, int pageNum, int size) {
    vector<MultiType> ResultList;
    string tempt = "";
    ResultList = View::displaySongs(songs, pageNum, size, line);
    tempt = View::alignLength();
    tempt += this->displayBottom(); 
    ResultList.push_back(tempt);
    return ResultList;
}

