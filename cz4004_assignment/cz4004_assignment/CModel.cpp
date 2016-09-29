#include <stdlib.h>
#include "glut.h"

#include "CModel.h"
#include "CMFileLoader.h"

using namespace CZ4004;
using namespace std;

CModel::CModel(const std::string & file_name)
	: m_minVertex(nullptr), m_maxVertex(nullptr)
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

		CalMinMaxVertex(v1);
		CalMinMaxVertex(v2);
		CalMinMaxVertex(v3);

		HE_face * new_face = new HE_face();
		CalNormalForFace(new_face, v1->coord, v2->coord, v3->coord);

		HE_edge * e_1_to_2 = new HE_edge();
		HE_edge * e_2_to_3 = new HE_edge();
		HE_edge * e_3_to_1 = new HE_edge();

		v1->edge = e_1_to_2;
		v2->edge = e_2_to_3;
		v3->edge = e_3_to_1;

		InitEdge(e_1_to_2,v1,v2,new_face,e_3_to_1,e_2_to_3);
		InitEdge(e_2_to_3,v2,v3,new_face,e_1_to_2,e_3_to_1);
		InitEdge(e_3_to_1,v3,v1,new_face,e_2_to_3,e_1_to_2);

		new_face->edge = e_1_to_2;
		m_faces.push_back(new_face);
	}

	CalNormalForAllVertices();

	printf("3D mesh has been created! \n");
}

void CModel::InitEdge(HE_edge * edge_to_init, HE_vert * vertex, HE_vert * vert_to_pair, HE_face * face, HE_edge * prev, HE_edge * next)
{
	edge_to_init->vert = vertex;
	edge_to_init->face = face;
	edge_to_init->prev = prev;
	edge_to_init->next = next;
	PairEdge(vertex, vert_to_pair, edge_to_init);
	m_edges.push_back(edge_to_init);
}

void CModel::PairEdge(HE_vert * start, HE_vert * end, HE_edge * edge)
{
	if (m_edgesToPair.find(end) == m_edgesToPair.end())
	{
		m_edgesToPair.insert(pair<HE_vert *, HE_edge *>(start, edge));
	}
	else
	{
		edge->pair = m_edgesToPair[end];
		m_edgesToPair[end]->pair = edge;
		map<HE_vert *, HE_edge *>::iterator itr = m_edgesToPair.find(end);
		if (itr != m_edgesToPair.end())
			m_edgesToPair.erase(itr);
	}
}

void CModel::CalNormalForFace(HE_face * face, CVector3 * v1, CVector3 * v2, CVector3 * v3)
{
	CVector3 * e1 = v2->Minus(v1);
	CVector3 * e2 = v3->Minus(v1);
	CVector3 * normal = e1->CrossProduct(e2);
	normal->Normalize();
	face->normal = normal;

	// Avoid memory leak
	delete e1;
	delete e2;
}

void CModel::CalNormalForAllVertices()
{
	for (size_t i = 0; i < m_vertices.size(); ++ i)
	{
		vector<HE_face *> adjacent_faces;
		HE_vert * vertex = m_vertices[i];
		HE_edge * original_edge = vertex->edge;
		HE_edge * current_edge = original_edge;
		do
		{
			HE_edge * pair_edge = current_edge->pair;
			if (!pair_edge)
				break;

			current_edge = pair_edge->next;
			adjacent_faces.push_back(current_edge->face);
		} while (current_edge != original_edge);

		CVector3 * sum_vector = new CVector3();
		for (size_t j = 0; j < adjacent_faces.size(); ++ j)
		{
			sum_vector->Plus(adjacent_faces[j]->normal);
		}
		sum_vector->Multiply(1.0f/adjacent_faces.size());
		sum_vector->Normalize();
		vertex->normal = sum_vector;

		adjacent_faces.clear();
	}
}

// TODO: This function is totally wrong, need to redo this function
void CModel::CalMinMaxVertex(HE_vert * v)
{
	if (!m_minVertex)
		m_minVertex = v;
	if (!m_maxVertex)
		m_maxVertex = v;
	else if (v->coord->x < m_minVertex->coord->x && v->coord->y < m_minVertex->coord->y && v->coord->z < m_minVertex->coord->z)
		m_minVertex = v;
	else if (v->coord->x > m_maxVertex->coord->x && v->coord->y > m_maxVertex->coord->y && v->coord->z > m_maxVertex->coord->z)
		m_maxVertex = v;
}

void CModel::ClearCachedData()
{
}

void CModel::Render()
{
	for (size_t i = 0; i < m_vertices.size(); ++ i)
	{
		//// glShadeModel(GL_SMOOTH);
		//glBegin(GL_TRIANGLES);
		//	// glColor3f();
		//	// glNormal3f();
		//	glVertex3f();
		//	glVertex3f();
		//	glVertex3f();
		//glEnd();

		glBegin(GL_POINTS);
		glVertex3f(m_vertices[i]->coord->x,m_vertices[i]->coord->y,m_vertices[i]->coord->z);
		glEnd();
	}
}

void CModel::Update()
{
	// TODO:
}