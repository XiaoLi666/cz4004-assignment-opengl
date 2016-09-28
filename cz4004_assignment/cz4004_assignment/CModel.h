#ifndef __CMODEL_H__
#define __CMODEL_H__

#include <vector>
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
		void ClearCachedData();

	private:
		std::vector<HE_vert *> m_vertices;
		std::vector<HE_face *> m_faces;
		std::vector<HE_edge *> m_edges;
		std::vector<Face_Loaded_Data *> m_facesLoadedData;
	};
}

#endif // __CMODEL_H__