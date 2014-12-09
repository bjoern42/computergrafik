#include "Transformation.h"

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

//3Dimensional stuff
CMat4f Transformation::get3DTransMat(CVec4f vP, CVec4f vT){
	//[row][column]
	float t_Array[4][4];
	t_Array[0][0] = 1;
	t_Array[0][1] = 0;
	t_Array[0][2] = 0;
	t_Array[0][3] = vT(0);
	t_Array[1][0] = 0;
	t_Array[1][1] = 1;
	t_Array[1][2] = 0;
	t_Array[1][3] = vT(1);
	t_Array[2][0] = 0;
	t_Array[2][1] = 0;
	t_Array[2][2] = 1;
	t_Array[2][3] = vT(2);
	t_Array[3][0] = 0;
	t_Array[3][1] = 0;
	t_Array[3][2] = 0;
	t_Array[3][3] = 1;
	return CMat4f(t_Array);
}

CVec4f Transformation::translate3D(CVec4f vP, CVec4f vT){
	CMat4f transMat = get3DTransMat(vP, vT);
	return transMat * vP;
}

CMat4f Transformation::get3DRotMatZAxis(CVec4f vP, float degree){
	float degree_rad = degree * M_PI / 180;
	float r_cos = cos(degree_rad);
	float r_sin = sin(degree_rad);
	float t_Array[4][4];
	
	t_Array[0][0] = r_cos;
	t_Array[0][1] = -r_sin;
	t_Array[0][2] = 0;
	t_Array[0][3] = 0;
	t_Array[1][0] = r_sin;
	t_Array[1][1] = r_cos;
	t_Array[1][2] = 0;
	t_Array[1][3] = 0;
	t_Array[2][0] = 0;
	t_Array[2][1] = 0;
	t_Array[2][2] = 1;
	t_Array[2][3] = 0;
	t_Array[3][0] = 0;
	t_Array[3][1] = 0;
	t_Array[3][2] = 0;
	t_Array[3][3] = 1;
	return CMat4f(t_Array);
}

CMat4f Transformation::get3DRotMatXAxis(CVec4f vP, float degree){
	float degree_rad = degree * M_PI / 180;
	float r_cos = cos(degree_rad);
	float r_sin = sin(degree_rad);
	float t_Array[4][4];
	
	t_Array[0][0] = 1;
	t_Array[0][1] = 0;
	t_Array[0][2] = 0;
	t_Array[0][3] = 0;
	t_Array[1][0] = 0;
	t_Array[1][1] = r_cos;
	t_Array[1][2] = -r_sin;
	t_Array[1][3] = 0;
	t_Array[2][0] = 0;
	t_Array[2][1] = r_sin;
	t_Array[2][2] = r_cos;
	t_Array[2][3] = 0;
	t_Array[3][0] = 0;
	t_Array[3][1] = 0;
	t_Array[3][2] = 0;
	t_Array[3][3] = 1;
	return CMat4f(t_Array);
}

CMat4f Transformation::get3DRotMatYAxis(CVec4f vP, float degree){
	float degree_rad = degree * M_PI / 180;
	float r_cos = cos(degree_rad);
	float r_sin = sin(degree_rad);
	float t_Array[4][4];
	
	t_Array[0][0] = r_cos;
	t_Array[0][1] = 0;
	t_Array[0][2] = r_sin;
	t_Array[0][3] = 0;
	t_Array[1][0] = 0;
	t_Array[1][1] = 1;
	t_Array[1][2] = 0;
	t_Array[1][3] = 0;
	t_Array[2][0] = -r_sin;
	t_Array[2][1] = 0;
	t_Array[2][2] = r_cos;
	t_Array[2][3] = 0;
	t_Array[3][0] = 0;
	t_Array[3][1] = 0;
	t_Array[3][2] = 0;
	t_Array[3][3] = 1;
	return CMat4f(t_Array);
}

CMat4f Transformation::get3DRotMat(CVec4f vP, float degree){
	float degree_rad = degree * M_PI / 180;
	float r_cos = cos(degree_rad);
	float r_sin = sin(degree_rad);
	float t_Array[4][4];
	
	CMat4f zAxisRot = get3DRotMatZAxis(vP, degree);
	CMat4f xAxisRot = get3DRotMatXAxis(vP, degree);
	CMat4f yAxisRot = get3DRotMatYAxis(vP, degree);
	
	return zAxisRot * xAxisRot * yAxisRot;
}

CVec4f Transformation::rotate3D(CVec4f vP, float degree){
	CMat4f rotMat = get3DRotMat(vP, degree);
	CMat4f transMat = get3DTransMat(vP, -vP);
	CMat4f transMat_inv = get3DTransMat(vP, vP);
	return transMat * rotMat * transMat_inv * vP;
}

CMat4f Transformation::getViewToWorldRotMat(View *view){
	CVec4f x = view->getViewX().getNormedVector(3);
	CVec4f y = view->getViewY().getNormedVector(3);
	CVec4f z = view->getViewZ().getNormedVector(3);

	CMat4f rotMat;
	for(int i=0; i<3; i++){
		rotMat(0, i) = x(i);
	}
	for(int i=0; i<3; i++){
		rotMat(1, i) = y(i);
	}
	for(int i=0; i<3; i++){
		rotMat(2, i) = z(i);
	}

	rotMat(3,3) = 1;
	
	return rotMat;
}

Cuboid* Transformation::rotate(Cuboid *c, float degree, CMat4f (*getRotMat)(CVec4f v, float f)){
	CVec4f *points = c->getPoints();
	CVec4f transformatedPoints[8];
	for(int i=0; i<8; i++){
		CMat4f rotMat = get3DRotMat(points[i], degree);
		CMat4f transMat = get3DTransMat(points[i], -points[i]);
		CMat4f transMat_inv = get3DTransMat(points[i], points[i]);
		transformatedPoints[i] = transMat * rotMat * transMat_inv * points[i];
	}
	return new Cuboid(transformatedPoints);
}

Cuboid* Transformation::transform(Cuboid *c, CMat4f transformMat){
	CVec4f *points = c->getPoints();
	CVec4f transformatedPoints[8];
	for(int i=0; i<8; i++){
		transformatedPoints[i] = transformMat * points[i];
	}
	return new Cuboid(transformatedPoints);
}
		
CMat4f Transformation::getViewToWorldTransMat(View *view){
	CVec4f eyePoint = view->getEyePoint();

	CMat4f transMat = get3DTransMat(eyePoint, -eyePoint);

	CMat4f rotMat = getViewToWorldRotMat(view);
	
	return transMat * rotMat;
}

CMat4f Transformation::getWorldToViewTransMat(View *view){
	CVec4f eyePoint = view->getEyePoint();

	CMat4f transMat = get3DTransMat(eyePoint, eyePoint);
	CMat4f rotMat = getViewToWorldRotMat(view);
	
	return transMat * rotMat.transpose();
}