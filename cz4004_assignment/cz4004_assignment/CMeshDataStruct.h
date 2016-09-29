#ifndef __CHALF_EDGE_H__
#define __CHALF_EDGE_H__

#include "CVector3.h"

namespace CZ4004
{
	struct HE_vert;
	struct HE_face;

	/*----------------------------------------*/
	/*--------HALF EDGE DATA STRUCTURE--------*/
	/*----------------------------------------*/
	struct HE_edge
	{
		HE_vert * vert;
		HE_edge * pair;
		HE_face * face;
		HE_edge * prev;
		HE_edge * next;
		HE_edge():vert(nullptr),pair(nullptr),face(nullptr),prev(nullptr),next(nullptr){};
	};

	struct HE_vert
	{
		CVector3 * coord;
		CVector3 * normal;
		HE_edge * edge;
		HE_vert():coord(nullptr),normal(nullptr),edge(nullptr){}
	};

	struct HE_face
	{
		HE_edge * edge;
		CVector3 * normal;
		HE_face():edge(nullptr),normal(nullptr){}
	};

	/*----------------------------------------*/
	/*-------------OTHER STRUCTURE------------*/
	/*----------------------------------------*/
	struct Face_Loaded_Data
	{
		int vertex1;
		int vertex2;
		int vertex3;
	};
}

#endif // __CHALF_EDGE_H__