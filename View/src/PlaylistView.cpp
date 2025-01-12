#include "PlaylistView.h"
#include <iostream>
using namespace std;
vector<MultiType> PlaylistView::display(vector<string> plists) {
    string tempt;
    vector<MultiType> ResultList;
    vector<string> option;
    int num = plists.size();
    //cout << View::alignMiddle(" SELECT PLAYLIST ", '=', WIDTH) << endl;
    //cout << endl;s
    tempt = View::alignMiddle(" SELECT PLAYLIST ", '=', WIDTH) + "\n" + "\n";
    tempt += "You have " + std::to_string(num) + " playlists. Please select one:" + "\n" + "\n";
    //cout << "You have " << num << " playlists. Please select one:" << endl << endl; 
    ResultList.push_back(tempt);
    for(int i = 0; i < num; i++) {
        //if((line % num) == i) {
        //    View::highlightLine(to_string(i+1)+ ". " + plists[i]);
        //} else cout << i + 1 << ". " << plists[i] << endl;a
        tempt = to_string(i+1) + ". " + plists[i];
        option.push_back(tempt);
        cout <<  "Test: " <<  tempt << endl;
    } 
    ResultList.push_back(option);
    tempt = "";
    tempt += View::alignLength();
    tempt += View::displayBottom();
    ResultList.push_back(tempt);
    return ResultList;
}