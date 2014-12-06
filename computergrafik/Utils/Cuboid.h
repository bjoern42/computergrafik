#ifndef CUBOID_H
#define CUBOID_H

#include "vec.h"
#include "mat.h"

class Cuboid{
	private:
		CVec4f *points;
		float height, length, depth;
		float increaseBy(float init, float incr);
	public:
		Cuboid(CVec4f origin, float height, float length, float depth);
		~Cuboid();
		CVec4f* getPoints();
		CVec4f getFrontBottomLeft();
		CVec4f getFrontBottomRight();
		CVec4f getFrontTopLeft();
		CVec4f getFrontTopRight();
		CVec4f getBackBottomLeft();
		CVec4f getBackBottomRight();
		CVec4f getBackTopLeft();
		CVec4f getBackTopRight();
		float getHeight();
		float getLength();
		float getDepth();
};

#endif // CUBOID_H
