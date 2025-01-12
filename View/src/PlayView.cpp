#include "PlayView.h"
#include <iostream>
#include <string>

using namespace std;

vector<MultiType> PlayView::display(Song s, vector<Song> songs, int curPos) {
     vector<MultiType> ResultList;
     string tempt = "";
     tempt  = View::display(s);
     tempt += "\n";
     tempt += View::displayPlayingInfor(songs, curPos);
     tempt += View::alignLength(); 
     ResultList = this->newdisplayBottom();    
     ResultList.insert(ResultList.begin(),tempt);
     return ResultList;
}

vector<MultiType> PlayView::newdisplayBottom() {
     vector<MultiType> ResultList;
     string tempt = "";
     tempt += alignLeft("",'-', WIDTH) + "\n";
     ResultList.push_back(tempt);
     vector<string> option = {
          "-1. Replay",
          "2. Pause",
          "3. Resume",
          "4. Edit Metadata",
          "-5. Next",
          "6. Previous",
          "7. Volume Up",
          "8. Volume Down"
     };
     for(unsigned int i = 0; i < option.size(); i++) {
          tempt = "";
          //if((line % option.size()) == i) View::highlightObj(alignLeft(option[i], ' ', WIDTH/4));
          tempt += alignLeft(option[i], ' ', WIDTH/4);
          if(i == 3 || i == 7) {
               tempt = tempt + "\b-" + "\n";
          }
          option[i] = tempt;
     }

     // cout << alignLeft("-1. Replay", ' ', WIDTH/4) 
     //      << alignLeft("2. Pause", ' ', WIDTH/4) 
     //      << alignLeft("3. Resume", ' ', WIDTH/4)
     //      << alignLeft("4. Edit Metadata", ' ', WIDTH/4 -1)
     //      << "-" <<endl;
     // cout << alignLeft("-5. Next", ' ', WIDTH/4) 
     //      << alignLeft("6. Previous", ' ', WIDTH/4) 
     //      << alignLeft("7. Volume Up", ' ', WIDTH/4)
     //      << alignLeft("8. Volume Down", ' ', WIDTH/4 -1) 
     //      << "-" <<endl;  
     ResultList.push_back(option);
     ResultList.push_back(View::displayBottom());
     return ResultList;       
}
