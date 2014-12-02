#ifndef PROJECTION_H
#define PROJECTION_H

#include <Cuboid.h>

class Projection{
	public:
		Projection();
		CVec4f projectZ(float fFocus, CVec4f pSicht);
		void projektZ(float fFocus, Cuboid *cuboid);
};

#endif // PROJECTION_H
