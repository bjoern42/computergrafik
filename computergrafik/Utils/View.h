#ifndef VIEW_H
#define VIEW_H

#include "vec.h"
#include "mat.h"

class View{
	private:
		float fFocus;
		CVec4f eyePoint, viewZ, viewY;
		
	public:
		View(CVec4f eyePoint, CVec4f viewZ, CVec4f viewY);
		~View();
		CVec4f getEyePoint();
		CVec4f getViewZ();
		CVec4f getViewY();
		CVec4f getViewX();
		void setEyePoint(CVec4f v);
		void setViewZ(CVec4f v);
		void setViewY(CVec4f v);
		void setFocus(float fFocus);
		float getFocus();
};

#endif // VIEW_H
