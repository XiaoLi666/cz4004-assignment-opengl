/* 
	What's new in this program?

  1. this program supports the mouse-based camera control. 
       to rotate the object, click the left button and move the mouse
	   to scale the object, click the middle button and move the mouse in y-direction, i.e., up and down

  2. this program draws the objects (cube, torus and teapot) in three modes, wireframe, solid, edges+solid
       press 'w', 's', and 'e' to set the display modes 
       
*/

#include <iostream>
#include <glut.h>
#include <cstdlib>
using namespace std;

#define TRANSFORM_NONE    0 
#define TRANSFORM_ROTATE  1
#define TRANSFORM_SCALE 2 

#define OBJ_WIREFRAME	0
#define OBJ_SOLID		1
#define OBJ_EDGE		2 

static int win;
static int menid;
static int submenid;
static int primitive = 0;

static int press_x, press_y; 
static float x_angle = 0.0; 
static float y_angle = 0.0; 
static float scale_size = 1; 

static int obj_mode = 0;
static int xform_mode = 0; 

#include "CMFileLoader.h"
#include "CModel.h"
#include "CCoordinates.h"
#include "CVector3.h"
using namespace CZ4004;

CModel * new_model;
CCoordinate * coordinate;

void menu(int value)
{
	if (value == 0)
	{
		glutDestroyWindow(win);
		exit(0);
	}
	else
	{
		primitive=value;
	}
  
	// you would want to redraw now
	glutPostRedisplay();
}

void createmenu(void)
{
	//// Testing code added by ZiLi
	//// CMFileLoader::GetInstance()->Load("bottle.m");
	//new_model = new CModel("bimba.m");
	//// new_model = new CModel("cap.m");
	//// CVector3 * v1 = new CVector3(2.0f,0.0f,0.0f);
	//// CVector3 * v2 = new CVector3(0.0f,0.0f,2.0f);
	//// CVector3 * cp = v1->CrossProduct(v2);
	//// cp->Normalize();
	//// setup OpenGL lighting

	//// Create a submenu, this has to be done first.
	//submenid = glutCreateMenu(menu);

	//// Add sub menu entry
	//glutAddMenuEntry("Teapot", 2);
	//glutAddMenuEntry("Cube", 3);
	//glutAddMenuEntry("Torus", 4);

	//// Create the menu, this menu becomes the current menu
	//menid = glutCreateMenu(menu);

	//// Create an entry
	//glutAddMenuEntry("Clear", 1);

	//glutAddSubMenu("Draw", submenid);
	//// Create an entry
	//glutAddMenuEntry("Quit", 0);

	//// Let the menu respond on the right mouse button
	//glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void disp(void)
{	
	glEnable(GL_DEPTH_TEST); 

	// Just clean the screen
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// setup the perspective projection
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluPerspective(60, 1, .1, 200);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); 
	gluLookAt(15,15,15,0,0,0,0,1,0); 

	GLfloat light_position[] = { 0.0, 20.0, 0.0, 0.0 };  // light position 
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };  // light color
	GLfloat lmodel_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };  
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);  

	glPushMatrix();
	// rotate and scale the object
	glRotatef(x_angle, 0, 1,0); 
	glRotatef(y_angle, 1,0,0); 
	glScalef(scale_size, scale_size, scale_size); 
	new_model->Render();
	glPopMatrix();

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);  
	coordinate->Render();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);  
	
	// swap the buffers
	glutSwapBuffers(); 
}


void mymouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) 
	{
		press_x = x; press_y = y; 
		if (button == GLUT_LEFT_BUTTON)
			xform_mode = TRANSFORM_ROTATE; 
		else if (button == GLUT_MIDDLE_BUTTON) 
			xform_mode = TRANSFORM_SCALE; 
	}
	else if (state == GLUT_UP) 
	{
		xform_mode = TRANSFORM_NONE; 
	}
}

void mymotion(int x, int y)
{
	if (xform_mode == TRANSFORM_ROTATE) 
	{
		x_angle += (x - press_x)/5.0; 

		if (x_angle > 180) 
			x_angle -= 360; 
		else if (x_angle <-180) 
			x_angle += 360; 
      
		press_x = x; 
	   
		y_angle += (y - press_y)/5.0; 

		if (y_angle > 180) 
			y_angle -= 360; 
		else if (y_angle <-180) 
			y_angle += 360; 
      
		press_y = y; 
    }
	else if (xform_mode == TRANSFORM_SCALE)
	{
		float old_size = scale_size;
		
		scale_size *= (1 + (y - press_y)/60.0); 

		if (scale_size <0) 
			scale_size = old_size; 
		press_y = y; 
    }

	// force the redraw function
	glutPostRedisplay(); 
}

void mykey(unsigned char key, int x, int y)
{
	switch(key) 
	{
	case 'w': 
		cout << "key 'w' is pressed! draw the object in wireframe" << endl;
		obj_mode = OBJ_WIREFRAME;
		break; 
	case 's':
		cout << "key 's' is pressed! draw the object in solid" << endl;
		obj_mode = OBJ_SOLID;
		break;
	case 'e':
		cout << "key 'e' is pressed! draw the object in solid+wireframe" << endl;
		obj_mode = OBJ_EDGE;
		break;
	}

	// force the redraw function
	glutPostRedisplay(); 
}


int main(int argc, char **argv)
{
	// normal initialisation
	glutInit(&argc, argv);
	// use double buffer to get better results on animation
	// use depth buffer for hidden surface removal
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	
	glutInitWindowSize(800,600);
	glutInitWindowPosition(100,100);

	win = glutCreateWindow("GLUT Transformation");
  
	// put all the menu functions in one nice procedure
	createmenu();

	new_model = new CModel("bimba.m");
	coordinate = new CCoordinate();

	// set the clearcolor and the callback
	glClearColor(0.0,0.0,0.0,0.0);

	// register your callback functions
	glutDisplayFunc(disp);
	glutMouseFunc(mymouse);
	glutMotionFunc(mymotion);
	glutKeyboardFunc(mykey);

	// enter the main loop
	glutMainLoop();

	return 1;
}
