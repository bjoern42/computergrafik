#ifndef VIEW_H
#define VIEW_H

#include "vec.h"
#include "mat.h"

class View{
	private:
		float fFocus;
		CVec4f eyePoint, viewZ, viewY;
		
		void init(CVec4f eyePoint, CVec4f viewZ, CVec4f viewY, float fFocus);
		
	public:
		View(float fFocus);
		View(CVec4f eyePoint, CVec4f viewZ, CVec4f viewY, float fFocus);
		~View();
		
		void setEyePoint(CVec4f v);
		void setViewZ(CVec4f v);
		void setViewY(CVec4f v);
		CVec4f getEyePoint();
		CVec4f getViewZ();
		CVec4f getViewY();
		CVec4f getViewX();
		void setFocus(float fFocus);
		float getFocus();
};

#endif // VIEW_H
