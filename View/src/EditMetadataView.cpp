#include "EditMetadataView.h"
#include <iostream>

string EditMetadataView::display(Song s) {
    View::display(s);
    View::alignLength(); 
    this->displayBottom();     
}

string EditMetadataView::displayBottom() {
    vector<string> option = {
        "-1. Set Title",
        "2. Set Artist",
        "3. Set Album",
        "4. Set Year-"    
    };
    cout << alignLeft("",'-', WIDTH) << endl;

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
    // cout << alignLeft("-1. Set Title", ' ', WIDTH/4) 
    //      << alignLeft("2. Set Artist", ' ', WIDTH/4) 
    //      << alignRight("3. Set Album", ' ', WIDTH/4)
    //      << alignRight("4. Set Year-", ' ', WIDTH/4)
    //      << endl;  
    View::displayBottom();       
}
