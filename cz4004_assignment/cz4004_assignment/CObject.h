#ifndef __COBJECT_H__
#define __COBJECT_H__

#include "CVector3.h"

namespace CZ4004
{
	class CObject
	{
	public:
		virtual void Render()
		{
			RenderOption();
		}

		// void SetRenderOption();

	protected:
		void RenderOption();
	};
}

#endif // __COBJECT_H__