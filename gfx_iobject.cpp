#include "types.hpp"
#include "gfx_iobject.hpp"
#include <fstream>
#include <vector>
#include <iostream>
#include <cstdio>
#include <algorithm>

float* IndexedObject::getVertices() {
    return &vertices[0];
}

unsigned int* IndexedObject::getIndices() {
    return &indices[0];
}

int IndexedObject::getISize() {
    return indices.size();
}

int IndexedObject::getVSize() {
    return vertices.size();
}

bool IndexedObject::loadObjFile(const char* file) {
    std::vector<std::string*> coord;
    std::vector<vec3*> normals;

    std::ifstream in(file);
    if (!in.is_open()) {
        std::cout << file << ": no such file.\n";
        return false;
    }
    char buf[256];
    while (!in.eof()){
        in.getline(buf, 256);
        coord.push_back(new std::string(buf));
    }

    for (int i=0; i<coord.size(); i++) {
        if (coord[i]->c_str()[0]=='#')
            continue;
        else if (coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]==' ') {
            float tx, ty, tz;
            sscanf(coord[i]->c_str(), "v %f %f %f", &tx, &ty, &tz);
            std::cout << "Loader: Vertex: " << tx << " " << ty << " " << tz << std::endl;
            vertices.push_back(tx);
            vertices.push_back(ty);
            vertices.push_back(tz);
        } else if (coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]=='n') {
            float tx, ty, tz;
            sscanf(coord[i]->c_str(), "vn %f %f %f", &tx, &ty, &tz);
            normals.push_back(new vec3(tx, ty, tz));
        } else if (coord[i]->c_str()[0]=='f') {
            int a, b, c;
            if (count(coord[i]->begin(), coord[i]->end(), ' ') == 3) {
                sscanf(coord[i]->c_str(), "f %d %d %d", &a, &b, &c);
                std::cout << "Loader: Triangle indices: " << a << " " << b << " " << c << std::endl;
                indices.push_back(a-1);
                indices.push_back(b-1);
                indices.push_back(c-1);
            } else
                std::cout << "Loader: Skipped line " << i << ". Not a triangular face :(\n";
        } else if (coord[i]->c_str()[0]!='\n'||coord[i]->c_str()[0]!=' ') {
            std::cout << "Loader: Unrecognized: " << *coord[i] << std::endl;
            continue;
        }
    }
    return true;
}
