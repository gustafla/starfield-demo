//Matrices will be just 1-dimensional arrays of float.

void getPProjMat(float* mat, float fov, float aspect/*w*/, float znear=1.0, float zfar=10.0);
void getXRotMat(float* mat, float a);
void getYRotMat(float* mat, float a);
void getZRotMat(float* mat, float a);
