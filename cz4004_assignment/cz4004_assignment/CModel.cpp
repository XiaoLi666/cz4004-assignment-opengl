#include <stdlib.h>
#include "GL\glut.h"
#include "Math.h"

#include "CModel.h"
#include "CMFileLoader.h"
#include "CUI.h"
#include "CUtilities.h"

using namespace CZ4004;
using namespace std;

CModel::CModel(const std::string & file_name)
	: m_minVertex(nullptr)
	, m_maxVertex(nullptr)
	, m_centerVertex(nullptr)
{
	CMFileLoader::GetInstance()->Load(file_name, m_vertices, m_facesLoadedData);
	printf("'%s' has been loaded! \n", file_name.c_str());

	// Create the 3D mesh by existing data
	Create();
}

CModel::~CModel()
{
	// Destructor

	// delete min and max vertex
	if (m_minVertex)
	{
		delete m_minVertex;
		m_minVertex = nullptr;
	}

	if (m_maxVertex)
	{
		delete m_maxVertex;
		m_maxVertex = nullptr;
	}

	// delete 
	// TODO:
}

void CModel::Create()
{
	printf("Start to create the 3D mesh ... \n");

	for (size_t i = 0; i < m_facesLoadedData.size(); ++ i)
	{
		HE_vert * v1 = m_vertices[m_facesLoadedData[i]->vertex1];
		HE_vert * v2 = m_vertices[m_facesLoadedData[i]->vertex2];
		HE_vert * v3 = m_vertices[m_facesLoadedData[i]->vertex3];

		CalMinMaxVertex(v1->coord);
		CalMinMaxVertex(v2->coord);
		CalMinMaxVertex(v3->coord);

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

		BuildPairEdgeStruct(e_1_to_2);
		BuildPairEdgeStruct(e_2_to_3);
		BuildPairEdgeStruct(e_3_to_1);

		new_face->edge = e_1_to_2;
		m_faces.push_back(new_face);
	}

	CalCenterVertex();
	m_boundingBox.Initialize(this->m_minVertex, this->m_maxVertex);

	FindPairedEdgesForAllEdges();
	CalNormalForAllVertices();

	printf("3D mesh has been created! \n");
}

void CModel::BuildPairEdgeStruct(HE_edge * edge)
{
	map<HE_vert *, deque<HE_edge *>>::iterator itr = m_edgesToPair.find(edge->vert);
	if (itr == m_edgesToPair.end())
	{
		deque<HE_edge *> new_deque;
		new_deque.push_back(edge);
		m_edgesToPair.insert(pair<HE_vert *, deque<HE_edge *>>(edge->vert, new_deque));
	}
	else
	{
		(*itr).second.push_back(edge);
	}
}

void CModel::FindPairedEdgesForAllEdges()
{
	for (size_t i = 0; i < m_edges.size(); ++ i)
	{
		HE_edge * edge = m_edges[i];
		if (!edge->pair)
		{
			deque<HE_edge *> d = m_edgesToPair[edge->next->vert];
			for (size_t j = 0; j < d.size(); ++ j)
			{
				if (d[j]->next->vert == edge->vert)
				{
					d[j]->pair = edge;
					edge->pair = d[j];
				}
			}
		}
	}
}

void CModel::InitEdge(HE_edge * edge_to_init, HE_vert * vertex, HE_vert * vert_to_pair, HE_face * face, HE_edge * prev, HE_edge * next)
{
	edge_to_init->vert = vertex;
	edge_to_init->face = face;
	edge_to_init->prev = prev;
	edge_to_init->next = next;
	// PairEdge(vertex, vert_to_pair, edge_to_init);
	m_edges.push_back(edge_to_init);
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
void CModel::CalMinMaxVertex(CVector3 * v)
{
	if (!m_minVertex)
		m_minVertex = new CVector3(v->x, v->y, v->z);
	if (!m_maxVertex)
		m_maxVertex = new CVector3(v->x, v->y, v->z);

	// Calculate the Min
	if (m_minVertex->x > v->x)
		m_minVertex->x = v->x;
	if (m_minVertex->y > v->y)
		m_minVertex->y = v->y;
	if (m_minVertex->z > v->z)
		m_minVertex->z = v->z;

	// Calculate the Max
	if (m_maxVertex->x < v->x)
		m_maxVertex->x = v->x;
	if (m_maxVertex->y < v->y)
		m_maxVertex->y = v->y;
	if (m_maxVertex->z < v->z)
		m_maxVertex->z = v->z;
}

void CModel::CalCenterVertex()
{
	if (!m_minVertex || !m_maxVertex)
	{
		printf("The min vertex and max vertex have not been initialized!");
		return;
	}

	if (m_centerVertex)
	{
		delete m_centerVertex;
		m_centerVertex = nullptr;
	}
	
	m_centerVertex = new CVector3(
		(m_minVertex->x + m_maxVertex->x) * 0.5f,
		(m_minVertex->y + m_maxVertex->y) * 0.5f,
		(m_minVertex->z + m_maxVertex->z) * 0.5f);

	m_centerVertex->Negative();

	for (unsigned int i = 0; i < m_vertices.size(); ++ i)
	{
		m_vertices[i]->coord->x += m_centerVertex->x;
		m_vertices[i]->coord->y += m_centerVertex->y;
		m_vertices[i]->coord->z += m_centerVertex->z;
	}
	m_minVertex->x += m_centerVertex->x;
	m_minVertex->y += m_centerVertex->y;
	m_minVertex->z += m_centerVertex->z;
	m_maxVertex->x += m_centerVertex->x;
	m_maxVertex->y += m_centerVertex->y;
	m_maxVertex->z += m_centerVertex->z;
}

void CModel::ClearCachedData()
{
}

void CModel::Render()
{
	CObject::Render();

	int rendering_mode = CUI::GetInstance()->GetRenderingMode();

	if (rendering_mode == 2)
	{
		glPushMatrix();
		//glTranslatef(m_centerVertex->x, m_centerVertex->y, m_centerVertex->z);
		for (size_t i = 0; i < m_vertices.size(); ++ i)
		{
			glBegin(GL_POINTS);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(m_vertices[i]->coord->x,m_vertices[i]->coord->y,m_vertices[i]->coord->z);
			glEnd();
		}
		
		if (CUI::GetInstance()->GetEnableBoundingBox()) m_boundingBox.Render();

		glPopMatrix();
	}
	else if (rendering_mode == 0 || rendering_mode == 1 || rendering_mode == 3)
	{
		glPushMatrix();
		//glTranslatef(m_centerVertex->x, m_centerVertex->y, m_centerVertex->z);
		glColor3f(0.0f, 0.0f, 0.0f);
		for (unsigned int i = 0; i < m_faces.size(); ++ i)
		{
			HE_edge * edge = m_faces[i]->edge;
			CVector3 * n1 = edge->vert->normal;
			CVector3 * n2 = edge->next->vert->normal;
			CVector3 * n3 = edge->next->next->vert->normal;
			glBegin(GL_TRIANGLES);
				glNormal3f(n1->x, n1->y, n1->z);
				glVertex3f(edge->vert->coord->x, edge->vert->coord->y, edge->vert->coord->z);
				glNormal3f(n2->x, n2->y, n2->z);
				edge = edge->next;
				glVertex3f(edge->vert->coord->x, edge->vert->coord->y, edge->vert->coord->z);
				glNormal3f(n3->x, n3->y, n3->z);
				edge = edge->next;
				glVertex3f(edge->vert->coord->x, edge->vert->coord->y, edge->vert->coord->z);
			glEnd();
		}

		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);

		if (CUI::GetInstance()->GetEnableBoundingBox()) m_boundingBox.Render();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPopMatrix();
	}
}

void CModel::Update()
{
	// TODO:
}

void CModel::SetRotation(float x_angle, float y_angle)
{
	delete m_minVertex; m_minVertex = nullptr;
	delete m_maxVertex; m_maxVertex = nullptr;

	float x_radian = CUtilities::Degree2Radian(x_angle);
	float y_radian = CUtilities::Degree2Radian(y_angle);

	CVector3 * cache_vertex = new CVector3();

	for (unsigned int i =  0; i < m_vertices.size(); ++ i)
	{
		// Rotate along the y axis
		cache_vertex->x = m_vertices[i]->coord->x * cos(x_radian) + m_vertices[i]->coord->z * sin(x_radian);
		cache_vertex->z = m_vertices[i]->coord->x * -sin(x_radian) + m_vertices[i]->coord->z * cos(x_radian);
		m_vertices[i]->coord->x = cache_vertex->x;
		m_vertices[i]->coord->z = cache_vertex->z;
		// Rotate along the x axis
		cache_vertex->y = m_vertices[i]->coord->y * cos(y_radian) + m_vertices[i]->coord->z * -sin(y_radian);
		cache_vertex->z = m_vertices[i]->coord->y * sin(y_radian) + m_vertices[i]->coord->z * cos(y_radian);
		m_vertices[i]->coord->y = cache_vertex->y;
		m_vertices[i]->coord->z = cache_vertex->z;
		CalMinMaxVertex(cache_vertex);
	}
	m_boundingBox.Initialize(this->m_minVertex, this->m_maxVertex);

	delete cache_vertex;
}