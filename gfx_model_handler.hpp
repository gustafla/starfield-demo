#ifndef GFX_MODEL_HANDLER_HPP
#define GFX_MODEL_HANDLER_HPP

#include <vector>
#include <map>
#include <string>
#include "gfx_model.hpp"

class GfxModelHandler {
    public:
        GfxModel* getModel(std::string name);
        bool freeModel(std::string name);
    private:
        std::map<std::string, GfxModel*> models;
};

#endif
