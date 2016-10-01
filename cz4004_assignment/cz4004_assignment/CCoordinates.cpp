#include <stdlib.h>
#include "glut.h"

#include "CCoordinates.h"

using namespace CZ4004;

CCoordinate::CCoordinate()
{
}

void CCoordinate::Render()
{
	glColor3f(1.0,0.0,0.0);
	DrawXAxis();
	glColor3f(0.0,1.0,0.0);
	DrawYAxis();
	glColor3f(0.0,0.0,1.0);
	DrawZAxis();
	glColor3f(0.0,0.0,0.0);
}

void CCoordinate::DrawXAxis()
{
	const float cylinder_height = 10.0f;

	glPushMatrix();
		glRotatef(90.0f,0.0f,1.0f,0.0f);

		GLUquadricObj * quadratic = gluNewQuadric();
		gluQuadricNormals(quadratic, GLU_SMOOTH);
		gluCylinder(quadratic,0.2,0.2,cylinder_height,32,32);
		
		glPushMatrix();
		glTranslatef(0.0,0.0,cylinder_height);
			glutSolidCone(0.5,1.5,32,32);
		glPopMatrix();
		glutWireCube(3.0);
	glPopMatrix();
}

void CCoordinate::DrawYAxis()
{
	const float cylinder_height = 10.0f;

	glPushMatrix();
		glRotatef(-90.0f,1.0f,0.0f,0.0f);

		GLUquadricObj * quadratic = gluNewQuadric();
		gluQuadricNormals(quadratic, GLU_SMOOTH);
		gluCylinder(quadratic,0.2,0.2,cylinder_height,32,32);
		
		glPushMatrix();
		glTranslatef(0.0,0.0,cylinder_height);
			glutSolidCone(0.5,1.5,32,32);
		glPopMatrix();
		glutWireCube(3.0);
	glPopMatrix();
}

void CCoordinate::DrawZAxis()
{
	const float cylinder_height = 10.0f;

	glPushMatrix();
		GLUquadricObj * quadratic = gluNewQuadric();
		gluQuadricNormals(quadratic, GLU_SMOOTH);
		gluCylinder(quadratic,0.2,0.2,cylinder_height,32,32);
		
		glPushMatrix();
		glTranslatef(0.0,0.0,cylinder_height);
			glutSolidCone(0.5,1.5,32,32);
		glPopMatrix();
		glutWireCube(3.0);
	glPopMatrix();
}