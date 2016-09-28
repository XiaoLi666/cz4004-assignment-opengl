#ifndef __CMOVABLEOBJECT_H__
#define __CMOVABLEOBJECT_H__

#include "CObject.h"

namespace CZ4004
{
	class CMovableObject : public CObject
	{
	public:
		virtual void Update() = 0;
	};
}

#endif // __CMOVABLEOBJECT_H__