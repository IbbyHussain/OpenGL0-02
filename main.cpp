#include "glut.h"



// camera variables
float camY = 5.f;
float camZ = 10.f;

void init()
{
	// rendering states
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// ogl default lighting
	glEnable(GL_LIGHTING); 
	glEnable(GL_LIGHT0);
}
void render()
{
	// Material code with shade blue using RGB. needs to be before rendering of object
	float clr[] = { 0.2f, 0.2f, 0.8f }; 
	glMaterialfv(GL_FRONT, GL_DIFFUSE, clr);

	// time-based animation control variable
	int time = glutGet(GLUT_ELAPSED_TIME);
	float theta = 0.1f * time;

	//clear screen abd buffers
	glClearColor(0.18f, 0.25f, 0.22f, 1.0f); // deep grey background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Setup the view point
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, camY, camZ, 0.0, camY - 5, camZ - 15, 0.0, 1.0, 0.0); // look at using camera variables
	//gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// Add rotation transfrom (deprecated) - animation
	glRotatef(theta, 0.0f, 1.0f, 0.0f);

	// LIGHTING, only works if object has material

	GLfloat clrWhite[] = { 1.0f, 1.0f, 1.0f }; 
	GLfloat posLight[] = { 3.0f, 3.0f, 0.0f, 1.0f }; 
	glLightfv(GL_LIGHT0, GL_AMBIENT, clrWhite);

	// ambient light colour
	glLightfv(GL_LIGHT0, GL_DIFFUSE, clrWhite); 

	// diffuse light colour
	glLightfv(GL_LIGHT0, GL_POSITION, posLight); // light position

	/*glBegin(GL_TRIANGLES);
	glVertex3f(-0.5, -0.5, 2.0);
	glVertex3f(0.5, 0.0, 1.0);
	glVertex3f(0.0, 0.5, 3.0);
	glEnd();*/

	// coloured triangle
	/*glBegin(GL_TRIANGLES); 
	glColor4f(1.0, 0.0, 0.0, 1.0); 
	glVertex3f(2.0, 2.5, -1.0); 
	glColor4f(0.0, 1.0, 0.0, 1.0); 
	glVertex3f(-3.5, -2.5, -1.0); 
	glColor4f(0.0, 0.0, 1.0, 1.0); 
	glVertex3f(2.0, -4.0, -1.0); 
	glEnd();*/

	// coloured pentagon
	/*glBegin(GL_TRIANGLE_FAN); 
	glColor4f(1.0, 1.0, 1.0, 1.0); 
	glVertex3f(-1.0, 2.0, 0.0); 
	glColor4f(1.0, 1.0, 0.0, 1.0); 
	glVertex3f(-3.0, -0.5, 0.0); 
	glColor4f(0.0, 1.0, 1.0, 1.0); 
	glVertex3f(-1.5, -3.0, 0.0); 
	glColor4f(0.0, 0.0, 0.0, 1.0); 
	glVertex3f(1.0, -2.0, 0.0); 
	glColor4f(1.0, 0.0, 1.0, 1.0); 
	glVertex3f(1.0, 1.0, 0.0); 
	glEnd();*/

	// 2.0 is size
	glutSolidTeapot(2.0); // displays a solid teapot

	//glutWireTeapot(2.01); // wireframe teapot

	// Used to move teapot somewhere in the scene
	//glTranslatef(0.0f, -1.0f, 3.0f);

	// doesnt work is deprecated
	glRotatef(90, 1.0f, 0.0f, 0.0f); 
	glRotatef(-theta, 0.0f, 1.0f, 0.0f);

	// essential for double-buffering technique
	glutSwapBuffers();

	// essential for animation
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	// find screen aspect ratio
	float ratio = w * 1.0 / h; // we hope that h is not zero


	// setup the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(60.0f, ratio, 1.0f, 100.0f);

	// set model/view matrix for rendering
	glMatrixMode(GL_MODELVIEW);
}

// control camera with a keyboard
void onKeyDown(unsigned char key, int x, int y) 
{
	switch (key)
	{
		// forward
	case 'w': camZ -= 0.4;
		break;
		// backward
	case 's': camZ += 0.4;
		break;
		// up
	case 'd': camY += 0.4;
		break;
		// down
	case 'a': camY -= 0.4;
		break;
	}
}

int main(int argc, char** argv)
{
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("CI5520 3D Graphics Programming");

	// register callbacks
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);

	// cmaera control function, register callback
	glutKeyboardFunc(onKeyDown);

	// init light and everything – not a GLUT or callback function!
	init();
	
	// enter GLUT event processing cycle
	glutMainLoop();
	return 1;
}

