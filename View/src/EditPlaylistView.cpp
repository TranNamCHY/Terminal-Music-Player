#include "EditPlaylistView.h"
#include <iostream>

void EditPlaylistView::displaySongs(vector<Song> songs,int pageNum, int size) {
    View::displaySongs(songs, pageNum, size, line, -1);
    View::alignLength();
    this->displayBottom();      
}

string EditPlaylistView::displayBottom() {
    vector<string> option = {
        "-1. Rename",
        "2. Add From Cur",
        "3. Add From New",
        "4. Remove-"
    };

    for(unsigned int i = 0; i < option.size(); i++) {
        if((line % option.size()) == i) {
            if (i < (option.size()/2)) View::highlightObj(alignLeft(option[i], ' ', WIDTH/4));
            else View::highlightObj(alignRight(option[i], ' ', WIDTH/4));
        } else {
            if(i < (option.size()/2)) cout << alignLeft(option[i], ' ', WIDTH/4);
            else cout << alignRight(option[i], ' ', WIDTH/4);
        } 
    }
    cout << endl;


    // cout << alignLeft("",'-', WIDTH) << endl;
    // cout << alignLeft("-1. Rename", ' ', WIDTH/4)
    //      << alignLeft("2. Add From Cur", ' ', WIDTH/4)
    //      << alignRight("3. Add From New", ' ', WIDTH/4)
    //      << alignRight("4. Remove-", ' ', WIDTH/4)
    //      << endl;
    string next = "-Next: [";
    next = next + NEXT_PAGE + "]";
    string pre = "Previous: [";
    pre = pre + PREVIOUS_PAGE + "]";
    string sortname = "SortName: [";
    sortname = sortname + SORT_BY_NAME + "]";
    string sortartist = "SortArtist: [";
    sortartist = sortartist + SORT_BY_ARTIST + "]-";
    cout << alignLeft("",'-', WIDTH) << endl;
    cout << alignLeft(next,' ', WIDTH/4)
         << alignLeft(pre,' ', WIDTH/4)
         << alignRight(sortname,' ', WIDTH/4)
         << alignRight(sortartist,' ', WIDTH/4)
         << endl;
    View::displayBottom();
}
