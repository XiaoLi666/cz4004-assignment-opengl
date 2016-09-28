#ifndef __CMODEL_H__
#define __CMODEL_H__

#include <vector>
#include "CMovableObject.h"

namespace CZ4004
{
	struct HE_vert;
	struct HE_face;

	struct HE_edge
	{
		HE_vert * vert;
		HE_edge * pair;
		HE_face * face;
		HE_edge * prev;
		HE_edge * next;
	};

	struct HE_vert
	{
		float x, y, z;
		HE_edge * edge;
	};

	struct HE_face
	{
		HE_edge * edge;
	};

	class CModel : public CMovableObject
	{
	public:
		void Initialization(/*TODO:*/);
		virtual void Render();

	private:
		std::vector<HE_vert> m_vertices;
		std::vector<HE_face> m_faces;
	};
}

#endif // __CMODEL_H__