#include <iostream>
#include <fstream>
#include "CMFileLoader.h"
#include "CUtilities.h"

using namespace CZ4004;
using namespace std;

CMFileLoader * CMFileLoader::m_instance = 0;

void CMFileLoader::Load(const std::string & file_name, 
	std::vector<HE_vert *> & vertices, 
	std::vector<Face_Loaded_Data *> & faces_loaded_data)
{
	string name;
	ifstream myfile;
	myfile.open((CUtilities::directory+file_name).c_str());
	
	if (myfile.is_open())
	{
		printf("'%s' is being loaded... \n", file_name.c_str());

		string type;

		int vertex_index;
		float vertex_x;
		float vertex_y;
		float vertex_z;

		int face_index;
		int vertex1;
		int vertex2;
		int vertex3;

		while (myfile >> type)
		{
			if (type == "Vertex")
			{
				myfile >> vertex_index; // index
				myfile >> vertex_x; // x
				myfile >> vertex_y; // y
				myfile >> vertex_z; // z

				HE_vert * new_vert = new HE_vert();
				new_vert->x = vertex_x;
				new_vert->y = vertex_y;
				new_vert->z = vertex_z;
				new_vert->edge = nullptr;
				vertices.push_back(new_vert);

#ifndef _DEBUG
				printf("Vertex Info: %d,%f,%f,%f \n", vertex_index, vertex_x, vertex_y, vertex_z);
#endif
			}
			else if (type == "Face")
			{
				myfile >> face_index; // index
				myfile >> vertex1; // v 1
				myfile >> vertex2; // v 2
				myfile >> vertex3; // v 3

				Face_Loaded_Data * new_face_loaded_data = new Face_Loaded_Data();
				new_face_loaded_data->vertex1 = vertex1-1;
				new_face_loaded_data->vertex2 = vertex2-1;
				new_face_loaded_data->vertex3 = vertex3-1;
				faces_loaded_data.push_back(new_face_loaded_data);

#ifndef _DEBUG
				printf("Face Info: %d,%d,%d,%d \n", face_index, vertex1, vertex2, vertex3);
#endif
			}
		}
	}
	
	myfile.close();
}