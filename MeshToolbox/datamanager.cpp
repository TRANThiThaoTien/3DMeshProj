#include "datamanager.h"

DataManager::DataManager()
{
    m_mesh.request_vertex_colors();
}

bool DataManager::importMeshFromFile(std::string filename)
{
    if(!OpenMesh::IO::read_mesh(m_mesh, filename))
        return false;
    else
    {
        if (m_mesh.has_vertex_colors())
        {
            std::cout << "Mesh has colors" << std::endl;
        }else{
            std::cout << "Mesh no has colors" << std::endl;

        }
        return true;
    }
}
TriMesh DataManager::getMesh() {
    return m_mesh;
}
