#ifndef __CGROUND_H_
#define __CGROUND_H_

#include "CObject.h"

namespace CZ4004
{
	class CGround : public CObject
	{
	public:
		CGround(float length, float width, unsigned int density);
		virtual void Render();

	public:
		float m_length;
		float m_width;
		unsigned int m_density;
	};
}

#endif