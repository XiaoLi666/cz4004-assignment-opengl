#include "CUI.h"

using namespace CZ4004;
using namespace std;

CUI * CUI::m_instance = nullptr;

// Declaration of Callback functions:
void CUICallBack(int id);
void (*CUICallBackFuncPtr)(int) = CUICallBack;

CUI::CUI()
	: m_mainWindow(0)
	, m_projectionMode(0)
	, m_renderingMode(0)
	, m_enableGround(1)
	, m_enableCoordinate(1)
	, m_showBoundingBox(1)
	, m_enableBoundingBox(1)
	, m_enableBackFaceCulling(1)
	, m_enableColorfulLights(0)
	, m_subWindow(nullptr)
	, m_modelListbox(nullptr)
{
}

CUI::~CUI()
{
}

void CUI::Initialize(int main_window)
{
	m_mainWindow = main_window;

	if (m_subWindow)
		printf("Sub window exists, something wrong? \n");

	m_subWindow = GLUI_Master.create_glui_subwindow(main_window, GLUI_SUBWINDOW);
	m_subWindow->set_main_gfx_window(m_mainWindow);
	
	m_modelListbox = m_subWindow->add_listbox("Model ");
	m_modelListbox->add_item(0,"bimba");
	m_modelListbox->add_item(1,"bottle");
	m_modelListbox->add_item(2,"bunny");
	m_modelListbox->add_item(3,"cap");
	m_modelListbox->add_item(4,"eight");
	m_modelListbox->add_item(5,"gargoyle");
	m_modelListbox->add_item(6,"knot");
	m_modelListbox->add_item(7,"statute");

	m_subWindow->add_button("Load Model", 0, CUICallBackFuncPtr);

	GLUI_Panel * projection_panel = m_subWindow->add_panel ("Projection Mode");
	GLUI_RadioGroup * projection_mode = m_subWindow->add_radiogroup_to_panel(projection_panel, &m_projectionMode);
	m_subWindow->add_radiobutton_to_group(projection_mode,"Perspective");
	m_subWindow->add_radiobutton_to_group(projection_mode,"Orthographic");

	GLUI_Panel * rendering_panel = m_subWindow->add_panel ("Rendering Mode");
	GLUI_RadioGroup * rendering_mode = m_subWindow->add_radiogroup_to_panel(rendering_panel, &m_renderingMode);
	m_subWindow->add_radiobutton_to_group(rendering_mode,"Smooth Shading");
	m_subWindow->add_radiobutton_to_group(rendering_mode,"Flat Shading");
	m_subWindow->add_radiobutton_to_group(rendering_mode,"Points");
	m_subWindow->add_radiobutton_to_group(rendering_mode,"Wireframe rendering");

	m_subWindow->add_checkbox("Ground", &m_enableGround);
	m_subWindow->add_checkbox("Coordinate", &m_enableCoordinate);
	m_subWindow->add_checkbox("Show BoundingBox", &m_showBoundingBox);
	m_subWindow->add_checkbox("Enable BoundingBox", &m_enableBoundingBox);
	m_subWindow->add_checkbox("Back Face Culling", &m_enableBackFaceCulling);
	m_subWindow->add_checkbox("Colorful Lights", &m_enableColorfulLights);

	m_subWindow->add_button("Exit Viewer",0,(GLUI_Update_CB)exit);
}