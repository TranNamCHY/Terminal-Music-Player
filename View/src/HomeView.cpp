#include "HomeView.h"
#include <iostream>
#include <variant>
vector<MultiType> HomeView::display() {
    string tempt;
    vector<MultiType> ResultList;
    vector<string> option = {
        "1. Select direction",
        "2. Play a playlist",
        "3. Play songs from recent folders",
        "4. Edit playlists"
    };
    // int num = option.size()

    system("clear");
    tempt = "";
    tempt = View::alignMiddle(" MEDIA BROWSER ", '=', WIDTH) + "\n" + "\n" + "Welcome. Select your option:" + "\n" + "\n";
    ResultList.push_back(tempt);
    //cout << View::alignMiddle(" MEDIA BROWSER ", '=', WIDTH) << endl;
    //cout << endl;
    //cout << "Welcome. Select your option:" << endl << endl;

    /* for(unsigned int i = 0; i < option.size(); i++) {
        cout << option[i] << endl;
        // else cout << i + 1 << ". " << option[i] << endl;
    } */
    ResultList.push_back(option);
    // cout << "1. Select direction" << endl;
    // cout << "2. Play a playlist" << endl;
    // cout << "3. Play songs from recent folders" << endl;  
    // cout << "4. Edit playlists" << endl;
    tempt = "";
    tempt += View::alignLength();
    tempt += View::displayBottom();
    ResultList.push_back(tempt);
    return ResultList;
    //return option;
}
 