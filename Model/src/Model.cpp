#include "Model.h"

Model::Model() : mediaManager(MediaManager::getInstance()) {}

Model& Model::getInstance() {
    static Model m = Model();
    return m;
}
