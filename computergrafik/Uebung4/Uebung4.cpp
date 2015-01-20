#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;

// might be you have to swith to
// #include "glut.h" depending on your GLUT installation
#include "GL/glut.h"

#include "vec.h"



/////////////////////////////////////////////////////////////////////////////////////////
//
// Hier wird einiges initialisiert. Sie dürfen sich gerne den Code anschauen und
// versuchen ihn zu verstehen. Das sollte Ihnen nicht allzu schwer fallen. Es werden
// jedoch einige Techniken benutzt (Texturen, ...) die wir in der Vorlesung noch
// nicht besprochen haben, die wir aber aus techn. Gründen hier benötigen.
//
// Weiter unten finden Sie einen Vermerk, ab dem Sie den Code jedoch vollständig
// verstehen sollten!!!


// Auflösungen der gesamten Textur
// !!!ACHTUNG!!! nicht alle Texturauflösungen funktionieren!
// Stichwort ungefähr: POT2 Problematik
#define TEX_RES_X 400
#define TEX_RES_Y 400
// Anzahl der Pixel der Textur
#define TEX_RES TEX_RES_X*TEX_RES_Y
// Achsenlänge der Textur (Achsen sind asymmetrisch von -TexRes#/2 bis TexRes#/2-1)

// Konvertiert Indices von (x,y) Koordinaten in ein lineares Array
#define TO_LINEAR(x, y) (((x)) + TEX_RES_X*((y)))

#define PI 3.1415926535

#define max(a ,b) (((a) > (b)) ? (a) : (b))
#define min(a ,b) (((a) < (b)) ? (a) : (b))

/////////////////////////////////////////////////////////////

// globaler Speicher für Texturdaten
char g_Buffer[3*TEX_RES];
// Textur ID Name
GLuint g_TexID = 0;

// Auflösung des Hauptfensters (kann sich durch User ändern)
int g_WinWidth = 400;
int g_WinHeight = 400;


// Kugel
// Kugel soll auf Z-Achse zentriert sein -> Mittelpunkt Kugel = (0,0,M)
int M= 100;
int R= 50;

const int R_INTERVAL = 1;
const int R_MIN = 1;
const int R_MAX = 200;

float rK= 1.0f;
float gK= 1.0f;
float bK= 1.0f;

const float RGB_MIN = 0.0f;
const float RGB_MAX = 255.0f;
const float RGB_INTERVAL = 5.0f;

// Licht
float xL= 0;
float yL= 1000;
float zL= 0;
float angleYZ;
float angleXZ;
float radL= 1000;

// Augpunkt
int A= -1;


//
/////////////////////////////////////////////////////////////////////////////////////////
//


// Eine überaus primitive Punktklasse
class Point {
public:

	Point (int x=0, int y=0) {
		this->x = x;
		this->y = y;
	}

	int x, y;
};

// Eine überaus primitive Farbklasse
class Color {
public:

	Color (float r=1.0f, float g=1.0f, float b=1.0f) {
		this->r = r;
		this->g = g;
		this->b = b;
	}

	float r, g, b;

	void print(char * name = "c") {
		cout << name << " = (" << r << ", " << g << ", " << b << ")" << endl;
	}
};

//
/////////////////////////////////////////////////////////////////////////////////////////
//


// Funktion organisiert die Textur.
// Kümmern Sie sich nicht weiter um diese Funktion, da
// sie momentan nur ein notwendiges Übel darstellt!
void manageTexture () {

	glEnable (GL_TEXTURE_2D);

	if (g_TexID==0)
		glGenTextures (1, &g_TexID);

	glBindTexture (GL_TEXTURE_2D, g_TexID);

	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, TEX_RES_X, TEX_RES_Y, 0, GL_RGB, GL_UNSIGNED_BYTE, g_Buffer);
	
	glBindTexture (GL_TEXTURE_2D, 0);

	glDisable (GL_TEXTURE_2D);
}

void mapTexture() {
	glBindTexture (GL_TEXTURE_2D, g_TexID);
	
	glEnable (GL_TEXTURE_2D);
	glBegin (GL_QUADS);
		glColor3f (1, 0, 0);
		glTexCoord2f (0, 0);
		glVertex2f (-g_WinWidth/2, -g_WinHeight/2);
		glTexCoord2f (1, 0);
		glVertex2f (g_WinWidth/2, -g_WinHeight/2);
		glTexCoord2f (1, 1);
		glVertex2f (g_WinWidth/2, g_WinHeight/2);
		glTexCoord2f (0, 1);
		glVertex2f (-g_WinWidth/2, g_WinHeight/2);
	glEnd ();

	glBindTexture (GL_TEXTURE_2D, 0);
	glDisable (GL_TEXTURE_2D);
}

// Callback Funktion um die Fenstergrößen anzupassen.
// Auch diese Funktion ist ein notwendiges Übel! Kümmern
// Sie sich im Moment nicht weiter darum.
void reshape(int w, int h) {

	g_WinWidth = w;
	g_WinHeight = h;

	glViewport(0, 0, w, h);					// Establish viewing area to cover entire window.

	glMatrixMode(GL_PROJECTION);			// Start modifying the projection matrix.
	glLoadIdentity();						// Reset project matrix.
	glOrtho(-w/2, w/2, -h/2, h/2, 0, 1);	// Map abstract coords directly to window coords.

	glutPostRedisplay ();
}

// Funktion löscht den Bildschirm mit der angegebenen Farbe
// Usage z.B.: clearImage (Color (1,1,1))
// löscht den Bildschirm in Weiß.
// Ohne Farbangabe ist der Standard Weiß
void clearTexture (Color c=Color()) {
	for (int i=0; i<TEX_RES; i++) {
		g_Buffer[3*i  ] = 255.0*c.r;
		g_Buffer[3*i+1] = 255.0*c.g;
		g_Buffer[3*i+2] = 255.0*c.b;
	}
}

// Funktion malt einen Punkt an die angegebenen Koordinaten
// Usage z.B.: addPoint (Point(10, 5), Color (1,0,0))
// malt einen Punkt an die Koordinate (10, 5)
// Ohne Farbangabe ist die standard Malfarbe Schwarz
//
// Nutzen Sie diese Funktion ...
void setPoint (Point p, Color c= Color(0,0,0)) {
	if (p.x < 0 || p.y < 0 || p.x > TEX_RES_X -1 || p.y > TEX_RES_Y -1) {
		cerr << "Illegal point co-ordinates (" << p.x << ", " << p.y << ")\n" << flush;
		return;
	}
	
	//cout << "test (" << p.x << "/" << p.y << ")" << 3*TO_LINEAR (p.x, p.y) << endl;
	g_Buffer[3*TO_LINEAR (p.x, p.y)  ] = 255.0*c.r;
	g_Buffer[3*TO_LINEAR (p.x, p.y)+1] = 255.0*c.g;
	g_Buffer[3*TO_LINEAR (p.x, p.y)+2] = 255.0*c.b;
}

void setQuad(Point p, Color c) {
	for (int x= p.x; x < p.x+10; x++){
		for (int y= p.y; y < p.y+10; y++){
			setPoint(Point(x,y),c);
		}
	}
}

//
/////////////////////////////////////////////////////////////////////////////////////////
//

float solveQuadraticABCFormula(float a, float b, float c){
	if(a == 0){
		return -1;
	}
	float tmp = b*b - 4 * a * c;
	if(tmp >= 0){
		float sqrtRoot = sqrt(tmp);
		float x1 = (-b + sqrtRoot) / (2 * a);
		float x2 = (-b - sqrtRoot) / (2 * a);
		
		//return min positive of x1, x2
		tmp = min(x1, x2);
		if(tmp < 0){
			tmp = max(x1, x2);
			if(tmp < 0){
				return -1;
			}
		}
		return tmp;
	}
	return -1;
}

CVec3f intersect (CVec3f EyePos, CVec3f ViewDir) {
	CVec3f hit;
	CVec3f sphereOrigin;
	//Auf Z-Achse zentriert -> (0,0,M)
	sphereOrigin(2) = M;
	
	// x1,2 = v²*t² + 2*v*(e-m)*t + (e-m)²-r²
	float a = ViewDir * ViewDir;
	float b = 2 * (ViewDir * (EyePos - sphereOrigin));
	float c = (EyePos - sphereOrigin) * (EyePos - sphereOrigin) - R * R;
	
	float t = solveQuadraticABCFormula(a, b, c);
	if(t == -1){
		hit(2) = -1;
	}else{
		hit = EyePos + ViewDir * t;
	}
	return hit;
}

Color phong(CVec3f HitPos, CVec3f ViewDir) {
	
// Phong-Parameter
	
	//Reflexionskoeffizienten fuer die Kugelfarben
	CVec3f Ka;		// ambient
	Ka(0)= rK;
	Ka(1)= gK;
	Ka(2)= bK;

	CVec3f Kd;		// diffuse
	Kd(0)= rK;
	Kd(1)= gK;
	Kd(2)= bK;

	CVec3f Ks;		// specular
	Ks(0)= 0.5;
	Ks(1)= 0.5;
	Ks(2)= 0.5;

	int exp= 28;	       // shininess

	//andere Reflexionskoeffizienten
	//////////////////
/*	// Messing
	CVec3f Ka;
	Ka(0)= 0.33;
	Ka(1)= 0.22;
	Ka(2)= 0.03;

	CVec3f Kd;
	Kd(0)= 0.78;
	Kd(0)= 0.57;
	Kd(0)= 0.11;

	CVec3f Ks;
	Ks(0)= 0.99;
	Ks(1)= 0.94;
	Ks(2)= 0.81;

	int exp= 28;
*/
/*	//////////////////
	// Bronze
	CVec3f Ka;
	Ka(0)= 0.21;
	Ka(1)= 0.13;
	Ka(2)= 0.05;

	CVec3f Kd;
	Kd(0)= 0.71;
	Kd(0)= 0.43;
	Kd(0)= 0.18;

	CVec3f Ks;
	Ks(0)= 0.39;
	Ks(1)= 0.27;
	Ks(2)= 0.17;
	
	int exp= 26;
	//////////////////
*/

	// Beleuchtungsstaerken
	///////////////////////
	CVec3f Ia;		// ambient
	Ia(0)= 0.1;
	Ia(1)= 0.1;
	Ia(2)= 0.1;
	
	CVec3f Id;		// diffuse
	Id(0)= 1.0;
	Id(1)= 1.0;
	Id(2)= 1.0;
	
	CVec3f Is;		// specular
	Is(0)= 1.0;
	Is(1)= 1.0;
	Is(2)= 1.0;
	///////////////////////

	
	CVec3f lightOrigin;
	lightOrigin(0) = xL;
	lightOrigin(1) = yL; 
	lightOrigin(2) = zL;
	
	//genormter Richtungsvektor des Lichts
	CVec3f L = (lightOrigin - HitPos).getNormedVector();
	
	CVec3f sphereOrigin;
	//Auf Z-Achse zentriert -> (0,0,M)
	sphereOrigin(2) = M;

	CVec3f N = (HitPos - sphereOrigin).getNormedVector();
	CVec3f V = ViewDir.getNormedVector();
	
	float tmp;
	tmp = L * N;
	tmp = max(0, tmp);

	CVec3f R = N * tmp * 2 - L;
	R=R.getNormedVector();
	
	CVec3f IDiff, ISpec, IAmb, IGes;
	//diffuse
	//tmp = L * N;
	//tmp = max(0, tmp);

	IDiff(0) = tmp * Id(0) * Kd(0);
	IDiff(1) = tmp * Id(1) * Kd(1);
	IDiff(2) = tmp * Id(2) * Kd(2);
	
	//specular
	tmp = pow((R * V), exp);
	tmp = max(0, tmp);
	ISpec(0) = tmp * Is(0) * Ks(0);
	ISpec(1) = tmp * Is(1) * Ks(1);
	ISpec(2) = tmp * Is(2) * Ks(2);
	
	//ambient
	IAmb(0) = Ia(0) * Ka(0);
	IAmb(1) = Ia(1) * Ka(1);
	IAmb(2) = Ia(2) * Ka(2);
	
	IGes(0) = IDiff(0) + ISpec(0) + IAmb(0);
	IGes(1) = IDiff(1) + ISpec(1) + IAmb(1);
	IGes(2) = IDiff(2) + ISpec(2) + IAmb(2);
	
	IGes(0) = min(1, max(0, IGes(0)));
	IGes(1) = min(1, max(0, IGes(1)));
	IGes(2) = min(1, max(0, IGes(2)));
	
	Color c(IGes(0), IGes(1), IGes(2));

	return c;
}

void rayCast() {
	clearTexture();

	CVec3f e,v;
	
	e(0)= 0;
	e(1)= 0;
	e(2)= A;
	
	v(2)= -A;

	for (int x= 0; x < TEX_RES_X; x++) {
		for (int y= 0; y < TEX_RES_Y; y++) {
			v(0)= -1 + 2*x / static_cast<float>(TEX_RES_X -1);
			v(1)= -1 + 2*y / static_cast<float>(TEX_RES_Y -1);
			
			CVec3f hit= intersect(e,v);
			
			Color c = Color(1,1,1); // Hintergrund weiß
			if (hit(2) != -1) {
				c = phong(hit,v);
			}
			
			setPoint(Point(x,y),c);
		}
	}
	cout << "raycast done." << endl;
}

// Die Callback Funktion die für das eigentliche Malen
// zuständig ist. Im Wesentlichen brauchen Sie sich nur
// um den Bereich zwischen den Kommentaren zu kümmern,
// alles andere ist wiederum ein notwendiges Übel!
void display (void) {

	manageTexture();
	
	glClear (GL_COLOR_BUFFER_BIT);
	
	mapTexture();

	glFlush ();
	glutSwapBuffers();
}

void init() {
	angleXZ= 1.5 * PI;
	angleYZ= 0;

	
	rayCast();
}

void calcL() {
	xL= radL * sin(angleYZ) * cos(angleXZ);
	zL= radL * sin(angleYZ) * sin(angleXZ);
	yL= radL * cos(angleYZ);
	//cout << "L= (" << xL << ", " << yL << ", " << zL << ")" << endl;
}

// nach Kugelkorrdinaten:
// (x) PI <= XZ <= 2Pi (X)
// (y) 0 <= YZ <= PI (Y)
void keyboard(unsigned char c, int x, int y) {
	switch (c) {

		case 'x':	if (angleXZ > PI) {
						angleXZ-= .1;
						calcL();
					}
					break;

		case 'X':	if (angleXZ < 2 * PI) {
						angleXZ+= .1;
						calcL();
					}
					break;

		case 'y':	if (angleYZ > 0) {
						angleYZ-= .1;
						calcL();
					}
					break;

		case 'Y':	if (angleYZ < PI) {
						angleYZ+= .1;
						calcL();
					}
					break;

		/////////////////////////////////

		case 'd':	R -= R_INTERVAL;
					if(R < R_MIN){
						R = R_MIN;
					}
					break;
					
		case 'D':	R += R_INTERVAL;
					if(R > R_MAX){
						R = R_MAX;
					}
					break;
		/////////////////////////////////

		case 'r':	rK -= RGB_INTERVAL;
					if(rK < RGB_MIN){
						rK = RGB_MIN;
					}
					break;
					
		case 'R':	rK += RGB_INTERVAL;
					if(rK > RGB_MAX){
						rK = RGB_MAX;
					}
					break;
					
		case 'g':	gK -= RGB_INTERVAL;
					if(gK < RGB_MIN){
						gK = RGB_MIN;
					}
					break;
					
		case 'G':	gK += RGB_INTERVAL;
					if(gK > RGB_MAX){
						gK = RGB_MAX;
					}
					break;
					
		case 'b':	bK -= RGB_INTERVAL;
					if(bK < RGB_MIN){
						bK = RGB_MIN;
					}
					break;
					
		case 'B':	bK += RGB_INTERVAL;
					if(bK > RGB_MAX){
						bK = RGB_MAX;
					}
					break;
		/////////////////////////////////


		default:	cout << "Please use 'x', 'X', 'y' and 'Y' for moving the light source." << endl; 
					break;
	}
	rayCast();	
	glutPostRedisplay();
}

// Diese Funktion kennen Sie ja bereits ...
int main (int argc, char **argv) {
	
	init();

	glutInit (&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize (g_WinWidth, g_WinHeight);

	glutCreateWindow ("Uebung 4: Phong");
	
	glutKeyboardFunc(keyboard);
	glutReshapeFunc (reshape);	// zuständig für Größenänderungen des Fensters
	glutDisplayFunc (display);	// zuständig für das wiederholte Neuzeichnen des Bildschirms
	
	glutMainLoop ();

	glDeleteTextures (1, &g_TexID); // löscht die oben angelegte Textur

	return 0;
}
