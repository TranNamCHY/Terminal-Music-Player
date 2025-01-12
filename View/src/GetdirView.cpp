#include "GetdirView.h"

using namespace std;
vector<MultiType> GetdirView::display() {
    vector<string> option = {
        "1. USB path: " + usbPath,
        "2. Choose another path",
        "3. Current path: " + path    
    };
    system("clear");
    cout << View::alignMiddle(" SELECT DIRECTORY ", '=', WIDTH) << endl;
    cout << endl;
    cout << "Select your option:" << endl << endl;
    
    for(unsigned int i = 0; i < option.size(); i++) {
        if((line % option.size()) == i) View::highlightLine(option[i]);
        else cout << option[i] << endl;
        // else cout << i + 1 << ". " << option[i] << endl;
    }
    // cout << "1. USB path: " << usbPath << endl;
    // cout << "2. Choose another path" << endl;
    // cout << "3. Current path: " << path << endl;
    View::alignLength();
    View::displayBottom();
}
