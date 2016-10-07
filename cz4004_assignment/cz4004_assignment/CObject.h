#ifndef __COBJECT_H__
#define __COBJECT_H__

#include "CVector3.h"

namespace CZ4004
{
	class CObject
	{
	public:
		virtual void Render() = 0;

	private:
		CVector3 m_position;
	};
}

#endif // __COBJECT_H__