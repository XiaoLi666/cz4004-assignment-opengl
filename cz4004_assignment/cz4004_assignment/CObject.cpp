#include <iostream>
#include <stdlib.h>
#include "glut.h"

#include "CObject.h"

using namespace CZ4004;

void CObject::RenderOption()
{
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH); // GL_FLAT or GL_SMOOTH
}