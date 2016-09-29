#include "CModel.h"
#include "CMFileLoader.h"

using namespace CZ4004;
using namespace std;

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

		// TODO: going to check the min and max vertex of the whole 3D mesh

		HE_face * new_face = new HE_face();

		HE_edge * e_1_to_2 = new HE_edge();
		HE_edge * e_2_to_3 = new HE_edge();
		HE_edge * e_3_to_1 = new HE_edge();

		new_face->edge = e_1_to_2;
		m_faces.push_back(new_face);

		v1->edge = e_1_to_2;
		v2->edge = e_2_to_3;
		v3->edge = e_3_to_1;

		InitEdge(e_1_to_2,v1,v2,new_face,e_3_to_1,e_2_to_3);
		InitEdge(e_2_to_3,v2,v3,new_face,e_1_to_2,e_3_to_1);
		InitEdge(e_3_to_1,v3,v1,new_face,e_2_to_3,e_1_to_2);
	}

	printf("3D mesh has been created! \n");
}

void CModel::InitEdge(HE_edge * edge_to_init, HE_vert * vertex, HE_vert * vert_to_pair, HE_face * face, HE_edge * prev, HE_edge * next)
{
	edge_to_init->vert = vertex;
	edge_to_init->face = face;
	edge_to_init->prev = prev;
	edge_to_init->next = next;
	PairEdge(vert_to_pair, edge_to_init);
}

void CModel::PairEdge(HE_vert * vertex, HE_edge * edge)
{
	// Go to edges to pair list to check whether there is a edge waiting to be paired
	if (m_edgesToPair.find(vertex) == m_edgesToPair.end())
	{
		m_edgesToPair.insert(pair<HE_vert *, HE_edge *>(vertex, edge));
	}
	else
	{
		edge->pair = m_edgesToPair[vertex];
		m_edgesToPair[vertex]->pair = edge;
		map<HE_vert *, HE_edge *>::iterator itr = m_edgesToPair.find(vertex);
		if (itr != m_edgesToPair.end())
			m_edgesToPair.erase(itr);
	}
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