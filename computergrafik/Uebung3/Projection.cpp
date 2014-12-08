#include "Projection.h"

Projection::Projection(){}


CVec4f Projection::projectZ(float fFocus, CVec4f pSicht){
	float p_Array[4][4];
	//[row][column]
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
	p_Array[2][2] = 1;
	p_Array[2][3] = 0;
	p_Array[3][0] = 0;
	p_Array[3][1] = 0;
	p_Array[3][2] = -(1/fFocus);
	p_Array[3][3] = 1;
	
	CMat4f p(p_Array);
	pSicht = p * pSicht;
	pSicht = pSicht * (1/(1 - pSicht(2)/fFocus));
	//pSicht = pSicht * (-fFocus/pSicht(2));
	return pSicht;
}

Cuboid* Projection::projektZ (float fFocus, Cuboid *cuboid){
	CVec4f *points = cuboid->getPoints();
	CVec4f projectedPoints[8];
	for(int i=0; i<8; i++){
		std::cout << "projektZ of point["<<i<<"]: (" << points[i](0) << "/" << points[i](1) << "/" << points[i](2) << ")";
		projectedPoints[i] = projectZ(fFocus, points[i]);
		std::cout << " -> (" << projectedPoints[i](0) << "/" << projectedPoints[i](1) << "/" << projectedPoints[i](2) << ")" << std::endl;
	}
	return new Cuboid(projectedPoints);
}