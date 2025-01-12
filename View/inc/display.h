#ifndef DISPLAY_H
#define DISPLAY_H

#define MAX_LINES 25
#define WIDTH 100
#define LENGTH MAX_LINES+7

/*
    Define navigator letters
*/
#define HOME "h"
#define GO_BACK "<"
#define FORWARD ">"
#define EXIT "x"
#define CREATE "c"
#define DELETE "d"

/*
    Define
*/
#define MAX_HISTORY_PAGE 10
#define NEXT_PAGE "n"
#define PREVIOUS_PAGE "p"
#define SORT_BY_NAME "s"
#define SORT_BY_ARTIST "a"

enum PLAYOPTION {
    REPLAY,
    PAUSE,
    RESUME,
    EDIT_META_DATA,
    NEXT,
    PREVIOUS,
    VOLUME_UP,
    VOLUME_DOWN,
    SET_VOLUME = 30
};

/* 
Define column size
*/
#define NO_COL WIDTH/20
#define TITLE_COL WIDTH*3/10
#define ARTIST_COL WIDTH/4
#define ALBUM_COL WIDTH/4
#define DURATION_COL WIDTH/10
#define YEAR_COL WIDTH/20
#define INDICATOR_COL WIDTH/20

#define ALIGN_COL WIDTH*3/10
#define LEFT_MARGIN WIDTH*1/5

#define SONG_NUM_SHOW 7
    
#endif
