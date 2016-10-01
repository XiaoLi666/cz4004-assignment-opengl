#ifndef __CCOORDINATE_H__
#define __CCOORDINATE_H__

#include "CObject.h"

namespace CZ4004
{
	class CCoordinate : public CObject
	{
	public:
		CCoordinate();
		virtual void Render();

	private:
		void DrawXAxis();
		void DrawYAxis();
		void DrawZAxis();
	};
}

#endif // __CCOORDINATE_H__