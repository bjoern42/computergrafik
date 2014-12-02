#ifndef CUBOID_H
#define CUBOID_H

#include "vec.h"
#include "mat.h"

class Cuboid{
	private:
		CVec4f *points;
		float height, length, depth;
	public:
		Cuboid(CVec4f origin, float height, float length, float depth);
		~Cuboid();
		CVec4f* getPoints();
		float getHeight();
		float getLength();
		float getDepth();
};

#endif // CUBOID_H
