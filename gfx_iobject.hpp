#include <vector>

class IndexedObject {
    public:
        float* getVertices/*Ptr*/();
        unsigned int* getIndices/*Ptr*/();/*
        std::vector<float>* getVertices();
        std::vector<unsigned int>* getIndices();*/
        int getISize();
        int getVSize();
        bool loadObjFile(const char* file);
    private:
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
};
