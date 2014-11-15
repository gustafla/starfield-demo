#ifndef DEMO_FLAG_HPP
#define DEMO_FLAG_HPP

#include "common.hpp"
#include "effects/point_flag.hpp"
#include "rpi_gfx.hpp"

class DemoFlag{
	public:
		DemoFlag(CommonData* icommon);
		~DemoFlag();
		void draw();
	private:
		PointFlag* flag;
};

#endif
