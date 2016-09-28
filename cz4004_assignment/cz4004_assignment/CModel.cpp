#include "CModel.h"
#include "CMFileLoader.h"

using namespace CZ4004;

CModel::CModel(const std::string & file_name)
{
	CMFileLoader::GetInstance()->Load(file_name, m_vertices, m_facesLoadedData);
	printf("'%s' has been loaded! \n", file_name.c_str());

	// Create the 3D mesh by existing data
	Create();
}

void CModel::Create()
{
	printf("Start to create the 3D mesh ... \n");

	for (size_t i = 0; i < m_facesLoadedData.size(); ++ i)
	{
		HE_vert * v1 = m_vertices[m_facesLoadedData[i]->vertex1];
		HE_vert * v2 = m_vertices[m_facesLoadedData[i]->vertex2];
		HE_vert * v3 = m_vertices[m_facesLoadedData[i]->vertex3];

		HE_face * new_face = new HE_face();

		HE_edge * e_1_to_2 = new HE_edge();
		HE_edge * e_2_to_3 = new HE_edge();
		HE_edge * e_3_to_1 = new HE_edge();

		new_face->edge = e_1_to_2;
		m_faces.push_back(new_face);

		v1->edge = e_1_to_2;
		v2->edge = e_2_to_3;
		v3->edge = e_3_to_1;

		// Create edge 1:
		e_1_to_2->vert = v1;
		e_1_to_2->face = new_face;
		e_1_to_2->next = e_2_to_3;
		e_1_to_2->prev = e_3_to_1;
		e_1_to_2->pair = nullptr;

		// Create edge 2:
		e_2_to_3->vert = v2;
		e_2_to_3->face = new_face;
		e_2_to_3->next = e_3_to_1;
		e_2_to_3->prev = e_1_to_2;
		e_2_to_3->pair = nullptr;

		// Create edge 3:
		e_3_to_1->vert = v3;
		e_3_to_1->face = new_face;
		e_3_to_1->next = e_1_to_2;
		e_3_to_1->prev = e_2_to_3;
		e_3_to_1->pair = nullptr;
	}

	printf("3D mesh has been created! \n");
}

void CModel::ClearCachedData()
{
}

void CModel::Render()
{
}

void CModel::Update()
{
}