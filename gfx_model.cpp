#include "gfx_model.hpp"

#include <vector>
#include <iostream>

GfxModel::GfxModel(std::string objFileName) {
    IndexedObject* obj = new IndexedObject();
    
    if(!obj->loadObjFile(objFileName))
        exit(-200);

    for (int n=0; n<obj->getISize(); n++) {
        geometry.push_back(obj->getVertices()[obj->getIndices()[n]*3]);
        geometry.push_back(obj->getVertices()[obj->getIndices()[n]*3+1]);
        geometry.push_back(obj->getVertices()[obj->getIndices()[n]*3+2]);
    }

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * geometry.size(), &geometry[0], GL_STATIC_DRAW);
    check();
    numVertices = geometry.size()/3;
    delete obj;
}

void GfxModel::draw(GfxShader* shaderProgram) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glEnableVertexAttribArray(shaderProgram->getAtrHandle("vertex"));
    glVertexAttribPointer(shaderProgram->getAtrHandle("vertex"), 3, GL_FLOAT, GL_TRUE, 0, /*&geometry[0]*/NULL);

    glDrawArrays(GL_TRIANGLES, 0, numVertices);
    //glDisableVertexAttribArray(shaderProgram->getAtrHandle("vertex"));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GfxModel::~GfxModel() {
    std::cout << "Model destructor called :O\n";
    glDeleteBuffers(1, &vbo);
    //glDeleteBuffers(1, &indexBuffer);
}
