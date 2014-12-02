#include "Projection.h"

Projection::Projection(){}


CVec4f Projection::projectZ(float fFocus, CVec4f pSicht){
	float p_Array[4][4];
	p_Array[0][0] = 1;
	p_Array[0][1] = 0;
	p_Array[0][2] = 0;
	p_Array[0][3] = 0;
	p_Array[1][0] = 0;
	p_Array[1][1] = 1;
	p_Array[1][2] = 0;
	p_Array[1][3] = 0;
	p_Array[2][0] = 0;
	p_Array[2][1] = 0;
	p_Array[2][2] = 0;
	p_Array[2][3] = 0;
	p_Array[3][0] = 0;
	p_Array[3][1] = 0;
	p_Array[3][2] = -(1/fFocus);
	p_Array[3][3] = 1;
	
	CMat4f p(p_Array);
	
	return p*pSicht;
}

void Projection::projektZ (float fFocus, Cuboid *cuboid){
	CVec4f *points = cuboid->getPoints();
	for(int i=0; i<8; i++){
		points[i] = projectZ(fFocus, points[i]);
	}
}