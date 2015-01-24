#include "gfx_model_handler.hpp"

GfxModel* GfxModelHandler::getModel(std::string name) {
    if (models.find(name) == models.end()) { //If there is no model name
        models[name] = new GfxModel(name);   //Create and map
    }
    return models[name]; //Give a pointer to the models in heap
}

bool GfxModelHandler::freeModel(std::string name) {
    if (models.find(name) == models.end()) { //If there is no model name
        return false;                        //Don't delete a nonexisting model
    }
    
    GfxModel* modelPtr = models[name];
    models.erase(name);
    delete modelPtr;
    
    return true;
}
