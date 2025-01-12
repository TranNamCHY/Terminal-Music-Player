#pragma once
#include <string>
#include <vector>
#include "MediaManager.h"

using namespace std;

/// @brief Store data of this program
class Model {
    Model();
public:

    /// @brief refrence to the unique instance of mediaManger.
    MediaManager& mediaManager;

    /// @brief Get Model reference, this aim to there is only one model when this program is executed.
    /// @return reference to a static Model. 
    static Model& getInstance();
};