#ifndef __CHALF_EDGE_H__
#define __CHALF_EDGE_H__

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