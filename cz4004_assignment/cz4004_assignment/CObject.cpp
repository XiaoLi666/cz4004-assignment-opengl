#include <iostream>
#include <stdlib.h>
#include "GL\glut.h"

#include "CObject.h"
#include "CUI.h"

using namespace CZ4004;

void CObject::RenderOption()
{
	glEnable(GL_NORMALIZE);

	if (CUI::GetInstance()->GetEnableBackFaceCulling() == 1)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
	}
	else
	{
		glDisable(GL_CULL_FACE);
	}

	int rendering_mode = CUI::GetInstance()->GetRenderingMode();

	switch (rendering_mode)
	{
	case 0: // smooth shading
		glShadeModel(GL_SMOOTH);
		break;
	case 1: // flat shading
		glShadeModel(GL_FLAT);
		break;
	case 2: // points
		glShadeModel(GL_SMOOTH);
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);  
		break;
	case 3: // wireframe rendering
		glShadeModel(GL_SMOOTH);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);  
		break;
	default:
		break;
	}
}