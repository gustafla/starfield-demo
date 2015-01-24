#include "gfx_model.hpp"

#define VERTEX_POS_INDEX 0

GfxModel::GfxModel(std::string objFileName) {
    IndexedObject* obj = new IndexedObject;
    
    if(!obj->loadObjFile(objFileName))
        exit(-200);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, obj->getVSize(), obj->getVertices(), GL_STATIC_DRAW);
    
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*obj->getISize(), obj->getIndices(), GL_STATIC_DRAW);
    
    numIndices = obj->getISize();
    delete obj;
};

void GfxModel::draw(GfxShader* shaderProgram) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    
    glEnableVertexAttribArray(VERTEX_POS_INDEX);
    glVertexAttribPointer(VERTEX_POS_INDEX, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindAttribLocation(shaderProgram->getHandle(), VERTEX_POS_INDEX, "vertex");
    
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
}

GfxModel::~GfxModel() {
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &indexBuffer);
}
