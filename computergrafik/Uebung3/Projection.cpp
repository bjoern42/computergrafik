#include "Projection.h"

Projection::Projection(){}


CVec4f Projection::projectZ(float fFocus, CVec4f pSicht){
	float p_Array[4][4];
	float z = pSicht(2);
	float delta_z = fFocus - z;
	
	p_Array[0][0] = fFocus/delta_z;
	p_Array[0][1] = 0;
	p_Array[0][2] = 0;
	p_Array[0][3] = 0;
	p_Array[1][0] = 0;
	p_Array[1][1] = fFocus/delta_z;
	p_Array[1][2] = 0;
	p_Array[1][3] = 0;
	p_Array[2][0] = 0;
	p_Array[2][1] = 0;
	p_Array[2][2] = 0;
	p_Array[2][3] = 0;
	p_Array[3][0] = 0;
	p_Array[3][1] = 0;
	p_Array[3][2] = 0;
	p_Array[3][3] = 1;

	CMat4f p(p_Array);
	
	return p*pSicht;
}

void Projection::projektZ (float fFocus, Cuboid *cuboid){
	CVec4f *points = cuboid->getPoints();
	for(int i=0; i<8; i++){
		std::cout << "before["<<i<<"] :" << points[i](0) << "/" << points[i](1) << "/" << points[i](2) << std::endl;
		points[i] = projectZ(fFocus, points[i]);
		std::cout << "after["<<i<<"] :" << points[i](0) << "/" << points[i](1) << "/" << points[i](2) << std::endl;
	}
}