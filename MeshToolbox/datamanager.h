#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "mesh.h"
#include <string>

class DataManager
{
public:
    DataManager();

public:
    bool importMeshFromFile(std::string filename);

    TriMesh getMesh() ;

    void setMesh(const TriMesh &mesh) {m_mesh = mesh;}

    void clearMesh() {
        TriMesh new_mesh;
        setMesh(new_mesh);
    }

private:
    TriMesh m_mesh;
};

#endif // DATAMANAGER_H
