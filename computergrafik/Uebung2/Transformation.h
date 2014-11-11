#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "vec.h"
#include "mat.h"
#include <math.h> 

class Transformation
{
public:
	Transformation();
	static CVec2f rotate(CVec2f p, float degree);
	static CVec3f rotate(CVec3f p, float degree);
	static CVec2f translate(CVec2f vP, CVec2f vT);
	static CVec3f translate(CVec3f vP, CVec3f vT);
	static CVec3f rotateArroundVec(CVec3f p, CVec3f v, float degree);
};

#endif // TRANSFORMATION_H
