#include "Transformation.h"

Transformation::Transformation(){
}

CVec2f Transformation::rotate(CVec2f p, float degree){
	float degree_rad = degree * M_PI / 180;
	float r_cos = cos(degree_rad);
	float r_sin = sin(degree_rad);
	
	float r_Array[2][2];
	r_Array[0][0] = r_cos;
	r_Array[0][1] = r_sin;
	r_Array[1][0] = -r_sin;
	r_Array[1][1] = r_cos;
	
	CMat2f r(r_Array);
	
	return r*p;
}

CVec2f Transformation::translate(CVec2f vP, CVec2f vT){	
	return vP + vT;
}

CVec3f Transformation::rotate(CVec3f p, float degree){
	float degree_rad = degree * M_PI / 180;
	float r_cos = cos(degree_rad);
	float r_sin = sin(degree_rad);
	
	float r_Array[3][3];
	r_Array[0][0] = r_cos;
	r_Array[0][1] = -r_sin;
	r_Array[0][2] = 0;
	r_Array[1][0] = r_sin;
	r_Array[1][1] = r_cos;
	r_Array[1][2] = 0;
	r_Array[2][0] = 0;
	r_Array[2][1] = 0;
	r_Array[2][2] = 1;
	
	CMat3f r(r_Array);
	
	return r*p;
}

CVec3f Transformation::translate(CVec3f vP, CVec3f vT){
	float t_Array[3][3];
	t_Array[0][0] = 1;
	t_Array[1][0] = 0;
	t_Array[2][0] = 0;
	t_Array[0][1] = 0;
	t_Array[1][1] = 1;
	t_Array[2][1] = 0;
	t_Array[0][2] = vT(0);
	t_Array[1][2] = vT(1);
	t_Array[2][2] = 1;
	CMat3f t(t_Array);
	return t*vP;
}

CVec3f Transformation::rotateArroundVec(CVec3f p, CVec3f v, float degree){
	float t_Array[3][3];
	t_Array[0][0] = 1;
	t_Array[1][0] = 0;
	t_Array[2][0] = 0;
	t_Array[0][1] = 0;
	t_Array[1][1] = 1;
	t_Array[2][1] = 0;
	t_Array[0][2] = v(0);
	t_Array[1][2] = v(1);
	t_Array[2][2] = 1;
	
	CMat3f t(t_Array);
	
	t_Array[0][2] = -v(0);
	t_Array[1][2] = -v(1);
	
	CMat3f t_inv(t_Array);
	
	float degree_rad = degree * M_PI / 180;
	float r_cos = cos(degree_rad);
	float r_sin = sin(degree_rad);
	
	float r_Array[3][3];
	r_Array[0][0] = r_cos;
	r_Array[0][1] = r_sin;
	r_Array[0][2] = 0;
	r_Array[1][0] = -r_sin;
	r_Array[1][1] = r_cos;
	r_Array[1][2] = 0;
	r_Array[2][0] = 0;
	r_Array[2][1] = 0;
	r_Array[2][2] = 1;
	
	CMat3f r(r_Array);
	
	return t*r*t_inv*p;
}
