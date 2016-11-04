#include <stdlib.h>
#include "glut.h"
#include "CGround.h"

using namespace CZ4004;

CGround::CGround(float length, float width, unsigned int density)
	: m_length(length)
	, m_width(width)
	, m_density(density)
{
}

void CGround::Render()
{
	for (unsigned int i = 0; i < m_density + 1; ++ i)
	{
		glBegin(GL_LINES);
		glColor4f(1.f, 1.f, 1.f, .1f);
		glVertex3f(-m_length * 0.5f + i * m_length / m_density, 0.0f, -m_width * 0.5f);
		glVertex3f(-m_length * 0.5f + i * m_length / m_density, 0.0f,  m_width * 0.5f);
		glEnd();
	}

	for (unsigned int i = 0; i < m_density + 1; ++i)
	{
		glBegin(GL_LINES);
		glColor4f(1.f, 1.f, 1.f, .1f);
		glVertex3f(-m_length * 0.5f, 0.0f, -m_width * 0.5f + i * m_width / m_density);
		glVertex3f( m_length * 0.5f, 0.0f, -m_width * 0.5f + i * m_width / m_density);
		glEnd();
	}
}