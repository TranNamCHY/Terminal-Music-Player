#pragma once
#include "View.h"
#include <iostream>
#include <vector>
#include "Song.h"
#include "ExtraVariableType.h"
using namespace std;

class EditMetadataView  : public View {
public:
    string display(Song s);
    string displayBottom();
    int line = 0;
};
