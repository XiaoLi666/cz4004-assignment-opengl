#include "CModel.h"
#include "CMFileLoader.h"

using namespace CZ4004;

CModel::CModel(const std::string & file_name)
{
	CMFileLoader::GetInstance()->Load(file_name, m_vertices, m_facesLoadedData);
	printf("'%s' has been loaded! \n", file_name.c_str());
}

void CModel::Create()
{
}

void CModel::Render()
{
}

void CModel::Update()
{
}