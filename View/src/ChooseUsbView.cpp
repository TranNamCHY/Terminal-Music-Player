#include "ChooseUsbView.h"

//Display multi USB chose
vector<MultiType> ChooseUsbView::display(vector<string> usbpath) {
    system("clear");
    cout << alignMiddle(" CHOOSE USB ", '=', WIDTH) << endl;
    cout << endl;
    cout << alignLeft("No", ' ', NO_COL)
         << alignLeft("USB Folder", ' ', TITLE_COL)
         << endl;
    unsigned index = 1;  // Biến đếm số thứ tự
    for (const string& path : usbpath) {
        // Tìm vị trí của ký tự '/' cuối cùng trong đường dẫn
        size_t pos = path.find_last_of("/\\");
        string folderName;
        
        if (pos != string::npos) {
            // Tách tên folder từ đường dẫn
            folderName = path.substr(pos + 1);
        } else {
            // Nếu không tìm thấy '/', thì toàn bộ chuỗi là tên folder
            folderName = path;
        }
        // In tên folder
        if((line % usbpath.size()) + 1 == index) {
        cout << "\033[30;47m";  // Chữ đen, nền trắng
        cout << alignLeft(to_string(index), ' ', NO_COL)
             << alignLeft(truncate(folderName,TITLE_COL), ' ', TITLE_COL);
        cout << "\033[0m" << endl;
        } else cout << alignLeft(to_string(index), ' ', NO_COL)
                    << alignLeft(truncate(folderName,TITLE_COL), ' ', TITLE_COL)
                    << endl;
        index++;
    }
    View::alignLength();
    View::displayBottom();     
}

