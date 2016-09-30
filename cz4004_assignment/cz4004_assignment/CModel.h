#ifndef __CMODEL_H__
#define __CMODEL_H__

#include <vector>
#include <map>
#include <deque>
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
		void PairEdge(HE_vert * start, HE_vert * end, HE_edge * edge);
		void CalNormalForFace(HE_face * face, CVector3 * v1, CVector3 * v2, CVector3 * v3);
		void CalNormalForAllVertices();
		void CalMinMaxVertex(HE_vert * v); // TODO: this function seems does not work well
		void ClearCachedData();

		void BuildPairEdgeStruct(HE_edge * edge);
		void FindPairedEdgesForAllEdges();

	private:
		std::vector<HE_vert *> m_vertices;
		std::vector<HE_face *> m_faces;
		std::vector<HE_edge *> m_edges;
		HE_vert * m_minVertex;
		HE_vert * m_maxVertex; 

		std::vector<Face_Loaded_Data *> m_facesLoadedData;

		// TODO: this data structure is wrong
		// std::map<HE_vert *, HE_edge *> m_edgesToPair;
		std::map<HE_vert *, std::deque<HE_edge *>> m_edgesToPair;
	};
}

#endif // __CMODEL_H__