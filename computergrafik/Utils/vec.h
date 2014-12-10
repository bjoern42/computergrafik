#ifndef _VEC_H_
#define _VEC_H_

#include <stdio.h>
#include <iostream>
#include <math.h>

template<class T, unsigned SIZE> class CMatrix;

// Vector class for SIMPLE data types
template <class T, unsigned SIZE> class CVector {
public:

	// standard constructor
	CVector<T,SIZE> (){   
		// initialize all elements with zero
		for (int i=0; i<SIZE; i++){
			m_atData[i] = T(0);
		}
	}

	// construction with data array
	CVector<T, SIZE> (const T atData[SIZE]){
		for (int i=0; i<SIZE; i++) {
			m_atData[i] = atData[i];			
		}
	}

	// copy constructor
	CVector<T, SIZE> (const CVector<T, SIZE> &vec){
		if (this==&vec){ return; 
			// nothing to do, it's me
		}
		for (int i=0; i<SIZE; i++){
			m_atData[i] = vec.m_atData[i];
		}
	}

	// destructor
	~CVector (){	
		// nothing to do here ...
	}

	void setData (const T atData[SIZE]){
		for (int i=0; i<SIZE; i++){
			m_atData[i] = atData[i];
		} 
	}

	void getData (T atData[SIZE]){
		for (int i=0; i<SIZE; i++){
			atData[i] = m_atData[i];
		}	
	}

	unsigned getDimension (){
		return SIZE;
	}

	CVector<T, SIZE> &operator = (const CVector<T, SIZE> &vec) {
		if (this==&vec) {
			return (*this); // ok, it's me, so no L-value action
		}
		// not me, so L-Value action: copy data
		for (int i=0; i<SIZE; i++){		
			m_atData[i] = vec.m_atData[i];
		}

		return (*this); // also an R-value in e.g
						// vec1    =       vec2      = vec3;
						// L-Value = R-Value/L-Value = R-Value
	}

	CVector<T, SIZE> &operator = (const T atData[SIZE]){
		 // not me, so L-Value action: copy data
		for (int i=0; i<SIZE; i++){
			m_atData[i] = atData[i];
		}
		return (*this); // also an R-value in e.g.
						// vec1  = vec2  +   (vec2=atData); // parenthesis () needed to evaluate expression vec2=atData
						// L-Val = R-Val +       R-Val
						//   "   =   "   + (L-Val = R-Val)
	}

	// usage of operator:
	// vec(i) = var;	// 0 <= i <= SIZE-1
	// var = vec(i);
	// vec1(i) = vec2(j);
	T &operator () (unsigned i){
		if (i>=SIZE){
			i = SIZE-1;	// !!! operator clips index ...	
		} 
		return m_atData[i];			// ... so we can safely return a reference
	}

	T operator () (unsigned i) const {
		if (i>=SIZE){ 
			i = SIZE-1;
		}
		return m_atData[i];
	}

	void operator += (const CVector<T, SIZE> &vec){
		for (int i=0; i<SIZE; i++){
			m_atData[i] += vec.m_atData[i];
		} 
	}

	CVector<T, SIZE> operator + (const CVector<T, SIZE> &vec){
		CVector<T, SIZE> buf (m_atData);
		for (int i=0; i<SIZE; i++) {
			buf.m_atData[i] += vec.m_atData[i];
		}
		return buf;
	}

	void operator -= (const CVector<T, SIZE> &vec){
		for (int i=0; i<SIZE; i++){
			m_atData[i] -= vec.m_atData[i];
		} 
	}

	// binary -
	// vec1 - vec2 i.e. (*this) - vec
	CVector<T, SIZE> operator - (const CVector<T, SIZE> &vec) {
		CVector<T, SIZE> buf (m_atData);
		for (int i=0; i<SIZE; i++){
			buf.m_atData[i] -= vec.m_atData[i];
		} 
		return buf;
	}

	// unary -
	// -vec i.e. -(*this)
	CVector<T, SIZE> operator - () {
		T atBuffer[SIZE];
		for (int i=0; i<SIZE; i++) {
			atBuffer[i] = -m_atData[i];
		}
		return CVector<T, SIZE> (atBuffer);
	}

	T operator * (const CVector<T, SIZE> & vec){
		T dp = T(0);
		for (int i=0; i<SIZE; i++){
			dp += m_atData[i]*vec.m_atData[i];
		} 
		return dp;
	}

	void operator *= (T tScale) {
		for (int i=0; i<SIZE; i++){
			m_atData[i] *= tScale;
		} 
	}

	CVector<T, SIZE> operator * (T tScale) {
		T atBuffer[SIZE];
		for (int i=0; i<SIZE; i++){
			atBuffer[i] = m_atData[i]*tScale;
		} 
		return CVector<T, SIZE> (atBuffer);
	}

	CVector<T, SIZE> operator * (const CMatrix<T, SIZE> &mat) {
		CVector<T, SIZE> vec;
		for (int j=0; j<SIZE; j++){
			for (int i=0; i<SIZE; i++){
				vec(j) += m_atData[i]*mat(i,j);
			}
		}
		return vec;
	}

	void print(){
		std::cout << "(";
		for (int i=0; i<SIZE-1; i++){
			std::cout << m_atData[i] << ",";
		}
		std::cout << m_atData[SIZE-1] << ")^t";
	}
	
	T scalarProduct(CVector<T, SIZE> &b){
		T sProduct = 0;
		for(int i=0; i<getDimension(); i++){
			sProduct += m_atData[i] * b(i);
		}
		//std::cout << "sProduct: " << sProduct << "  " << sqrt(sProduct) << std::endl;
		return sqrt(sProduct);
	}

	CVector<T, SIZE> getNormedVector(){
		T sProduct = scalarProduct(*this);
		return (*this) * (1/sProduct);
	}

	CVector<T, SIZE> crossProduct3D(CVector<T, SIZE> &b){
		if(getDimension() < 3){
			return NULL;
		}
		
		CVector<T, SIZE> vec;
		
		vec(0) = m_atData[1] * b(2) - m_atData[2] * b(1);
		vec(1) = m_atData[2] * b(0) - m_atData[0] * b(2);
		vec(2) = m_atData[0] * b(1) - m_atData[1] * b(0);
		return vec;
	}
private:
	T m_atData[SIZE];

}; // class CVector


// some common vector classes (abbr. names)
typedef CVector<float, 2> CVec2f;
typedef CVector<float, 3> CVec3f;
typedef CVector<float, 4> CVec4f;

typedef CVector<double, 2> CVec2d;
typedef CVector<double, 3> CVec3d;
typedef CVector<double, 4> CVec4d;

typedef CVector<int, 2> CVec2i;
typedef CVector<int, 3> CVec3i;
typedef CVector<int, 4> CVec4i;

typedef CVector<bool, 2> CVec2b;
typedef CVector<bool, 3> CVec3b;
typedef CVector<bool, 4> CVec4b;

#endif
