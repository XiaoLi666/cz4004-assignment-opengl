#include <stdlib.h>
#include <iostream>
#include "GL\glut.h"

#include "CBoundingBox.h"

using namespace CZ4004;

CBoundingBox::CBoundingBox()
{
}

void CBoundingBox::Initialize(CVector3 * min_vertex, CVector3 * max_vertex)
{
	if (!min_vertex || !max_vertex)
		printf("Invalid parameters passed into Bounding Box\n");

	m_minVertex.Set(min_vertex->x,min_vertex->y,min_vertex->z);
	m_maxVertex.Set(max_vertex->x,max_vertex->y,max_vertex->z);

	// Create the eight coordinates for AABB
	m_coordinates[0].Set(m_minVertex.x, m_minVertex.y, m_minVertex.z);
	m_coordinates[1].Set(m_maxVertex.x, m_minVertex.y, m_minVertex.z);
	m_coordinates[2].Set(m_maxVertex.x, m_minVertex.y, m_maxVertex.z);
	m_coordinates[3].Set(m_minVertex.x, m_minVertex.y, m_maxVertex.z);
	m_coordinates[4].Set(m_minVertex.x, m_maxVertex.y, m_minVertex.z);
	m_coordinates[5].Set(m_maxVertex.x, m_maxVertex.y, m_minVertex.z);
	m_coordinates[6].Set(m_maxVertex.x, m_maxVertex.y, m_maxVertex.z);
	m_coordinates[7].Set(m_minVertex.x, m_maxVertex.y, m_maxVertex.z);
}

void CBoundingBox::Render()
{
	// Method 1: Using glutWireCube(...)
	//glPushMatrix();
	//glColor3f(1.0f,1.0f,1.0f);
	//	glTranslatef((m_maxVertex.x+m_minVertex.x)*0.5f, (m_maxVertex.y+m_minVertex.y)*0.5f, (m_maxVertex.z+m_minVertex.z)*0.5f);
	//	glScalef(m_maxVertex.x-m_minVertex.x, m_maxVertex.y-m_minVertex.y, m_maxVertex.z-m_minVertex.z);
	//	glutWireCube(1.0);
	//glPopMatrix();

	// Method 2: Using AABB bounding box
	glPushMatrix();
		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_LINES);
		glVertex3f(m_coordinates[0].x, m_coordinates[0].y, m_coordinates[0].z);
		glVertex3f(m_coordinates[1].x, m_coordinates[1].y, m_coordinates[1].z);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_LINES);
		glVertex3f(m_coordinates[1].x, m_coordinates[1].y, m_coordinates[1].z);
		glVertex3f(m_coordinates[2].x, m_coordinates[2].y, m_coordinates[2].z);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_LINES);
		glVertex3f(m_coordinates[2].x, m_coordinates[2].y, m_coordinates[2].z);
		glVertex3f(m_coordinates[3].x, m_coordinates[3].y, m_coordinates[3].z);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_LINES);
		glVertex3f(m_coordinates[3].x, m_coordinates[3].y, m_coordinates[3].z);
		glVertex3f(m_coordinates[0].x, m_coordinates[0].y, m_coordinates[0].z);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_LINES);
		glVertex3f(m_coordinates[4].x, m_coordinates[4].y, m_coordinates[4].z);
		glVertex3f(m_coordinates[5].x, m_coordinates[5].y, m_coordinates[5].z);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_LINES);
		glVertex3f(m_coordinates[5].x, m_coordinates[5].y, m_coordinates[5].z);
		glVertex3f(m_coordinates[6].x, m_coordinates[6].y, m_coordinates[6].z);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_LINES);
		glVertex3f(m_coordinates[6].x, m_coordinates[6].y, m_coordinates[6].z);
		glVertex3f(m_coordinates[7].x, m_coordinates[7].y, m_coordinates[7].z);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_LINES);
		glVertex3f(m_coordinates[7].x, m_coordinates[7].y, m_coordinates[7].z);
		glVertex3f(m_coordinates[4].x, m_coordinates[4].y, m_coordinates[4].z);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_LINES);
		glVertex3f(m_coordinates[0].x, m_coordinates[0].y, m_coordinates[0].z);
		glVertex3f(m_coordinates[4].x, m_coordinates[4].y, m_coordinates[4].z);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_LINES);
		glVertex3f(m_coordinates[1].x, m_coordinates[1].y, m_coordinates[1].z);
		glVertex3f(m_coordinates[5].x, m_coordinates[5].y, m_coordinates[5].z);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_LINES);
		glVertex3f(m_coordinates[2].x, m_coordinates[2].y, m_coordinates[2].z);
		glVertex3f(m_coordinates[6].x, m_coordinates[6].y, m_coordinates[6].z);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_LINES);
		glVertex3f(m_coordinates[3].x, m_coordinates[3].y, m_coordinates[3].z);
		glVertex3f(m_coordinates[7].x, m_coordinates[7].y, m_coordinates[7].z);
		glEnd();
	glPopMatrix();
}