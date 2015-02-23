// Copyright 2015 Lauri Gustafsson
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

IndexedObject::IndexedObject():
textured(false), nottextured(false) {}

float* IndexedObject::getVertices() {
    return &vertices[0];
}

float* IndexedObject::getTcoords() {
    return &tcoords[0];
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

int IndexedObject::getTSize() {
    if (textured)
        return tcoords.size();
    else return 0;
}

bool IndexedObject::loadObjFile(std::string file) {
    name = file;
    std::vector<std::string*> objLine;
    std::vector<vec3*> normals;

    std::ifstream in(file.c_str());
    if (!in.is_open()) {
        alarm("no such file.");
        return false;
    }
    char buf[256];
    while (!in.eof()){
        in.getline(buf, 256);
        objLine.push_back(new std::string(buf));
    }
    
    float tx, ty, tz;
    unsigned short a, b, c, d, e, f;
    
    for (int i=0; i<objLine.size(); i++) {
        if (objLine[i]->c_str()[0]=='#' || objLine[i]->c_str()[0]=='\n')
            continue;
        else if (objLine[i]->c_str()[0]=='v' && objLine[i]->c_str()[1]==' ') { //vertex
            sscanf(objLine[i]->c_str(), "v %f %f %f", &tx, &ty, &tz);
            alarm("Vertex: ", tx, " ", ty, " ", tz);
            vertices.push_back(tx);
            vertices.push_back(ty);
            vertices.push_back(tz);
        } else if (objLine[i]->c_str()[0]=='v' && objLine[i]->c_str()[1]=='n') { //normal (not usable for now)
            sscanf(objLine[i]->c_str(), "vn %f %f %f", &tx, &ty, &tz);
            normals.push_back(new vec3(tx, ty, tz));
        } else if (objLine[i]->c_str()[0]=='v' && objLine[i]->c_str()[1]=='t') { //texture coordinate
            if (count(objLine[i]->begin(), objLine[i]->end(), ' ') == 3) {
                sscanf(objLine[i]->c_str(), "vt %f %f %f", &tx, &ty, &tz);
                alarm("Texture coord: ", tx, " ", ty, " ", tz);
                tcoords.push_back(tx);
                tcoords.push_back(ty);
                tcoords.push_back(tz);
            } else if (count(objLine[i]->begin(), objLine[i]->end(), ' ') == 2) {
                sscanf(objLine[i]->c_str(), "vt %f %f", &tx, &ty);
                alarm("Texture coord: ", tx, " ", ty, " ", 0.0f);
                tcoords.push_back(tx);
                tcoords.push_back(ty);
                tcoords.push_back(0.0f);
            } else {
                alarm("Something wrong with line ", i, ".");
                exit(-200);
            }
        } else if (objLine[i]->c_str()[0]=='f') { //face
            if (count(objLine[i]->begin(), objLine[i]->end(), ' ') == 3) { //triangular face
                if (count(objLine[i]->begin(), objLine[i]->end(), '/') == 0) { //only vertex coords
                    nottextured = true;
                    sscanf(objLine[i]->c_str(), "f %d %d %d", &a, &b, &c);
                    alarm("Triangle indices: ", a, " ", b, " ", c);
                    indices.push_back(a-1);
                    indices.push_back(b-1);
                    indices.push_back(c-1);
                } else if (count(objLine[i]->begin(), objLine[i]->end(), '/') == 3) { //vertex coords + texture coords
                    textured = true;
                    sscanf(objLine[i]->c_str(), "f %d/%d %d/%d %d/%d", &a, &b, &c, &d, &e, &f);
                    alarm("Triangle indices and texture coord indices: ", a, " ", b, " ", c, " / ", d, " ", e, " ", f);
                    indices.push_back(a-1);
                    indices.push_back(b-1);
                    indices.push_back(c-1);
                    indices.push_back(d-1);
                    indices.push_back(e-1);
                    indices.push_back(f-1);
                } else 
                    alarm("Skipped line ", i, ". Face indices with normals not supported yet.");
            } else //not triangular face
                alarm("Skipped line ", i, ". Not a triangular face :(");
        } else {
            alarm("Unrecognized: " + *objLine[i]);
            continue;
        }
    }
    
    if (textured && nottextured) {
        alarm("Mixed textured and untextured indices not supported.");
        return false;
    }
    if (!textured && tcoords.size()) {
        alarm("Warning: Texture coords entirely unused.");
    }
    
    return true;
}

 //Don't look down there VVV :)
 //I should learn templates of something
void IndexedObject::alarm(std::string text) {
    std::cout << "Loader: " << name << ": " << text << std::endl;
}

void IndexedObject::alarm(std::string text, int i, std::string text2) {
    std::cout << "Loader: " << name << ": " << text << i << text2 << std::endl;
}

void IndexedObject::alarm(std::string t0, int i0, std::string t1, int i1, std::string t2, int i2, std::string t3, int i3, std::string t4, int i4, std::string t5, int i5) {
    std::cout << "Loader: " << name << ": " << t0 << i0 << t1 << i1 << t2 << i2 << t3 << i3 << t4 << i4 << t5 << i5 << std::endl;
}

void IndexedObject::alarm(std::string t0, int i0, std::string t1, int i1, std::string t2, int i2, std::string t3, int i3, std::string t4, int i4) {
    std::cout << "Loader: " << name << ": " << t0 << i0 << t1 << i1 << t2 << i2 << t3 << i3 << t4 << i4 << std::endl;
}

void IndexedObject::alarm(std::string t0, int i0, std::string t1, int i1, std::string t2, int i2, std::string t3, int i3) {
    std::cout << "Loader: " << name << ": " << t0 << i0 << t1 << i1 << t2 << i2 << t3 << i3 << std::endl;
}

void IndexedObject::alarm(std::string t0, int i0, std::string t1, int i1, std::string t2, int i2) {
    std::cout << "Loader: " << name << ": " << t0 << i0 << t1 << i1 << t2 << i2 << std::endl;
}

void IndexedObject::alarm(std::string t0, int i0, std::string t1, int i1) {
    std::cout << "Loader: " << name << ": " << t0 << i0 << t1 << i1 << std::endl;
}

void IndexedObject::alarm(std::string t0, int i0) {
    std::cout << "Loader: " << name << ": " << t0 << i0 << std::endl;
}

void IndexedObject::alarm(std::string text, float i, std::string text2) {
    std::cout << "Loader: " << name << ": " << text << i << text2 << std::endl;
}

void IndexedObject::alarm(std::string t0, float i0, std::string t1, float i1, std::string t2, float i2, std::string t3, float i3, std::string t4, float i4, std::string t5, float i5) {
    std::cout << "Loader: " << name << ": " << t0 << i0 << t1 << i1 << t2 << i2 << t3 << i3 << t4 << i4 << t5 << i5 << std::endl;
}

void IndexedObject::alarm(std::string t0, float i0, std::string t1, float i1, std::string t2, float i2, std::string t3, float i3, std::string t4, float i4) {
    std::cout << "Loader: " << name << ": " << t0 << i0 << t1 << i1 << t2 << i2 << t3 << i3 << t4 << i4 << std::endl;
}

void IndexedObject::alarm(std::string t0, float i0, std::string t1, float i1, std::string t2, float i2, std::string t3, float i3) {
    std::cout << "Loader: " << name << ": " << t0 << i0 << t1 << i1 << t2 << i2 << t3 << i3 << std::endl;
}

void IndexedObject::alarm(std::string t0, float i0, std::string t1, float i1, std::string t2, float i2) {
    std::cout << "Loader: " << name << ": " << t0 << i0 << t1 << i1 << t2 << i2 << std::endl;
}

void IndexedObject::alarm(std::string t0, float i0, std::string t1, float i1) {
    std::cout << "Loader: " << name << ": " << t0 << i0 << t1 << i1 << std::endl;
}

void IndexedObject::alarm(std::string t0, float i0) {
    std::cout << "Loader: " << name << ": " << t0 << i0 << std::endl;
}
