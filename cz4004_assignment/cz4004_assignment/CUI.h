#ifndef __CUI_H__
#define __CUI_H__

#include "GL\glui.h"

namespace CZ4004
{
	class CUI
	{
	public:
		static CUI * m_instance;
		static CUI * GetInstance()
		{
			if (!m_instance)
			{
				m_instance = new CUI();
			}
			return m_instance;
		}

		void Initialize(int main_window);
		inline const int GetProjectionMode() const { return m_projectionMode; }
		inline const int GetRenderingMode() const { return m_renderingMode; }
		inline const int GetEnableGround() const { return m_enableGround; }
		inline const int GetEnableCoordinate() const { return m_enableCoordinate; }
		inline const int GetShowBoundingBox() const { return m_showBoundingBox; }
		inline const int GetEnableBoundingBox() const { return m_enableBoundingBox; }
		inline const int GetEnableBackFaceCulling() const { return m_enableBackFaceCulling; }
		inline const int GetModelListboxSelectedId() const { return m_modelListbox->get_int_val(); }
		inline const int GetEnableColorfulLight() const { return m_enableColorfulLights; }

	private:
		CUI();
		~CUI();
		// void LoadModelCallBack(int id);

	private:
		int m_mainWindow;
		
		int m_projectionMode;
		int m_renderingMode;
		int m_enableGround;
		int m_enableCoordinate;
		int m_showBoundingBox;
		int m_enableBoundingBox;
		int m_enableBackFaceCulling;
		int m_enableColorfulLights;

		GLUI * m_subWindow;
		GLUI_Listbox * m_modelListbox;
	};
}

#endif // __CUI_H__