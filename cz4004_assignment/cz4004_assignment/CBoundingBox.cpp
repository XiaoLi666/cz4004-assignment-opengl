#include <stdlib.h>
#include <iostream>
#include "glut.h"

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
}

void CBoundingBox::Render()
{
	glPushMatrix();
	glColor3f(1.0f,1.0f,1.0f);
		glScalef(m_maxVertex.x-m_minVertex.x, m_maxVertex.y-m_minVertex.y, m_maxVertex.z-m_minVertex.z);
		// glTranslatef((m_maxVertex.x-m_minVertex.x)*0.5f, (m_maxVertex.y-m_minVertex.y)*0.5f, (m_maxVertex.z-m_minVertex.z)*0.5f);
		glutWireCube(1.0);
	glPopMatrix();
}