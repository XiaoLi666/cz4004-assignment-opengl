#ifndef __CMFILELOADER_H__
#define __CMFILELOADER_H__

#include <string>
#include <vector>
#include "CMeshDataStruct.h"

namespace CZ4004
{
	// singleton class
	class CMFileLoader
	{
	private:
		static CMFileLoader * m_instance;

	private:
		CMFileLoader() {}

	public:
		~CMFileLoader() {}

		static CMFileLoader * GetInstance()
		{
			if (!m_instance)
				m_instance = new CMFileLoader();
			return m_instance;
		}

		void Load(const std::string & file_name, 
			std::vector<HE_vert> & vertices, 
			std::vector<Face_Loaded_Data> & faces_loaded_data);
	};
}

#endif // __CMFILELOADER_H__