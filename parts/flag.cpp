#include "parts/flag.hpp" 

DemoFlag::DemoFlag(CommonData* icommon) {
    flag = new PointFlag(icommon);
}

DemoFlag::~DemoFlag() {
    delete flag;
}

void DemoFlag::draw() {
    flag->draw();
}
