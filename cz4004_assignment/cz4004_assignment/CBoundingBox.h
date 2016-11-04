#ifndef __CBOUNDINGBOX_H__
#define __CBOUNDINGBOX_H__

#include "CObject.h"
#include "CVector3.h"

namespace CZ4004
{
	// AABB bounding box
	class CBoundingBox : public CObject
	{
	public:
		CBoundingBox();
		void Initialize(CVector3 * min_vertex, CVector3 * max_vertex);
		virtual void Render();

	private:
		CVector3 m_minVertex;
		CVector3 m_maxVertex;
		CVector3 m_coordinates[8];
	};
}

#endif // __CBOUNDINGBOX_H__