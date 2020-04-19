#include "glcanvas.hpp"
#include <iostream>
#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
//#include <GL/glew.h> // Include the GLEW header file 
#include <cmath>
using namespace cnv;
using namespace std;

float sundX = 0.0; //dx, dy
float sundY = 0.0;

float sunX = 0.8; //sun starting pos
float sunY = -1.0;

float shadeX = 0.0; //starting X pos for castle shade
float shadedX = 0.0; //dx for castle shade (used only in day time)

bool sun = true;

int R = 0;
int G = 255;
int B = 255;

/*
 * Function that handles the drawing of a circle using the triangle fan
 * method. This will create a filled circle.
 *
 * Params:
 *	x (GLFloat) - the x position of the center point of the circle
 *	y (GLFloat) - the y position of the center point of the circle
 *	radius (GLFloat) - the radius that the painted circle will have
 */
void drawFilledCircleHalf(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	float PI = 3.14159;
	int triangleAmount = 200; //# of triangles used to draw circle
	
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex2f(
		        x + (radius * cos(i *  twicePi / triangleAmount)), 
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	float PI = 3.14159;
	int triangleAmount = 200; //# of triangles used to draw circle
	
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex2f(
		        x + (radius * cos(i *  twicePi / triangleAmount)), 
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}

/*
 * Function that handles the drawing of a circle using the line loop
 * method. This will create a hollow circle.
 *
 * Params:
 *	x (GLFloat) - the x position of the center point of the circle
 *	y (GLFloat) - the y position of the center point of the circle
 *	radius (GLFloat) - the radius that the painted circle will have
 */
void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	float PI = 3.14159;
	int lineAmount = 100; //# of triangles used to draw circle
	
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;
	
	glBegin(GL_LINE_LOOP);
		for(i = 0; i <= lineAmount;i++) { 
			glVertex2f(
			    x + (radius * cos(i *  twicePi / lineAmount)), 
			    y + (radius * sin(i * twicePi / lineAmount))
			);
		}
	glEnd();
}

void drawHollowCircleHalf(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	float PI = 3.14159;
	int lineAmount = 100; //# of triangles used to draw circle
	
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 1.0f * PI;
	
	glBegin(GL_LINE_LOOP);
		for(i = 0; i <= lineAmount;i++) { 
			glVertex2f(
			    x + (radius * cos(i *  twicePi / lineAmount)), 
			    y + (radius * sin(i * twicePi / lineAmount))
			);
		}
	glEnd();
}

void display_morning() {
   //glClearColor(0.0f, 0.0f, 4.0f, 3.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);	// Clear the color buffer (background)
	
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
//~~~~~~~~~~~~~~~~~~~SKY~~~~~~~~~~~~~~~~~~~

	glBegin(GL_QUADS); //background
		//yellow color
		glColor3ub(251,111,2);
		glVertex2f(-1.0,-1.0);
		glVertex2f(1.0,-1.0);
		//orange color
		glColor3ub(251,205,3);
		glVertex2f(1.0, 1.0);
		glVertex2f(-1.0, 1.0);
	glEnd();

//~~~~~~~~~~~~~~~~~~~~~~~~END OF SKY~~~~~~~~~~~~~~~~~~~~	
	
//~~~~~~~~~~~~~~~~~~SUN~~~~~~~~~~~~~~~~~~~~~~

//	glColor3ub(241,223,10);
	glColor3ub(241,164,10);
	drawFilledCircle(0.7,-0.7,0.1);
	glEnable (GL_BLEND);//to make transparent circles
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0,1.0,0.0,0.1);//R,G,B,A -- alpha channel
	drawFilledCircle(0.7,-0.7,0.2);
	glColor4f(1.0,1.0,0.0,0.08);
	drawFilledCircle(0.7,-0.7,0.3);
	glColor4f(1.0,1.0,0.0,0.05);
	drawFilledCircle(0.7,-0.7,0.5);
	glColor4f(1.0,1.0,0.0,0.03);
	drawFilledCircle(0.7,-0.7,0.7);

//~~~~~~~~~~~~~~~~~~~~~~~~~~END OF SUN~~~~~~~~~~~~~~~~~~~~~



//~~~~~~~~~~~~~~~~~~~GRASS~~~~~~~~~~~~~~~~~~~~~~~~

	glColor3ub( 14, 149, 1);
	glRectf(-1.0f, -0.7f, 1.0f, -1.0f);//x1,y1 (left upper point), x2,y2 (bottom right point). Solid green rectangle
	//another green rectangle, but within darken-green shaders.
	glBegin(GL_QUADS); 
		//green color
		glColor3ub(14,149,1);
		glVertex2f(-1.0, -0.8);
		glVertex2f(1.0, -0.8);
		
		//black color (darken-green) for making shaders on the grass
		glColor3ub(34,114,28);
		glVertex2f(1.0,-0.7);
		glVertex2f(-1.0,-0.7);
	
	glEnd();
	
//~~~~~~~~~~~~~~~~~~~~END OF GRASS~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~STRONGHOLD~~~~~~~~~~~~~~~~~~~~~~~
	//castle:
	glColor3ub( 171, 171, 171);//light grey
	glRectf(-0.8f, -0.4f, -0.1f, -0.9f);//1st stage block
	glRectf(-0.7, 0.0, -0.2, -0.4);//2nd stage block
	glColor3ub(105,104,104);//dark grey
	glRectf(-0.8,-0.4, -0.6, -0.9);//1st floor shaders
	glRectf(-0.7, 0.0, -0.5, -0.4);//2nd floor shadres
//~~~~~~~~~~~BLACK OUTLINE~~~~~~~~~~~~~~~
	glLineWidth(10);
	glBegin(GL_LINES); //black lines
		glColor3ub(0, 0, 0);
		glVertex2f(-0.8, -0.4);
		glVertex2f(-0.8, -0.9);

		glVertex2f(-0.1, -0.4);
		glVertex2f(-0.1, -0.9);

		glVertex2f(-0.815, -0.4);
		glVertex2f(-0.085, -0.4);

		glVertex2f(-0.7, 0.0);
		glVertex2f(-0.7,-0.4);

		glVertex2f(-0.2, -0.4);
		glVertex2f(-0.2, 0.0);

		glVertex2f(-0.186, 0.0);
		glVertex2f(-0.716, 0.0);

		glVertex2f(-0.35, 0.0);
		glVertex2f(-0.35, 0.3);
//~~~~~~~~~~~~~ CROWNS ~~~~~~~~~~~~~~~
		//1st floor
		glVertex2f(-0.15,-0.4);
		glVertex2f(-0.15,-0.45);

		glVertex2f(-0.25,-0.4);
		glVertex2f(-0.25,-0.45);

		glVertex2f(-0.35,-0.4);
		glVertex2f(-0.35,-0.45);

		glVertex2f(-0.45,-0.4);
		glVertex2f(-0.45,-0.45);

		glVertex2f(-0.55,-0.4);
		glVertex2f(-0.55,-0.45);

		glVertex2f(-0.65,-0.4);
		glVertex2f(-0.65,-0.45);

		glVertex2f(-0.75,-0.4);
		glVertex2f(-0.75,-0.45);

		//2nd floor
		glVertex2f(-0.25,0.0);
		glVertex2f(-0.25,-0.05);

		glVertex2f(-0.35,0.0);
		glVertex2f(-0.35,-0.05);

		glVertex2f(-0.45,0.0);
		glVertex2f(-0.45,-0.05);

		glVertex2f(-0.55,0.0);
		glVertex2f(-0.55,-0.05);

		glVertex2f(-0.65,0.0);
		glVertex2f(-0.65,-0.05);

//~~~~~~~~~~~~~~~~~END OF CROWNS~~~~~~~~~~~~

	glEnd();	
//~~~~~~~~~~~~~~~~~~~END OF OUTLINES~~~~~~~~~~~~~~~~~~~~~~
//
//~~~~~~~~~~~~~~~~~~~WINDOWS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	glColor3ub(0,0,0); //black
	glRectf(-0.37, -0.1, -0.3, -0.25);

	glRectf(-0.5,-0.5 ,-0.45, -0.6);
	glRectf(-0.35,-0.5, -0.3 , -0.6);
	glRectf(-0.22, -0.5, -0.17, -0.6);

	glRectf(-0.72, -0.5, -0.67, -0.6);


	glColor3ub(148, 100, 22);//brown
	glRectf(-0.4,-0.75,-0.27,-0.9);//door
	drawFilledCircle(-0.335, -0.75, 0.065);
//~~~~~~~~~~~~~~~~~~~~END OF WINDOWS~~~~~~~~~~~~~~~~~~~
//
//~~~~~~~~~~~~~~~~~~~~FLAG~~~~~~~~~~~~~~~~~~~~~~~~~	

	//flag:
	glColor3ub(255,0,0);
	glRectf(-0.34,0.3, -0.16, 0.16);
	glBegin(GL_POLYGON);
		glColor3ub(183,4,4);
		glVertex2f(-0.16,0.26);
		glVertex2f(-0.16,0.12);
		glVertex2f(0.02,0.12);
		glVertex2f(-0.07,0.19);
		glVertex2f(0.02,0.26);
	glEnd();
	//glRectf(-0.16, 0.26, 0.02, 0.12 );
	
	
//~~~~~~~~~~~~~~~~~~~END OF FLAG~~~~~~~~~~~~~~~~~
//
//~~~~~~~~~~~~~CASTLE SHADE~~~~~~~~~~~~~~~~~~~~~
	
	glBegin(GL_POLYGON);
		glColor4f(0.2,0.19,0.19,0.5);
		glVertex2f(-0.82, -0.9);
		glVertex2f(-1.0, -0.93);
		glVertex2f(-1.0,-1.0);
		glVertex2f(-0.6,-0.9);
	glEnd();


//~~~~~~~~~~~~END OF CASTLE SHADE~~~~~~~~~~~~~~~
//
//~~~~~~~~~~~~~~DOOR LINES~~~~~~~~~~~~~~~~~~~~~
	glLineWidth(4);
	glBegin(GL_LINES);
		glColor3ub(0,0,0);
		glVertex2f(-0.335,-0.9);
		glVertex2f(-0.335,-0.685);	
		glVertex2f(-0.37,-0.695);
		glVertex2f(-0.37, -0.9);
		glVertex2f(-0.3, -0.9);
		glVertex2f(-0.3, -0.695);
		glVertex2f(-0.4,-0.75);
		glVertex2f(-0.4,-0.9);
		glVertex2f(-0.27, -0.75);
		glVertex2f(-0.27,-0.9);
		glVertex2f(-0.4,-0.85);
		glVertex2f(-0.27,-0.85);
	glEnd();
		drawHollowCircleHalf(-0.335, -0.75, 0.065);
//~~~~~~~~~~~~~~~~~~END OF DOOR LINES~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~END OF STRONGHOLD~~~~~~~~~~~~~~~~~~~~~~~~~~~
   glFlush();  // Render now
}
void display_day() {
    glClear(GL_COLOR_BUFFER_BIT);	// Clear the color buffer (background)
	
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
//~~~~~~~~~~~~~~~~~~~SKY~~~~~~~~~~~~~~~~~~~

	glBegin(GL_QUADS); //background
		//white color
		glColor3f(-1.0,1.0,1.0);
		glVertex2f(-1.0,-1.0);
		glVertex2f(1.0,-1.0);
		//blue color
		glColor3f(0.0,0.0,1.0);
		glVertex2f(1.0, 1.0);
		glVertex2f(-1.0, 1.0);
	glEnd();

//~~~~~~~~~~~~~~~~~~~~~~~~END OF SKY~~~~~~~~~~~~~~~~~~~~	
	

//~~~~~~~~~~~~~~~~~~~GRASS~~~~~~~~~~~~~~~~~~~~~~~~

	glColor3ub( 14, 149, 1);
	glRectf(-1.0f, -0.7f, 1.0f, -1.0f);//x1,y1 (left upper point), x2,y2 (bottom right point). Solid green rectangle
	//another green rectangle, but within darken-green shaders.
	glBegin(GL_QUADS); 
		//green color
		glColor3ub(14,149,1);
		glVertex2f(-1.0, -0.8);
		glVertex2f(1.0, -0.8);
		
		//black color (darken-green) for making shaders on the grass
		glColor3ub(34,114,28);
		glVertex2f(1.0,-0.7);
		glVertex2f(-1.0,-0.7);
	
	glEnd();
	
//~~~~~~~~~~~~~~~~~~~~END OF GRASS~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~SUN~~~~~~~~~~~~~~~~~~~~~~

	glColor3ub(241,223,10);
	glColor3ub(241,164,10);
	drawFilledCircle(0.7,0.7,0.1);
	glEnable (GL_BLEND);//to make transparent circles
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0,1.0,0.0,0.1);//R,G,B,A -- alpha channel
	drawFilledCircle(0.7,0.7,0.2);
	glColor4f(1.0,1.0,0.0,0.08);
	drawFilledCircle(0.7,0.7,0.3);
	glColor4f(1.0,1.0,0.0,0.05);
	drawFilledCircle(0.7,0.7,0.5);
	glColor4f(1.0,1.0,0.0,0.03);
	drawFilledCircle(0.7,0.7,0.7);

//~~~~~~~~~~~~~~~~~~~~~~~~~~END OF SUN~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~STRONGHOLD~~~~~~~~~~~~~~~~~~~~~~~
	//castle:
	glColor3ub( 171, 171, 171);//light grey
	glRectf(-0.8f, -0.4f, -0.1f, -0.9f);//1st stage block
	glRectf(-0.7, 0.0, -0.2, -0.4);//2nd stage block
	glColor3ub(105,104,104);//dark grey
	glRectf(-0.8,-0.4, -0.6, -0.9);//1st floor shaders
	glRectf(-0.7, 0.0, -0.5, -0.4);//2nd floor shadres
//~~~~~~~~~~~BLACK OUTLINE~~~~~~~~~~~~~~~
	glLineWidth(10);
	glBegin(GL_LINES); //black lines
		glColor3ub(0, 0, 0);
		glVertex2f(-0.8, -0.4);
		glVertex2f(-0.8, -0.9);

		glVertex2f(-0.1, -0.4);
		glVertex2f(-0.1, -0.9);

		glVertex2f(-0.815, -0.4);
		glVertex2f(-0.085, -0.4);

		glVertex2f(-0.7, 0.0);
		glVertex2f(-0.7,-0.4);

		glVertex2f(-0.2, -0.4);
		glVertex2f(-0.2, 0.0);

		glVertex2f(-0.186, 0.0);
		glVertex2f(-0.716, 0.0);

		glVertex2f(-0.35, 0.0);
		glVertex2f(-0.35, 0.3);
//~~~~~~~~~~~~~ CROWNS ~~~~~~~~~~~~~~~
		//1st floor
		glVertex2f(-0.15,-0.4);
		glVertex2f(-0.15,-0.45);

		glVertex2f(-0.25,-0.4);
		glVertex2f(-0.25,-0.45);

		glVertex2f(-0.35,-0.4);
		glVertex2f(-0.35,-0.45);

		glVertex2f(-0.45,-0.4);
		glVertex2f(-0.45,-0.45);

		glVertex2f(-0.55,-0.4);
		glVertex2f(-0.55,-0.45);

		glVertex2f(-0.65,-0.4);
		glVertex2f(-0.65,-0.45);

		glVertex2f(-0.75,-0.4);
		glVertex2f(-0.75,-0.45);

		//2nd floor
		glVertex2f(-0.25,0.0);
		glVertex2f(-0.25,-0.05);

		glVertex2f(-0.35,0.0);
		glVertex2f(-0.35,-0.05);

		glVertex2f(-0.45,0.0);
		glVertex2f(-0.45,-0.05);

		glVertex2f(-0.55,0.0);
		glVertex2f(-0.55,-0.05);

		glVertex2f(-0.65,0.0);
		glVertex2f(-0.65,-0.05);

//~~~~~~~~~~~~~~~~~END OF CROWNS~~~~~~~~~~~~

	glEnd();	
//~~~~~~~~~~~~~~~~~~~END OF OUTLINES~~~~~~~~~~~~~~~~~~~~~~
//
//~~~~~~~~~~~~~~~~~~~WINDOWS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	glColor3ub(0,0,0); //black
	glRectf(-0.37, -0.1, -0.3, -0.25);

	glRectf(-0.5,-0.5 ,-0.45, -0.6);
	glRectf(-0.35,-0.5, -0.3 , -0.6);
	glRectf(-0.22, -0.5, -0.17, -0.6);

	glRectf(-0.72, -0.5, -0.67, -0.6);


	glColor3ub(148, 100, 22);//brown
	glRectf(-0.4,-0.75,-0.27,-0.9);//door
	drawFilledCircle(-0.335, -0.75, 0.065);
//~~~~~~~~~~~~~~~~~~~~END OF WINDOWS~~~~~~~~~~~~~~~~~~~
//
//~~~~~~~~~~~~~~~~~~~~FLAG~~~~~~~~~~~~~~~~~~~~~~~~~	

	//flag:
	glColor3ub(255,0,0);
	glRectf(-0.34,0.3, -0.16, 0.16);
	glBegin(GL_POLYGON);
		glColor3ub(183,4,4);
		glVertex2f(-0.16,0.26);
		glVertex2f(-0.16,0.12);
		glVertex2f(0.02,0.12);
		glVertex2f(-0.07,0.19);
		glVertex2f(0.02,0.26);
	glEnd();
	//glRectf(-0.16, 0.26, 0.02, 0.12 );
	
	
//~~~~~~~~~~~~~~~~~~~END OF FLAG~~~~~~~~~~~~~~~~~
//
//~~~~~~~~~~~~~CASTLE SHADE~~~~~~~~~~~~~~~~~~~~~
	
	glBegin(GL_POLYGON);
		glColor4f(0.2,0.19,0.19,0.5);
		glVertex2f(-0.82, -0.9);
		glVertex2f(-1.0, -0.96);
		glVertex2f(-1.0,-1.0);
		glVertex2f(-0.65,-1.0);
		glVertex2f(-0.6,-0.9);
	glEnd();


//~~~~~~~~~~~~END OF CASTLE SHADE~~~~~~~~~~~~~~~
//
//~~~~~~~~~~~~~~DOOR LINES~~~~~~~~~~~~~~~~~~~~~
	glLineWidth(4);
	glBegin(GL_LINES);
		glColor3ub(0,0,0);
		glVertex2f(-0.335,-0.9);
		glVertex2f(-0.335,-0.685);	
		glVertex2f(-0.37,-0.695);
		glVertex2f(-0.37, -0.9);
		glVertex2f(-0.3, -0.9);
		glVertex2f(-0.3, -0.695);
		glVertex2f(-0.4,-0.75);
		glVertex2f(-0.4,-0.9);
		glVertex2f(-0.27, -0.75);
		glVertex2f(-0.27,-0.9);
		glVertex2f(-0.4,-0.85);
		glVertex2f(-0.27,-0.85);
	glEnd();
		drawHollowCircleHalf(-0.335, -0.75, 0.065);
//~~~~~~~~~~~~~~~~~~END OF DOOR LINES~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~END OF STRONGHOLD~~~~~~~~~~~~~~~~~~~~~~~~~~~
   glFlush();  // Render now
}


void display_evening() {
    glClear(GL_COLOR_BUFFER_BIT);	// Clear the color buffer (background)
	
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
//~~~~~~~~~~~~~~~~~~~SKY~~~~~~~~~~~~~~~~~~~

	glBegin(GL_QUADS); //background
		//white color
		glColor3ub(255,117,227);
		glVertex2f(-1.0,-1.0);
		glVertex2f(1.0,-1.0);
		//blue color
		glColor3ub(158,2,251);
		glVertex2f(1.0, 1.0);
		glVertex2f(-1.0, 1.0);
	glEnd();

//~~~~~~~~~~~~~~~~~~~~~~~~END OF SKY~~~~~~~~~~~~~~~~~~~~	
	

//~~~~~~~~~~~~~~~~~~~GRASS~~~~~~~~~~~~~~~~~~~~~~~~

	glColor3ub( 14, 149, 1);
	glRectf(-1.0f, -0.7f, 1.0f, -1.0f);//x1,y1 (left upper point), x2,y2 (bottom right point). Solid green rectangle
	//another green rectangle, but within darken-green shaders.
	glBegin(GL_QUADS); 
		//green color
		glColor3ub(14,149,1);
		glVertex2f(-1.0, -0.8);
		glVertex2f(1.0, -0.8);
		
		//black color (darken-green) for making shaders on the grass
		glColor3ub(34,114,28);
		glVertex2f(1.0,-0.7);
		glVertex2f(-1.0,-0.7);
	
	glEnd();
	
//~~~~~~~~~~~~~~~~~~~~END OF GRASS~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~STRONGHOLD~~~~~~~~~~~~~~~~~~~~~~~
	//castle:
	glColor3ub( 171, 171, 171);//light grey
	glRectf(-0.8f, -0.4f, -0.1f, -0.9f);//1st stage block
	glRectf(-0.7, 0.0, -0.2, -0.4);//2nd stage block
	glColor3ub(105,104,104);//dark grey
	glRectf(-0.8,-0.4, -0.6, -0.9);//1st floor shaders
	glRectf(-0.7, 0.0, -0.5, -0.4);//2nd floor shadres
//~~~~~~~~~~~BLACK OUTLINE~~~~~~~~~~~~~~~
	glLineWidth(10);
	glBegin(GL_LINES); //black lines
		glColor3ub(0, 0, 0);
		glVertex2f(-0.8, -0.4);
		glVertex2f(-0.8, -0.9);

		glVertex2f(-0.1, -0.4);
		glVertex2f(-0.1, -0.9);

		glVertex2f(-0.815, -0.4);
		glVertex2f(-0.085, -0.4);

		glVertex2f(-0.7, 0.0);
		glVertex2f(-0.7,-0.4);

		glVertex2f(-0.2, -0.4);
		glVertex2f(-0.2, 0.0);

		glVertex2f(-0.186, 0.0);
		glVertex2f(-0.716, 0.0);

		glVertex2f(-0.35, 0.0);
		glVertex2f(-0.35, 0.3);
//~~~~~~~~~~~~~ CROWNS ~~~~~~~~~~~~~~~
		//1st floor
		glVertex2f(-0.15,-0.4);
		glVertex2f(-0.15,-0.45);

		glVertex2f(-0.25,-0.4);
		glVertex2f(-0.25,-0.45);

		glVertex2f(-0.35,-0.4);
		glVertex2f(-0.35,-0.45);

		glVertex2f(-0.45,-0.4);
		glVertex2f(-0.45,-0.45);

		glVertex2f(-0.55,-0.4);
		glVertex2f(-0.55,-0.45);

		glVertex2f(-0.65,-0.4);
		glVertex2f(-0.65,-0.45);

		glVertex2f(-0.75,-0.4);
		glVertex2f(-0.75,-0.45);

		//2nd floor
		glVertex2f(-0.25,0.0);
		glVertex2f(-0.25,-0.05);

		glVertex2f(-0.35,0.0);
		glVertex2f(-0.35,-0.05);

		glVertex2f(-0.45,0.0);
		glVertex2f(-0.45,-0.05);

		glVertex2f(-0.55,0.0);
		glVertex2f(-0.55,-0.05);

		glVertex2f(-0.65,0.0);
		glVertex2f(-0.65,-0.05);

//~~~~~~~~~~~~~~~~~END OF CROWNS~~~~~~~~~~~~

	glEnd();	
//~~~~~~~~~~~~~~~~~~~END OF OUTLINES~~~~~~~~~~~~~~~~~~~~~~
//
//~~~~~~~~~~~~~~~~~~~WINDOWS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
//	glColor3ub(0,0,0); //yellow
	glColor4f(1.0,1.0,0.0,0.7);
	glRectf(-0.37, -0.1, -0.3, -0.25);
//	glColor4f(1.0,1.0,0.0,0.5);
	glRectf(-0.5,-0.5 ,-0.45, -0.6);
	glRectf(-0.35,-0.5, -0.3 , -0.6);
	glRectf(-0.22, -0.5, -0.17, -0.6);
//	glColor3ub(0,0,0);
	glRectf(-0.72, -0.5, -0.67, -0.6);


	glColor3ub(148, 100, 22);//brown
//	glColor3ub(0,0,0);
	glRectf(-0.4,-0.75,-0.27,-0.9);//door
	drawFilledCircle(-0.335, -0.75, 0.065);
//~~~~~~~~~~~~~~~~~~~~END OF WINDOWS~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~WINDOW SHADE~~~~~~~~~~~~~~~~~
	glColor4f(1.0,1.0,0.0,0.3);
	glBegin(GL_QUADS);
		glVertex2f(-0.45, -0.95);
		glVertex2f(-0.35, -1.0);
		glVertex2f(-0.25, -1.0);
		glVertex2f(-0.35, -0.95);

		glVertex2f(-0.3+0.05, -0.95);
		glVertex2f(-0.2+0.05, -1.0);
		glVertex2f(-0.1+0.05, -1.0);
		glVertex2f(-0.2+0.05, -0.95);

		glVertex2f(-0.15+0.1, -0.95);
		glVertex2f(-0.05+0.1, -1.0);
		glVertex2f(0.05+0.1, -1.0);
		glVertex2f(-0.05+0.1, -0.95);

		glVertex2f(-0.90+0.05+0.01,-0.95+0.02);
		glVertex2f(-1.0, -1.0);
		glVertex2f(-0.9, -1.0);
		glVertex2f(-0.8+0.05+0.01,-0.95+0.02);

	glEnd();
	
//~~~~~~~~~~~~~~~~~~~~~~END OF WINDOW SHADE~~~~~~~~~~~~
	
//~~~~~~~~~~~~~~~~~~~~FLAG~~~~~~~~~~~~~~~~~~~~~~~~~	

	//flag:
	glColor3ub(255,0,0);
	glRectf(-0.34,0.3, -0.16, 0.16);
	glBegin(GL_POLYGON);
		glColor3ub(183,4,4);
		glVertex2f(-0.16,0.26);
		glVertex2f(-0.16,0.12);
		glVertex2f(0.02,0.12);
		glVertex2f(-0.07,0.19);
		glVertex2f(0.02,0.26);
	glEnd();
	
	
//~~~~~~~~~~~~~~~~~~~END OF FLAG~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~DOOR LINES~~~~~~~~~~~~~~~~~~~~~
	glLineWidth(4);
	glBegin(GL_LINES);
		glColor3ub(0,0,0);
		glVertex2f(-0.335,-0.9);
		glVertex2f(-0.335,-0.685);	
		glVertex2f(-0.37,-0.695);
		glVertex2f(-0.37, -0.9);
		glVertex2f(-0.3, -0.9);
		glVertex2f(-0.3, -0.695);
		glVertex2f(-0.4,-0.75);
		glVertex2f(-0.4,-0.9);
		glVertex2f(-0.27, -0.75);
		glVertex2f(-0.27,-0.9);
		glVertex2f(-0.4,-0.85);
		glVertex2f(-0.27,-0.85);
	glEnd();
		drawHollowCircleHalf(-0.335, -0.75, 0.065);
//~~~~~~~~~~~~~~~~~~END OF DOOR LINES~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~END OF STRONGHOLD~~~~~~~~~~~~~~~~~~~~~~~~~~~
   glFlush();  // Render now
}

void timer(int){
	glPushMatrix();
	sunX -= 0.007;

	glutPostRedisplay();
	glPopMatrix();
	glutTimerFunc(16,timer,0);
}

void display_loop() {
    glClear(GL_COLOR_BUFFER_BIT);	// Clear the color buffer (background)
	
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_LINE_SMOOTH);

	glEnable (GL_BLEND);//to make transparent circles
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (sun){
//~~~~~~~~~~~~~~~~~~~SKY~~~~~~~~~~~~~~~~~~~


	glBegin(GL_QUADS); //background
		//white color
		glColor3ub(R,G,B);
		glVertex2f(-1.0,-1.0);
		glVertex2f(1.0,-1.0);
		//blue color
		glColor3ub(0,0,B);
		glVertex2f(1.0, 1.0);
		glVertex2f(-1.0, 1.0);
	glEnd();


}
//~~~~~~~~~~~~~~~~~~~~~~~~END OF SKY~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SUN~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~YELLOW SUN~~~~~~~~~~~~~~~~~~~~~~~~~~
	if (sun){
		if (sunY <= 0.8){
		//	sunX -=0.03; //! --> set to 0.01
			sunY = -2*sunX*sunX;
			glColor3ub(241,223,10);
			drawFilledCircle(sunX + sundX,sunY+sundY,0.1);
			glColor4f(1.0,1.0,0.0,0.1);//R,G,B,A -- alpha channel
			drawFilledCircle(sunX+sundX,sunY+sundY,0.2);
			glColor4f(1.0,1.0,0.0,0.08);
			drawFilledCircle(sunX+sundX,sunY+sundY,0.3);
			glColor4f(1.0,1.0,0.0,0.05);
			drawFilledCircle(sunX+sundX,sunY+sundY,0.5);
			glColor4f(1.0,1.0,0.0,0.03);
			drawFilledCircle(sunX+sundX,sunY+sundY,0.7);

		}

		else if (sunY > 0.8){ 
			sundY -= 0.08;
			sundY = -2*sunX*sunX;
			glColor3ub(241,223,10);
			drawFilledCircle(sunX+sundX,sunY+sundY,0.1);

			glColor4f(1.0,1.0,0.0,0.1);//R,G,B,A -- alpha channel
			drawFilledCircle(sunX+sundX,sunY+sundY,0.2);
			glColor4f(1.0,1.0,0.0,0.08);
			drawFilledCircle(sunX+sundX,sunY+sundY,0.3);
			glColor4f(1.0,1.0,0.0,0.05);
			drawFilledCircle(sunX+sundX,sunY+sundY,0.5);
			glColor4f(1.0,1.0,0.0,0.03);
			drawFilledCircle(sunX+sundX,sunY+sundY,0.7);
		}

		if (sunX > -0.8){
			glColor3ub(241,223,10);
			drawFilledCircle(sunX+sundX,sunY+sundY,0.1);

			glColor4f(1.0,1.0,0.0,0.1);//R,G,B,A -- alpha channel
			drawFilledCircle(sunX+sundX,sunY+sundY,0.2);
			glColor4f(1.0,1.0,0.0,0.08);
			drawFilledCircle(sunX+sundX,sunY+sundY,0.3);
			glColor4f(1.0,1.0,0.0,0.05);
			drawFilledCircle(sunX+sundX,sunY+sundY,0.5);
			glColor4f(1.0,1.0,0.0,0.03);
			drawFilledCircle(sunX+sundX,sunY+sundY,0.7);


		}

		else if (sunX <= -0.8){
			sunX = 0.8;
			sunY = -1.0;
			sundX = 0.0;
			sundY = 0.0;
			glColor3ub(241,223,10);
			drawFilledCircle(sunX+sundX,sunY+sundY,0.1);

			glColor4f(1.0,1.0,0.0,0.1);//R,G,B,A -- alpha channel
			drawFilledCircle(sunX+sundX,sunY+sundY,0.2);
			glColor4f(1.0,1.0,0.0,0.08);
			drawFilledCircle(sunX+sundX,sunY+sundY,0.3);
			glColor4f(1.0,1.0,0.0,0.05);
			drawFilledCircle(sunX+sundX,sunY+sundY,0.5);
			glColor4f(1.0,1.0,0.0,0.03);
			drawFilledCircle(sunX+sundX,sunY+sundY,0.7);
			sun = false;

		}
	}

//~~~~~~~~~~~~~~~~~~~~END OF YELLOW SUN~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~MOON~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	else if(!sun){ 

//~~~~~~~~~~~~~~~~~~~SKY~~~~~~~~~~~~~~~~~~~
		glBegin(GL_QUADS); //background
			//white color
			glColor3ub(57,21,116);
			glVertex2f(-1.0,-1.0);
			glVertex2f(1.0,-1.0);
			//blue color
			glColor3ub(21,24,116);
			glVertex2f(1.0, 1.0);
			glVertex2f(-1.0, 1.0);
		glEnd();

//~~~~~~~~~~~~~~~~~~~~~~~~END OF SKY~~~~~~~~~~~~~~~~~~~~	
		if (sunY <= 0.8){
			sunY = -2*sunX*sunX;
			glColor3ub(255,255,255);
			drawFilledCircle(sunX+sundX,sunY+sundY,0.1);
			glColor3ub(148,148,148);
			glLineWidth(7);
			drawHollowCircle(sunX+sundX, sunY+sundY, 0.1);

			glColor4f(1.0,1.0,1.0,0.03);//R,G,B,A -- alpha channel
			drawFilledCircle(sunX+sundX,sunY+sundY,0.2);

		}

		else if (sunY > 0.8){ 
			sundY -= 0.08;
			sunY = -2*sunX*sunX;
			glColor3ub(255,255,255);
			drawFilledCircle(sunX+sundX,sunY+sundY,0.1);


		}

		if (sunX > -0.8){
			glColor3ub(255,255,255);
			drawFilledCircle(sunX+sundX,sunY+sundY,0.1);



		}

		else if (sunX <= -0.8){
			sunX = 0.8;
			sunY = -1.0;
			sundX = 0.0;
			sundY = 0.0;
			glColor3ub(255,255,255);
			drawFilledCircle(sunX+sundX,sunY+sundY,0.1);



			sun = true;

		}		
	}

//~~~~~~~~~~~~~~~~~~~~~~~~~~END OF MOON~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
//~~~~~~~~~~~~~~~~~~~~~~~~~~END OF SUN~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~GRASS~~~~~~~~~~~~~~~~~~~~~~~~
if (sun){
	glColor3ub( 14, 149, 1);
	glRectf(-1.0f, -0.7f, 1.0f, -1.0f);//x1,y1 (left upper point), x2,y2 (bottom right point). Solid green rectangle
	//another green rectangle, but within darken-green shaders.
	glBegin(GL_QUADS); 
		//green color
		glColor3ub(14,149,1);
		glVertex2f(-1.0, -0.8);
		glVertex2f(1.0, -0.8);
		
		//black color (darken-green) for making shaders on the grass
		glColor3ub(34,114,28);
		glVertex2f(1.0,-0.7);
		glVertex2f(-1.0,-0.7);
	
	glEnd();
}
else if(!sun){
	glColor3ub( 3, 65, 5);
	glRectf(-1.0f, -0.7f, 1.0f, -1.0f);//x1,y1 (left upper point), x2,y2 (bottom right point). Solid green rectangle
	//another green rectangle, but within darken-green shaders.
	glBegin(GL_QUADS); 
		//green color
		glColor3ub(3,64,5);
		glVertex2f(-1.0, -0.8);
		glVertex2f(1.0, -0.8);
		
		//black color (darken-green) for making shaders on the grass
		glColor3ub(0,40,2);
		glVertex2f(1.0,-0.7);
		glVertex2f(-1.0,-0.7);
	
	glEnd();
}
//~~~~~~~~~~~~~~~~~~~~END OF GRASS~~~~~~~~~~~~~~~~~~~~~~




//~~~~~~~~~~~~~~~~~~~STRONGHOLD~~~~~~~~~~~~~~~~~~~~~~~
	//castle:
	glColor3ub( 171, 171, 171);//light grey
	glRectf(-0.8f, -0.4f, -0.1f, -0.9f);//1st stage block
	glRectf(-0.7, 0.0, -0.2, -0.4);//2nd stage block
	glColor3ub(105,104,104);//dark grey
	glRectf(-0.8,-0.4, -0.6, -0.9);//1st floor shaders
	glRectf(-0.7, 0.0, -0.5, -0.4);//2nd floor shadres
//~~~~~~~~~~~BLACK OUTLINE~~~~~~~~~~~~~~~
	glLineWidth(10);
	glBegin(GL_LINES); //black lines
		glColor3ub(0, 0, 0);
		glVertex2f(-0.8, -0.4);
		glVertex2f(-0.8, -0.9);

		glVertex2f(-0.1, -0.4);
		glVertex2f(-0.1, -0.9);

		glVertex2f(-0.815, -0.4);
		glVertex2f(-0.085, -0.4);

		glVertex2f(-0.7, 0.0);
		glVertex2f(-0.7,-0.4);

		glVertex2f(-0.2, -0.4);
		glVertex2f(-0.2, 0.0);

		glVertex2f(-0.186, 0.0);
		glVertex2f(-0.716, 0.0);

		glVertex2f(-0.35, 0.0);
		glVertex2f(-0.35, 0.3);
//~~~~~~~~~~~~~ CROWNS ~~~~~~~~~~~~~~~
		//1st floor
		glVertex2f(-0.15,-0.4);
		glVertex2f(-0.15,-0.45);

		glVertex2f(-0.25,-0.4);
		glVertex2f(-0.25,-0.45);

		glVertex2f(-0.35,-0.4);
		glVertex2f(-0.35,-0.45);

		glVertex2f(-0.45,-0.4);
		glVertex2f(-0.45,-0.45);

		glVertex2f(-0.55,-0.4);
		glVertex2f(-0.55,-0.45);

		glVertex2f(-0.65,-0.4);
		glVertex2f(-0.65,-0.45);

		glVertex2f(-0.75,-0.4);
		glVertex2f(-0.75,-0.45);

		//2nd floor
		glVertex2f(-0.25,0.0);
		glVertex2f(-0.25,-0.05);

		glVertex2f(-0.35,0.0);
		glVertex2f(-0.35,-0.05);

		glVertex2f(-0.45,0.0);
		glVertex2f(-0.45,-0.05);

		glVertex2f(-0.55,0.0);
		glVertex2f(-0.55,-0.05);

		glVertex2f(-0.65,0.0);
		glVertex2f(-0.65,-0.05);

//~~~~~~~~~~~~~~~~~END OF CROWNS~~~~~~~~~~~~

	glEnd();	
//~~~~~~~~~~~~~~~~~~~END OF OUTLINES~~~~~~~~~~~~~~~~~~~~~~
//
//~~~~~~~~~~~~~~~~~~~WINDOWS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
if (sun){
	glColor3ub(0,0,0); //black
	glRectf(-0.37, -0.1, -0.3, -0.25);

	glRectf(-0.5,-0.5 ,-0.45, -0.6);
	glRectf(-0.35,-0.5, -0.3 , -0.6);
	glRectf(-0.22, -0.5, -0.17, -0.6);

	glRectf(-0.72, -0.5, -0.67, -0.6);


	glColor3ub(148, 100, 22);//brown
	glRectf(-0.4,-0.75,-0.27,-0.9);//door
	drawFilledCircle(-0.335, -0.75, 0.065);
}
else if(!sun){
//	glColor3ub(0,0,0); //yellow
	glColor4f(1.0,1.0,0.0,0.7);
	glRectf(-0.37, -0.1, -0.3, -0.25);
//	glColor4f(1.0,1.0,0.0,0.5);
	glRectf(-0.5,-0.5 ,-0.45, -0.6);
	glRectf(-0.35,-0.5, -0.3 , -0.6);
	glRectf(-0.22, -0.5, -0.17, -0.6);
	glRectf(-0.72, -0.5, -0.67, -0.6);

	glColor3ub(148, 100, 22);//brown
	glRectf(-0.4,-0.75,-0.27,-0.9);//door
	drawFilledCircle(-0.335, -0.75, 0.065);

}
//~~~~~~~~~~~~~~~~~~~~END OF WINDOWS~~~~~~~~~~~~~~~~~~~
//
//~~~~~~~~~~~~~~~~~~~~FLAG~~~~~~~~~~~~~~~~~~~~~~~~~	

	//flag:
	glColor3ub(255,0,0);
	glRectf(-0.34,0.3, -0.16, 0.16);
	glBegin(GL_POLYGON);
		glColor3ub(183,4,4);
		glVertex2f(-0.16,0.26);
		glVertex2f(-0.16,0.12);
		glVertex2f(0.02,0.12);
		glVertex2f(-0.07,0.19);
		glVertex2f(0.02,0.26);
	glEnd();
	
	
//~~~~~~~~~~~~~~~~~~~END OF FLAG~~~~~~~~~~~~~~~~~
//
//~~~~~~~~~~~~~CASTLE SHADE~~~~~~~~~~~~~~~~~~~~~
if (sun){
	shadeX = -1.0;
	shadedX += 0.0015;
	glBegin(GL_POLYGON);
		glColor4f(0.2,0.19,0.19,0.5);
		glVertex2f(-0.82, -0.9);
		glVertex2f(-1.0, -0.96);
		glVertex2f(-1.0,-1.0);
		glVertex2f(shadeX+shadedX,-1.0);
		glVertex2f(-0.6,-0.9);
	glEnd();

}
else if (!sun){
	shadeX = -1.0;
	shadedX = 0.0;

//~~~~~~~~~~~~~~~~~~~~~~~~WINDOW SHADE~~~~~~~~~~~~~~~~~
	glColor4f(1.0,1.0,0.0,0.2);
	glBegin(GL_QUADS);
		glVertex2f(-0.45, -0.95);
		glVertex2f(-0.35, -1.0);
		glVertex2f(-0.25, -1.0);
		glVertex2f(-0.35, -0.95);

		glVertex2f(-0.3+0.05, -0.95);
		glVertex2f(-0.2+0.05, -1.0);
		glVertex2f(-0.1+0.05, -1.0);
		glVertex2f(-0.2+0.05, -0.95);

		glVertex2f(-0.15+0.1, -0.95);
		glVertex2f(-0.05+0.1, -1.0);
		glVertex2f(0.05+0.1, -1.0);
		glVertex2f(-0.05+0.1, -0.95);

		glVertex2f(-0.90+0.05+0.01,-0.95+0.02);
		glVertex2f(-1.0, -1.0);
		glVertex2f(-0.9, -1.0);
		glVertex2f(-0.8+0.05+0.01,-0.95+0.02);

	glEnd();
	
//~~~~~~~~~~~~~~~~~~~~~~END OF WINDOW SHADE~~~~~~~~~~~~
}


//~~~~~~~~~~~~END OF CASTLE SHADE~~~~~~~~~~~~~~~
//
//~~~~~~~~~~~~~~DOOR LINES~~~~~~~~~~~~~~~~~~~~~
	glLineWidth(4);
	glBegin(GL_LINES);
		glColor3ub(0,0,0);
		glVertex2f(-0.335,-0.9);
		glVertex2f(-0.335,-0.685);	
		glVertex2f(-0.37,-0.695);
		glVertex2f(-0.37, -0.9);
		glVertex2f(-0.3, -0.9);
		glVertex2f(-0.3, -0.695);
		glVertex2f(-0.4,-0.75);
		glVertex2f(-0.4,-0.9);
		glVertex2f(-0.27, -0.75);
		glVertex2f(-0.27,-0.9);
		glVertex2f(-0.4,-0.85);
		glVertex2f(-0.27,-0.85);
	glEnd();
		drawHollowCircleHalf(-0.335, -0.75, 0.065);
//~~~~~~~~~~~~~~~~~~END OF DOOR LINES~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~END OF STRONGHOLD~~~~~~~~~~~~~~~~~~~~~~~~~~~
   glFlush();  // Render now
}

void keyPressed (unsigned char key, int x, int y) {  

	if (key == 'd') { // If they ‘a’ key was pressed  
		glutDisplayFunc(display_day); // Register display callback handler for window re-paint
	}

	if (key == 'm'){
		glutDisplayFunc(display_morning);
	}

	if (key == 'e'){
		glutDisplayFunc(display_evening);
	}	
	if (key == 'l'){
		glutDisplayFunc(display_loop);
	}
}  



void reshape (int width, int height) {  
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window  
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed  
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)  
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes  
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly  
} 

/* Main function: GLUT runs as a console application starting at main()  */

int main(int argc, char** argv) {
    glutInit(&argc, argv);                 // Initialize GLUT
    glutInitWindowSize(650, 650);   // Set the window's initial width & height
    glutInitWindowPosition(0, 0); // Position the window's initial top-left corner

    glutCreateWindow("Stronghold"); // Create a window with the given title
   
    glutDisplayFunc(display_loop); // Register display callback handler for window re-paint
	glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping 
	glutKeyboardFunc(keyPressed); 
	glutTimerFunc(1000/60,timer,0);
    glutMainLoop();           // Enter the event-processing loop
    return 0;
}
