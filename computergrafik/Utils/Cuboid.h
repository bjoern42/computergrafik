#ifndef CUBOID_H
#define CUBOID_H

#include "vec.h"
#include "mat.h"
#include "Color.hpp"

class Cuboid{
	private:
		CVec4f *points;
		float height, length, depth;
		Color color;
		
		float increaseBy(float init, float incr);
		void init(CVec4f origin, float length, float height, float depth, Color color);
		
	public:
		Cuboid(CVec4f origin, float length, float height, float depth, Color color);
		Cuboid(float x, float y, float z, float length, float height, float depth, Color color);
		Cuboid(CVec4f points[8], Color color);
		~Cuboid();
		CVec4f* getPoints();
		void printPoints();
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
		void setColor(Color color);
		Color getColor();
};

#endif // CUBOID_H
