#include "View.h"
#include <iostream>
#include "Song.h"
#include <math.h>
#include "display.h"
#include "ExtraVariableType.h"
int View::displayWidth(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
    auto utf16 = convert.from_bytes(str);
    return utf16.length();
}

std::string View::alignLeft(const std::string& str, const char& gap, int width) {
    std::locale::global(std::locale(""));
    int dataWidth = displayWidth(str);
    std::ostringstream oss;
    oss << std::left << std::setw(width + (str.length() - dataWidth)) << std::setfill(gap) << str;
    return oss.str();
}

std::string View::alignRight(const std::string& str, const char& gap, int width) {
    std::locale::global(std::locale(""));
    int dataWidth = displayWidth(str);
    std::ostringstream oss;
    oss << std::right << std::setw(width + (str.length() - dataWidth)) << std::setfill(gap) << str;
    return oss.str();
}

std::string View::alignMiddle(const std::string& str, const char& gap, int width) {
    std::locale::global(std::locale(""));
    int dataWidth = displayWidth(str);
    int leftWidth = (width - dataWidth) / 2;
    int rightWidth = width - dataWidth - leftWidth;
    std::ostringstream oss;
    oss << alignLeft("", gap, leftWidth) << "" << str << std::setw(rightWidth) << std::setfill(gap) << "";
    return oss.str();
}

string View::displayBottom() {
    string home = "-Home: [";
    home = home + HOME + "]";
    string goback = "Go back: [";
    goback = goback + GO_BACK + "]";
    string forward = "Forward: [";
    forward = forward + FORWARD + "]";
    string exit = "Exit: [";
    exit = exit + EXIT + "]-";
    string tempt;

    /* cout << alignLeft("",'-', WIDTH) << endl;
    cout << alignLeft(home,' ', WIDTH/4)
         << alignLeft(goback,' ', WIDTH/4)
         << alignRight(forward,' ', WIDTH/4)
         << alignRight(exit,' ', WIDTH/4)
         << endl;
    cout << alignLeft("",'-', WIDTH) << endl; */
    
    tempt = alignLeft("",'-', WIDTH) + "\n"
            + alignLeft(home,' ', WIDTH/4)
            + alignLeft(goback,' ', WIDTH/4)
            + alignRight(forward,' ', WIDTH/4)
            + alignRight(exit,' ', WIDTH/4)
            + "\n"
            + alignLeft("",'-', WIDTH)
            + "\n";

    // vector<string> option = {
    //     "-Home: [" + string(HOME) + "]",
    //     "Go back: [" + string(GO_BACK) + "]",
    //     "Forward: [" + string(FORWARD) + "]",
    //     "Exit: [" + string(EXIT) + "]-"
    // };
    // cout << alignLeft("",'-', WIDTH) << endl;
    // for(unsigned int i; i < option.size(); i++) {
    //     if(i < option.size()/2) cout << alignLeft(option[i],' ', WIDTH/4);
    //     else cout << alignRight(option[i],' ', WIDTH/4);
    // }
    // cout << endl;
    // cout << alignLeft("",'-', WIDTH) << endl;
    return tempt;
}

string View::display(Song s) {
     //system("clear");
     string tempt = "";
     tempt = "";
     tempt +=  alignMiddle(" MEDIA PLAYING ", '=', WIDTH) + "\n";
     tempt += "\n";
     int length = 2*ALIGN_COL + 1;
     tempt = tempt + "\n\n"
        + alignLeft("", ' ', LEFT_MARGIN)
        + "Metadata: \n"
        + alignLeft("", ' ', LEFT_MARGIN)
        + string(length , '-') + "\n" 
        + alignLeft("", ' ', LEFT_MARGIN)
        + alignLeft("| TITLE", ' ', ALIGN_COL) + alignLeft(truncate("| " + s.getTitle(),ALIGN_COL), ' ', ALIGN_COL) + "|\n"
        + alignLeft("", ' ', LEFT_MARGIN)
        + string(length, '-') + "\n"
        + alignLeft("", ' ', LEFT_MARGIN)
        + alignLeft("| ARTIST", ' ', ALIGN_COL) + alignLeft(truncate("| " + s.getArtist(), ALIGN_COL), ' ', ALIGN_COL) + "|\n"
        + alignLeft("", ' ', LEFT_MARGIN)
        + string(length, '-') + "\n"
        + alignLeft("", ' ', LEFT_MARGIN)
        + alignLeft("| ALBUM", ' ', ALIGN_COL) + alignLeft(truncate("| " + s.getAlbum(), ALIGN_COL), ' ', ALIGN_COL) + "|\n"
        + alignLeft("", ' ', LEFT_MARGIN)
        + string(length, '-') + "\n"
        + alignLeft("", ' ', LEFT_MARGIN) 
        + alignLeft("| DURATION", ' ', ALIGN_COL) + alignLeft(truncate("| " + s.getDuration(), ALIGN_COL), ' ', ALIGN_COL) + "|\n"
        + alignLeft("", ' ', LEFT_MARGIN)
        + string(length, '-') + "\n"
        + alignLeft("", ' ', LEFT_MARGIN)
        + alignLeft("| YEAR",' ', ALIGN_COL) + alignLeft(truncate("| " + s.getYear(), ALIGN_COL), ' ', ALIGN_COL) + "|\n"
        + alignLeft("", ' ', LEFT_MARGIN)
        + string(length, '-') + "\n"
        + "\n";  
     return tempt;
}

string View::alignLength() {
    //std::cout << "\033["<< LENGTH <<";0H";
    return "\033[" + to_string(LENGTH) + ";0H";
}

string View::truncate(const std::string& str, int width) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wide_str = converter.from_bytes(str);

    if (wide_str.length() <= (long unsigned int)(width - 1)) {
        return converter.to_bytes(wide_str); 
    
    } else {
        wide_str = wide_str.substr(0, width - 4);
        return converter.to_bytes(wide_str) + "...";
    }
}

string View::displayPlayingInfor(vector<Song> songs, int curPos) {
    std::string tempt = "";
    tempt = tempt + alignLeft("", ' ', LEFT_MARGIN*1.5) + "Playing list" + "\n" + "\n";
    for(int i = 0; i < (int)songs.size(); i++) {
        if (i != curPos) {
            tempt = tempt + alignLeft("", ' ', LEFT_MARGIN*1.5 + INDICATOR_COL)
                 +  songs[i].getTitle() + "\n";
        } else {
            tempt = tempt + alignLeft("", ' ', LEFT_MARGIN*1.5)
                 + alignLeft(">>>", ' ', INDICATOR_COL)
                 +  songs[i].getTitle() + "\n";
        }
    }
    return tempt;
}

vector<MultiType> View::displaySongs(vector<Song> songs, int pageNum, int size, int line, int highlight) {
    //system("clear");
    string tempt = "";
    std::vector<string> option;
    std::vector<MultiType> ResultList;
    /* cout << alignMiddle(" MEDIA LIST ", '=', WIDTH) << endl;
    cout << endl;
    cout << alignLeft("N0", ' ', NO_COL)
         << alignLeft("TITLE", ' ', TITLE_COL)
         << alignLeft("ARTIST", ' ', ARTIST_COL)
         << alignLeft("ALBUM", ' ', ALBUM_COL)
         << alignLeft("DURATION", ' ', DURATION_COL)
         << alignLeft("YEAR", ' ', YEAR_COL)
         << endl << endl; */
    tempt += alignMiddle(" MEDIA LIST ", '=', WIDTH) + "\n" + "\n";
    tempt = tempt + alignLeft("N0", ' ', NO_COL) +
                    alignLeft("TITLE", ' ', TITLE_COL) +
                    alignLeft("ARTIST", ' ', ARTIST_COL) +
                    alignLeft("ALBUM", ' ', ALBUM_COL) +
                    alignLeft("DURATION", ' ', DURATION_COL) +
                    alignLeft("YEAR", ' ', YEAR_COL) +
                    + "\n" + "\n";
    ResultList.push_back(tempt);
    unsigned num = songs.size();
    unsigned int count = pageNum * MAX_LINES + 1;
    for (auto it = songs.begin(); it != songs.end(); ++it) {
        tempt = "";
        if(((line % songs.size()) + 1 == count || (line % num) + 1 + MAX_LINES == count) && highlight == 0) {
            /* cout << "\033[30;47m";
            cout << alignLeft(to_string(count), ' ', NO_COL)
                << alignLeft(truncate((*it).getTitle(), TITLE_COL), ' ', TITLE_COL) 
                << alignLeft(truncate((*it).getArtist(), ARTIST_COL), ' ', ARTIST_COL) 
                << alignLeft(truncate((*it).getAlbum(), ALBUM_COL), ' ', ALBUM_COL)
                << alignLeft(truncate((*it).getDuration(), DURATION_COL), ' ', DURATION_COL)
                << alignLeft(truncate((*it).getYear(), YEAR_COL), ' ', YEAR_COL)
                << "\033[0m" << endl; */
            tempt += "\033[30;47m";
            tempt = tempt + alignLeft(to_string(count), ' ', NO_COL)
                + alignLeft(truncate((*it).getTitle(), TITLE_COL), ' ', TITLE_COL) 
                + alignLeft(truncate((*it).getArtist(), ARTIST_COL), ' ', ARTIST_COL) 
                + alignLeft(truncate((*it).getAlbum(), ALBUM_COL), ' ', ALBUM_COL)
                + alignLeft(truncate((*it).getDuration(), DURATION_COL), ' ', DURATION_COL)
                + alignLeft(truncate((*it).getYear(), YEAR_COL), ' ', YEAR_COL)
                + "\033[0m";
                //+ "\n";      
        } else {
            tempt = tempt + alignLeft(to_string(count), ' ', NO_COL)
                + alignLeft(truncate((*it).getTitle(), TITLE_COL), ' ', TITLE_COL) 
                + alignLeft(truncate((*it).getArtist(), ARTIST_COL), ' ', ARTIST_COL) 
                + alignLeft(truncate((*it).getAlbum(), ALBUM_COL), ' ', ALBUM_COL)
                + alignLeft(truncate((*it).getDuration(), DURATION_COL), ' ', DURATION_COL)
                + alignLeft(truncate((*it).getYear(), YEAR_COL), ' ', YEAR_COL);
                //+ "\n";
        }
        option.push_back(tempt);
        count++;
    }
    ResultList.push_back(option);
    tempt = "";
    tempt = tempt +  "\033[" +  std::to_string(LENGTH - 1)  + ";0H";
    tempt = tempt + "Page " + std::to_string(pageNum + 1) + " of " + std::to_string(ceil(size * 1.0 / MAX_LINES)) + "\n";
    ResultList.push_back(tempt);
    return ResultList;
}


void View::highlightLine(string str) {
    std::cout << "\033[30;47m";  // Chữ đen, nền trắng
    //std::cout << "\033[43m\033[30m"; // Set background to yellow, text to black
    std::cout << std::setw(WIDTH) << std::left << str;
    std::cout << "\033[0m" << std::endl;  // Reset lại màu sắc và kiểu chữ mặc định
    //std::cout << "\033[0m"; // Reset formatting
}

void View::highlightObj(string str) {
    std::cout << "\033[30;47m";  // Chữ đen, nền trắng
    std::cout << str;
    std::cout << "\033[0m";  // Reset lại màu sắc và kiểu chữ mặc định
}

