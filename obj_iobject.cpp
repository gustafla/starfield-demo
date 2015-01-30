// Copyright 2014 Lauri Gustafsson
/*
This file is part of [DEMO NAME].

    [DEMO NAME] is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    [DEMO NAME] is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with [DEMO NAME], see COPYING. If not, see <http://www.gnu.org/licenses/>.
*/

#include "types.hpp"
#include "obj_iobject.hpp"
#include <fstream>
#include <vector>
#include <iostream>
#include <cstdio>
#include <algorithm>

float* IndexedObject::getVertices() {
    return &vertices[0];
}

unsigned short* IndexedObject::getIndices() {
    return &indices[0];
}

int IndexedObject::getISize() {
    return indices.size();
}

int IndexedObject::getVSize() {
    return vertices.size();
}

bool IndexedObject::loadObjFile(std::string file) {
    std::vector<std::string*> coord;
    std::vector<vec3*> normals;

    std::ifstream in(file.c_str());
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
            //std::cout << "Loader: Vertex: " << tx << " " << ty << " " << tz << std::endl;
            vertices.push_back(tx);
            vertices.push_back(ty);
            vertices.push_back(tz);
        } else if (coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]=='n') {
            float tx, ty, tz;
            sscanf(coord[i]->c_str(), "vn %f %f %f", &tx, &ty, &tz);
            normals.push_back(new vec3(tx, ty, tz));
        } else if (coord[i]->c_str()[0]=='f') {
            unsigned short a, b, c;
            if (count(coord[i]->begin(), coord[i]->end(), ' ') == 3) {
                sscanf(coord[i]->c_str(), "f %d %d %d", &a, &b, &c);
                //std::cout << "Loader: Triangle indices: " << a << " " << b << " " << c << std::endl;
                indices.push_back(a-1);
                indices.push_back(b-1);
                indices.push_back(c-1);
            } else
                std::cout << "Loader: Skipped line " << i << ". Not a triangular face :(\n";
        } else if (coord[i]->c_str()[0]!='\n'||coord[i]->c_str()[0]!=' ') {
            //std::cout << "Loader: Unrecognized: " << *coord[i] << std::endl;
            continue;
        }
    }
    return true;
}
