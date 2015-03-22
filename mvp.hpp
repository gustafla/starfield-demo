#ifndef MVP_HPP
#define MVP_HPP

#include "rpi_gfx.hpp"
#include "gfx_mat.hpp"

class MVP {
    public:
        MVP(GLfloat* _projection, GLfloat vtx=0.0f, GLfloat vty=0.0f, GLfloat vtz=0.0f, GLfloat vrx=0.0f, GLfloat vry=0.0f, GLfloat vrz=0.0f, GLfloat tx=0.0f, GLfloat ty=0.0f, GLfloat tz=0.0f, GLfloat rx=0.0f, GLfloat ry=0.0f, GLfloat rz=0.0f, GLfloat _scale=1.0f);
        void buildMVP();
        void buildModel();
        GLfloat mvp[16];
        void setProjection(GLfloat* _projection);
        
        void setView(GLfloat vtx=0.0f, GLfloat vty=0.0f, GLfloat vtz=0.0f, GLfloat vrx=0.0f, GLfloat vry=0.0f, GLfloat vrz=0.0f);
        void setViewTranslation(GLfloat vtx=0.0f, GLfloat vty=0.0f, GLfloat vtz=0.0f);
        void setViewRotation(GLfloat vrx=0.0f, GLfloat vry=0.0f, GLfloat vrz=0.0f);
        
        void setModel(GLfloat tx=0.0f, GLfloat ty=0.0f, GLfloat tz=0.0f, GLfloat rx=0.0f, GLfloat ry=0.0f, GLfloat rz=0.0f, GLfloat _scale=1.0f);
        void setModelTranslation(GLfloat tx=0.0f, GLfloat ty=0.0f, GLfloat tz=0.0f);
        void setModelRotation(GLfloat rx=0.0f, GLfloat ry=0.0f, GLfloat rz=0.0f);
        void setModelScale(GLfloat _scale=1.0f);
        
    private:
        GLfloat* projection;
        
        GLfloat viewt[16];
        GLfloat viewr[16];
        GLfloat view[16];
        
        GLfloat rotation[16];
        GLfloat scale[16];
        GLfloat translation[16];
        
        GLfloat model[16];
        GLfloat identity[16];
        GLfloat tmp[16];
};

#endif
