#include "gfx_model.hpp"
#include <cstdlib>
#include <vector>
#include <iostream>

GfxModel::GfxModel(std::string objFileName, float* igeometry, unsigned int size, GLuint idrawmode):
drawmode(idrawmode),
textured(false),
stride(0) {
    IndexedObject* obj;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    if (igeometry == NULL) {
        obj = new IndexedObject();
    
        if(!obj->loadObjFile(objFileName))
            exit(-200);
        
        if (!obj->getTSize()) {
            for (int n=0; n<obj->getISize(); n++) {
                geometry.push_back(obj->getVertices()[obj->getIndices()[n]*3]);
                geometry.push_back(obj->getVertices()[obj->getIndices()[n]*3+1]);
                geometry.push_back(obj->getVertices()[obj->getIndices()[n]*3+2]);
            }
        } else {
            textured = true;
            for (int n=0; n<obj->getISize(); n+=2) {
                geometry.push_back(obj->getVertices()[obj->getIndices()[n]*3]);
                geometry.push_back(obj->getVertices()[obj->getIndices()[n]*3+1]);
                geometry.push_back(obj->getVertices()[obj->getIndices()[n]*3+2]);
                geometry.push_back(obj->getTcoords()[obj->getIndices()[n+1]*3]);
                geometry.push_back(obj->getTcoords()[obj->getIndices()[n+1]*3+1]);
                geometry.push_back(obj->getTcoords()[obj->getIndices()[n+1]*3+2]);
            }
        }
        
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * geometry.size(), &geometry[0], GL_STATIC_DRAW);
        
        if (textured) {
            numVertices = geometry.size()/6;
            stride = 6;
        } else {
            numVertices = geometry.size()/3;
            stride = 3;
        }
        
        delete obj;
    }
    else {
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * size, igeometry, GL_STATIC_DRAW);
        numVertices = size/3;
    }
    check();
    geometry.clear(); //Don't need this anymore thanks to VBO
}

void GfxModel::draw(GfxShader* shaderProgram) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glEnableVertexAttribArray(shaderProgram->getAtrHandle("vertex"));
    glVertexAttribPointer(shaderProgram->getAtrHandle("vertex"), 3, GL_FLOAT, GL_TRUE, sizeof(GLfloat)*stride, INT2P(0));
    if (textured) {
        glEnableVertexAttribArray(shaderProgram->getAtrHandle("a_texpos"));
        glVertexAttribPointer(shaderProgram->getAtrHandle("a_texpos"), 3, GL_FLOAT, GL_TRUE, sizeof(GLfloat)*stride, INT2P(3));
    }

    glDrawArrays(drawmode, 0, numVertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GfxModel::draw(GfxShader* shaderProgram, float start) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glEnableVertexAttribArray(shaderProgram->getAtrHandle("vertex"));
    glVertexAttribPointer(shaderProgram->getAtrHandle("vertex"), 3, GL_FLOAT, GL_TRUE, sizeof(GLfloat)*stride, INT2P(0));
    if (textured) {
        glEnableVertexAttribArray(shaderProgram->getAtrHandle("a_texpos"));
        glVertexAttribPointer(shaderProgram->getAtrHandle("a_texpos"), 3, GL_FLOAT, GL_TRUE, sizeof(GLfloat)*stride, INT2P(3));
    }
    
    float s;
    if (start <= 0.0) {
        s=0.0;
        glDrawArrays(drawmode, 0, numVertices);
    }
    else {
        s=start;
        if (start > 1.0)
            s=1.0;
        glDrawArrays(drawmode, s*numVertices, numVertices-numVertices*s+1);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GfxModel::~GfxModel() {
    //std::cout << "Model destructor called :O\n";
    glDeleteBuffers(1, &vbo);
    //glDeleteBuffers(1, &indexBuffer);
}
