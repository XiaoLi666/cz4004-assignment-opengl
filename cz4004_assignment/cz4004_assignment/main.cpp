#include <string.h>
#include "GL\glui.h"
#include "GL\glut.h"

int main_window;
// Define for this assignment
#include "CUI.h"
#include "CGround.h"
#include "CCoordinates.h"
#include "CModel.h"
using namespace std;
using namespace CZ4004;
CGround * ground = new CGround(80.0f, 80.0f, 20);
CCoordinate * coordinate = new CCoordinate();
CModel * model = nullptr;

#define TRANSFORM_NONE		0
#define TRANSFORM_ROTATE	1
#define TRANSFORM_SCALE		2
#define TRANSFORM_TRANSLATE 3

static int win;
static int menid;
static int submenid;
static int primitive = 0;


static int press_x, press_y;

static float x_trans = 0.0;
static float y_trans = 0.0;

static float x_angle = 0.0;
static float x_angle_prev = 0.0;
static float y_angle = 0.0; 
static float y_angle_prev = 0.0;
static float scale_size = 1; 
static int obj_mode = 0;
static int xform_mode = 0; 

void CreateModel()
{
	int model_id = CUI::GetInstance()->GetModelListboxSelectedId();
	string model_name = "";
	switch(model_id)
	{
	case 0:
		model_name = "bimba.m";
		break;
	case 1:
		model_name = "bottle.m";
		break;
	case 2:
		model_name = "bunny.m";
		break;
	case 3:
		model_name = "cap.m";
		break;
	case 4:
		model_name = "eight.m";
		break;
	case 5:
		model_name = "gargoyle.m";
		break;
	case 6:
		model_name = "knot.m";
		break;
	case 7:
		model_name = "statute.m";
		break;
	default:break;
	}

	if (model_name == "")
	{
		printf("Error: Invalid model id, cannot create the model1\n");
		return;
	}

	model = new CModel(model_name);

	// Reset some global values
	primitive = 0;
	x_angle = 0.0;
	y_angle = 0.0;
	x_trans = 0.0;
	y_trans = 0.0;
	x_angle_prev = 0.0;
	y_angle_prev = 0.0;
	scale_size = 1;
	obj_mode = 0;
	xform_mode = 0;
}

void DeleteModel()
{
	if (!model)
	{
		delete model;
		model = nullptr;
	}
}

// Callback functions
void CUICallBack(int id)
{
	switch (id)
	{
	case 0:
		CreateModel();
		DeleteModel();
		break;
	default:
		break;
	}
}

void myGlutIdle(void)
{
	if (glutGetWindow() != main_window)
		glutSetWindow(main_window);
	glutPostRedisplay();
}

void myGlutReshape( int x, int y )
{
	float xy_aspect;
	xy_aspect = (float) x / (float) y;
	glViewport(0, 0, (GLsizei)x, (GLsizei)y);
	// GLUI_Master.auto_set_viewport();
	glutPostRedisplay();
}

void myGlutDisplay( void )
{
	glClearColor( .9f, .9f, .9f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	
	if (CUI::GetInstance()->GetProjectionMode() == 0)
	{
		gluPerspective(60, 1, .1, 200);
	}
	else
	{
		// glOrtho(-x/20, x/20, -y/20, y/20, 0, 200);
		// glFrustum(-xy_aspect*.08, xy_aspect*.08, -.08, .08, .1, 15.0);
		glOrtho(-30, 30, -30, 30, -1, 200);
	}

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	gluLookAt(60,60,60,0,0,0,0,1,0);

  	GLfloat light_position_0[] = { 0.0, 0.0, 10.0, 0.0 };  // light position
	GLfloat light_position_1[] = { 0.0, 0.0, -10.0, 0.0 };  // light position
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };  // light color white
	GLfloat green_light[] = { 0.0, 0.0, 1.0, 1.0 };  // light color green
	GLfloat blue_light[] = { 0.0, 1.0, 0.0, 1.0 };  // light color blue
	GLfloat lmodel_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	
	if (CUI::GetInstance()->GetEnableColorfulLight())
	{
		glLightfv(GL_LIGHT0, GL_POSITION, light_position_0);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, green_light);
		glLightfv(GL_LIGHT0, GL_SPECULAR, green_light);
		glLightfv(GL_LIGHT1, GL_POSITION, light_position_1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, blue_light);
		glLightfv(GL_LIGHT1, GL_SPECULAR, blue_light);
	}
	else
	{
		glLightfv(GL_LIGHT0, GL_POSITION, light_position_0);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
		glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
		glLightfv(GL_LIGHT1, GL_POSITION, light_position_1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, white_light);
		glLightfv(GL_LIGHT1, GL_SPECULAR, white_light);
	}

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	if (CUI::GetInstance()->GetEnableGround()) ground->Render();
	if (CUI::GetInstance()->GetEnableCoordinate()) coordinate->Render();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glPushMatrix();
		// glRotatef(x_angle, 0,1,0);
		// glRotatef(y_angle, 1,0,0);
		glTranslatef(x_trans, 0, y_trans);
		glScalef(scale_size, scale_size, scale_size);
		if (model)
			model->Render();
	glPopMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);

	glutSwapBuffers();
}

void mymouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) // press down mouse button
	{
		press_x = x; press_y = y; 
		if (button == GLUT_LEFT_BUTTON)
			xform_mode = TRANSFORM_ROTATE; 
		else if (button == GLUT_RIGHT_BUTTON) 
			xform_mode = TRANSFORM_SCALE; 
		else if (button == GLUT_MIDDLE_BUTTON)
			xform_mode = TRANSFORM_TRANSLATE;
	}
	else if (state == GLUT_UP) // release mouse button
	{
		xform_mode = TRANSFORM_NONE;
	}
}

void mymotion(int x, int y)
{
	if (xform_mode == TRANSFORM_ROTATE) 
	{
		x_angle += (x-press_x)/5.0;
		if (x_angle > 180) x_angle -= 360;
		else if (x_angle <-180) x_angle += 360;
     	press_x = x;

		y_angle += (y - press_y) / 5.0;
		if (y_angle > 180) y_angle -= 360;
		else if (y_angle <-180) y_angle += 360;
		press_y = y;

		model->SetRotation(x_angle - x_angle_prev, y_angle - y_angle_prev);
		x_angle_prev = x_angle; y_angle_prev = y_angle;
    }
	else if (xform_mode == TRANSFORM_SCALE)
	{
		float old_size = scale_size;
		
		scale_size *= (1 + (y - press_y)/60.0); 

		if (scale_size <0) 
			scale_size = old_size; 
		press_y = y; 
    }
	else if (xform_mode == TRANSFORM_TRANSLATE)
	{
		x_trans += (x-press_x)/5.0;
		if (x_trans > 180) x_trans -= 360;
		else if (x_trans <-180) x_trans += 360;
     	press_x = x;

		y_trans += (y - press_y) / 5.0;
		if (y_trans > 180) y_trans -= 360;
		else if (y_trans <-180) y_trans += 360;
		press_y = y;
	}

	// force the redraw function
	glutPostRedisplay(); 
}

int main(int argc, char* argv[])
{
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(1280, 800);

	main_window = glutCreateWindow( "CZ4004 Programming Assignment" );
	
	glutMouseFunc(mymouse);
	glutMotionFunc(mymotion);

	glutDisplayFunc( myGlutDisplay );
	glutReshapeFunc( myGlutReshape );

	glEnable(GL_DEPTH_TEST);
	CUI::GetInstance()->Initialize(main_window);

	/* We register the idle callback with GLUI, *not* with GLUT */
	GLUI_Master.set_glutIdleFunc( myGlutIdle );
	GLUI_Master.set_glutReshapeFunc( myGlutReshape );
	glutMainLoop();
}