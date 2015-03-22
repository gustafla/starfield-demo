#include "mvp.hpp"

MVP::MVP(GLfloat* _projection, GLfloat vtx, GLfloat vty, GLfloat vtz, GLfloat vrx, GLfloat vry, GLfloat vrz, GLfloat tx, GLfloat ty, GLfloat tz, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat _scale) {
    projection = _projection;
    getScaleMat(identity, 1.0f);
    getTranslationMat(viewt, vtx, vty, vtz);
    getXYZRotMat(viewr, vrx, vry, vrz);
    multMat4(view, viewt, viewr);
    
    getTranslationMat(translation, tx, ty, tz);
    getXYZRotMat(rotation, rx, ry, rz);
    getScaleMat(scale, _scale);
    buildModel();
    
    buildMVP();
}

void MVP::buildMVP() {
    multMat4(tmp, projection, view);
    multMat4(mvp, tmp, model);
}

void MVP::buildModel() {
    multMat4(tmp, translation, rotation);
    multMat4(model, tmp, scale);
}

void MVP::setProjection(GLfloat* _projection) {
    projection = _projection;
}

void MVP::setView(GLfloat vtx, GLfloat vty, GLfloat vtz, GLfloat vrx, GLfloat vry, GLfloat vrz) {
    getTranslationMat(viewt, vtx, vty, vtz);
    getXYZRotMat(viewr, vrx, vry, vrz);
    multMat4(view, viewt, viewr);
}

void MVP::setViewTranslation(GLfloat vtx, GLfloat vty, GLfloat vtz) {
    getTranslationMat(viewt, vtx, vty, vtz);
    multMat4(view, viewt, viewr);
}

void MVP::setViewRotation(GLfloat vrx, GLfloat vry, GLfloat vrz) {
    getXYZRotMat(viewr, vrx, vry, vrz);
    multMat4(view, viewt, viewr);
}

void MVP::setModel(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat _scale) {
    getTranslationMat(translation, tx, ty, tz);
    getXYZRotMat(rotation, rx, ry, rz);
    getScaleMat(scale, _scale);
    multMat4(tmp, translation, rotation);
    multMat4(model, tmp, scale);
}

void MVP::setModelTranslation(GLfloat tx, GLfloat ty, GLfloat tz) {
    getTranslationMat(translation, tx, ty, tz);
}

void MVP::setModelRotation(GLfloat rx, GLfloat ry, GLfloat rz) {
    getXYZRotMat(rotation, rx, ry, rz);
}
void MVP::setModelScale(GLfloat _scale) {
    getScaleMat(scale, _scale);
}

