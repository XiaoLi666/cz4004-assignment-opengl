#ifndef __CLIGHT_H__
#define __CLIGHT_H__

#include "CVector3.h"
#include "CMovableObject.h"

#define LIGHT_ARRAY_SIZE 4

namespace CZ4004
{
	class CLight : public CMovableObject
	{
	public:
		CLight();
		void EnableLight(const bool is_enable);
		virtual void Render();
		virtual void Update();

	private:
		CVector3 m_position;
		//GLfloat m_whiteLight[LIGHT_ARRAY_SIZE];
		//GLfloat m_lmodelAmbient[LIGHT_ARRAY_SIZE];
	};
}

#endif // __CLIGHT_H__