#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "vec.h"
#include "mat.h"
#include "View.h"
#include "Cuboid.h"
#include <math.h> 

class Transformation{
	public:
		static CVec2f rotate(CVec2f p, float degree);
		static CVec3f rotate(CVec3f p, float degree);
		static CVec2f translate(CVec2f vP, CVec2f vT);
		static CVec3f translate(CVec3f vP, CVec3f vT);
		static CVec3f rotateArroundVec(CVec3f p, CVec3f v, float degree);
		
		//3Dimensional stuff
		static CMat4f get3DTransMat(CVec4f vP, CVec4f vT);
		static CVec4f translate3D(CVec4f vP, CVec4f vT);
		static CMat4f get3DRotMatZAxis(CVec4f vP, float degree);
		static CMat4f get3DRotMatXAxis(CVec4f vP, float degree);
		static CMat4f get3DRotMatYAxis(CVec4f vP, float degree);
		static Cuboid* transform(Cuboid *c, CMat4f transformMat);
		static CMat4f getViewToWorldRotMat(View *view);
		static CMat4f getWorldToViewTransMat(View *view);
};

#endif // TRANSFORMATION_H
