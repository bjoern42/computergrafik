#ifndef PROJECTION_H
#define PROJECTION_H

#include "Cuboid.h"

class Projection{
	public:
		static CVec4f projectZ(float fFocus, CVec4f pSicht);
		static Cuboid* projektZ(float fFocus, Cuboid *cuboid);
		static CVec4f projectZallg(CMat4f transformationMat, float fFocus, CVec4f pWorld);
		static Cuboid* projektZallg (CMat4f transformationMat, float fFocus, Cuboid *cuboid);
};

#endif // PROJECTION_H
