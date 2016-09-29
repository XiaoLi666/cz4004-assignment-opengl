#ifndef __CMODEL_H__
#define __CMODEL_H__

#include <vector>
#include <map>
#include "CMovableObject.h"
#include "CMeshDataStruct.h"

namespace CZ4004
{
	class CModel : public CMovableObject
	{
	public:
		CModel(const std::string & file_name);
		virtual void Render();
		virtual void Update();

	private:
		void Create();
		void InitEdge(HE_edge * edge_to_init, HE_vert * vertex, HE_vert * vert_to_pair, HE_face * face, HE_edge * prev, HE_edge * next);
		void PairEdge(HE_vert * vertex, HE_edge * edge);
		void ClearCachedData();

	private:
		std::vector<HE_vert *> m_vertices;
		std::vector<HE_face *> m_faces;
		std::vector<HE_edge *> m_edges;

		// TODO:
		// Going to find the min and max point coordinates
		HE_vert * m_minVertex;
		HE_vert * m_maxVertex;

		std::vector<Face_Loaded_Data *> m_facesLoadedData;
		std::map<HE_vert *, HE_edge *> m_edgesToPair;
	};
}

#endif // __CMODEL_H__