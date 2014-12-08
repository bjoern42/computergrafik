#ifndef CG_COLOR_H
#define CG_COLOR_H

class Color{
	private:
		void validate(float* x);
	public:
		float r, g, b;
		Color(float r=1.0f, float g=1.0f, float b=1.0f);
		void set(float r, float g, float b);
		void darken(float f);
		void lighten(float f);
};
#endif // COLOR_H
