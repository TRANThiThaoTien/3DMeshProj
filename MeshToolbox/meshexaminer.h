#ifndef MESHEXAMINER_H
#define MESHEXAMINER_H

#include "glexaminer.h"
#include "mesh.h"

class MeshExaminer : public GLExaminer
{
public:
    MeshExaminer();
    virtual ~MeshExaminer();

    // draw the scene
    virtual void draw();

    void resetMesh(const TriMesh &mesh, bool needNormalize);
    void updateMesh(const TriMesh &mesh);
    void setDrawPointsStatus(bool value){
        m_drawPointsStatus = value;
    }
    void setDrawEdgesStatus(bool value){
        m_drawEdgesStatus = value;
    }
    void setDrawFacesStatus(bool value){
        m_drawFacesStatus = value;
    }

protected:
    TriMesh m_meshShow;

    bool m_drawPointsStatus;
    bool m_drawEdgesStatus;
    bool m_drawFacesStatus;


    // compute the bounding box of a mesh
    bool meshBoundingBox(TriMesh::Point &minCoord, TriMesh::Point &maxCoord);
};

#endif // MESHEXAMINER_H
