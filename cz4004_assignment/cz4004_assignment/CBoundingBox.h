#ifndef __CBOUNDINGBOX_H__
#define __CBOUNDINGBOX_H__

#include "CObject.h"

namespace CZ4004
{
	// AABB bounding box
	class CBoundingBox : public CObject
	{
	public:
		virtual void Render();

	private:
		CObject * owner;
	};
}

#endif // __CBOUNDINGBOX_H__