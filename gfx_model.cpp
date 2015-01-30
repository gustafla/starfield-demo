#include "gfx_model.hpp"

#include <vector>
#include <iostream>

GfxModel::GfxModel(std::string objFileName, float* igeometry, unsigned int size, GLuint idrawmode):
drawmode(idrawmode) {
    IndexedObject* obj;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    if (igeometry == NULL) {
        obj = new IndexedObject();
    
        if(!obj->loadObjFile(objFileName))
            exit(-200);
            
        for (int n=0; n<obj->getISize(); n++) {
            geometry.push_back(obj->getVertices()[obj->getIndices()[n]*3]);
            geometry.push_back(obj->getVertices()[obj->getIndices()[n]*3+1]);
            geometry.push_back(obj->getVertices()[obj->getIndices()[n]*3+2]);
        }
        
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * geometry.size(), &geometry[0], GL_STATIC_DRAW);
        
        numVertices = geometry.size()/3;
        delete obj;
    }
    else {
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * size, igeometry, GL_STATIC_DRAW);
        numVertices = size/3;
    }
    check();
}

void GfxModel::draw(GfxShader* shaderProgram) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glEnableVertexAttribArray(shaderProgram->getAtrHandle("vertex"));
    glVertexAttribPointer(shaderProgram->getAtrHandle("vertex"), 3, GL_FLOAT, GL_TRUE, 0, /*&geometry[0]*/NULL);

    glDrawArrays(drawmode, 0, numVertices);
    //glDisableVertexAttribArray(shaderProgram->getAtrHandle("vertex"));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GfxModel::~GfxModel() {
    //std::cout << "Model destructor called :O\n";
    glDeleteBuffers(1, &vbo);
    //glDeleteBuffers(1, &indexBuffer);
}
