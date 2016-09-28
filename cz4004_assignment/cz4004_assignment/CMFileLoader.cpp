#include <iostream>
#include <fstream>
#include "CMFileLoader.h"
#include "CUtilities.h"

using namespace CZ4004;
using namespace std;

CMFileLoader * CMFileLoader::m_instance = 0;

void CMFileLoader::Load(const std::string & file_name)
{
	// FILE *f;
	// f = std::fopen(filePath,"r");

	string name;
	ifstream myfile;
	myfile.open((CUtilities::directory+file_name).c_str());
	
	if (myfile.is_open())
	{
		printf("The file %s is being loaded... \n", file_name.c_str());

		string s;
		int vertex_index;
		float vertex_x;
		float vertex_y;
		float vertex_z;

		while (myfile >> s)
		{
			if (s == "Vertex")
			{
				myfile >> s; // index
				
				myfile >> s; // x
				
				myfile >> s; // y
				
				myfile >> s; // z
			}
			else if (s == "Face")
			{
				myfile >> s; // index
				
				myfile >> s; // x
				
				myfile >> s; // y
				
				myfile >> s; // z
			}
		}

		//while (getline(myfile, s))
		//{
		//	if (s[0] == '#')
		//		continue;
		//	else if (s[0] == 'V')
		//	{
		//		// fscanf(myfile,"Vertex %d %f %f %f \n", &vertex_index, &vertex_x, &vertex_y, &vertex_z) == 7
		//	}
		//		// TODO: initialize for vertex
		//	// else if (s[0] == 'F')
		//		// TODO: initialize for face

		//	printf("The s is            %c \n", s[0]);
		//}

		printf("Loading finished! \n");
	}
	
	myfile.close();
}