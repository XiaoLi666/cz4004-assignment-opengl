#ifndef __CCAMERA_H__
#define __CCAMERA_H__

#include "CMovableObject.h"
#include "CVector3.h"

namespace CZ4004
{
	class CCamera : public CMovableObject
	{
	public:
		CCamera();
		void Update();
		
	private:

	};
}

#endif // __CCAMERA_H__