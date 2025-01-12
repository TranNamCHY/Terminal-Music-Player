#include "CreatePlaylistView.h"
#include <iostream>

string CreatePlaylistView::displayBottom() {
    string tempt = "";
    string create = "Create: [";
    create = create + CREATE + "]";
    string del = "Delete: [";
    del = del + DELETE + "]";
    tempt += alignLeft("",'-', WIDTH) + "\n";
    tempt = tempt + alignMiddle(create,' ', WIDTH/2)
         + alignMiddle(del,' ', WIDTH/2)
         + "\n";
    tempt += View::displayBottom();
    return tempt;
}

vector<MultiType> CreatePlaylistView::display(vector<string> plists) {
    vector<MultiType> ResultList;
    vector<string> option;
    string tempt = "";
    tempt = tempt + View::alignMiddle(" EDIT PLAYLISTS ", '=', WIDTH) + "\n" + "\n";
    //cout << endl;
    int num = plists.size();
    tempt = tempt + "You have " + std::to_string(num) + " playlists. Please select one" + "\n" + "\n";
    ResultList.push_back(tempt);
    for(int i = 0; i < num; i++) {
        tempt = "";
        /* if((line % num) == i) {
            View::highlightLine(to_string(i+1)+ ". " + plists[i]);
        } else  */
        tempt = tempt + std::to_string(i + 1) + ". " + plists[i];
        option.push_back(tempt);
    }
    ResultList.push_back(option);
    tempt = "";
    tempt += View::alignLength();
    tempt += CreatePlaylistView::displayBottom();
    ResultList.push_back(tempt);
    return ResultList;
}
