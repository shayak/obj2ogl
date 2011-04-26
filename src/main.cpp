#include <iomanip>
#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <obj2ogl.h>
using namespace std;

// light
GLfloat lita[] = {0.0, 0.0, 0.0, 1.0};
GLfloat litds[] = {1.0, 1.0, 1.0, 1.0};
GLfloat lit0pos[] = {5.0, 0.0, 5.0};
GLfloat lit1pos[] = {-5.0, 10.0, 0.0};

// material
GLfloat mata[] = {0.5, 0.0, 0.0, 1.0};
GLfloat matd[] = {1.0, 1.0, 1.0, 1.0};
GLfloat mats[] = {1.0, 1.0, 1.0, 1.0};
GLfloat matshin[] = {360.784314};

double xrot = 0.0, yrot = 0.0, xvel = 2.0, yvel = 2.0;

void init();
void set2Dmode();
void set3Dmode();
void lighting();
void display();
void keys(unsigned char, int, int);
void speckeys(int, int, int);

Model mod;

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Shit");
	glutDisplayFunc(display);
	glutKeyboardFunc(keys);
	glutSpecialFunc(speckeys);
	init();
	mod = Model("models/ant/ant.obj", 1);
	//mod = Model("/home/shek/workspace/github/obj2ogl/models/redball/redball.obj",1);
	glutMainLoop();
	return 0;
}

void init()
{
	/* set clear color to black */
	glClearColor (0.0, 0.0, 0.0, 1.0);

	/* set fill color to white */
	//glColor3f(1.0, 0.0, 0.0); 

	/* set up standard orthogonal view with clipping */
	/* box as cube of side 2 centered at origin */
	/* This is default view and these statement could be removed */
	set3Dmode();
	// lighting
	lighting();
	glEnable(GL_DEPTH_TEST);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();

	glPushMatrix();
		glTranslatef(0.0, 0.0, 15.0);
		glRotatef(yrot, 0.0, 1.0, 0.0);
		glRotatef(xrot, 1.0, 0.0, 0.0);
		glScalef(2.0, 2.0, 2.0);
		mod.drawModel();
	glPopMatrix();

	xrot += xvel;
	yrot += yvel;

	if (xrot > 360.0) xrot -= 360.0;
	if (yrot > 360.0) yrot -= 360.0;

	glutSwapBuffers();
	glutPostRedisplay();
}

void set2Dmode()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,499, 0, 499);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void set3Dmode()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 1.0, 1000);
	gluLookAt(0.0, 0.0, 0.0,
				0.0, 0.0, 1.0,
					0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void lighting()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, lita);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, litds);
	glLightfv(GL_LIGHT0, GL_SPECULAR, litds);
	glLightfv(GL_LIGHT0, GL_POSITION, lit0pos);
	
	glLightfv(GL_LIGHT1, GL_AMBIENT, lita);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, litds);
	glLightfv(GL_LIGHT1, GL_SPECULAR, litds);
	glLightfv(GL_LIGHT1, GL_POSITION, lit1pos);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mata);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mats);
	glMaterialfv(GL_FRONT, GL_SHININESS, matshin);
}

void keys(unsigned char key, int x, int y)
{
	if (key==27)
		exit(0);
	if (key=='f' || key=='F')
		mod.setShading(0);
	if (key=='s' || key=='S')
		mod.setShading(1);
}

void speckeys(int key, int x, int y) 
{
	if (key==GLUT_KEY_LEFT)
	{
		xvel = xvel * 0.8;
	}
	if (key==GLUT_KEY_RIGHT) 
	{
		xvel = xvel * 1.2;
	}
	if (key==GLUT_KEY_UP) 
	{
		yvel = yvel * 1.2;
	}
	if (key==GLUT_KEY_DOWN) 
	{
		yvel = yvel * 0.8;
	}
}
