#include "meshexaminer.h"
#include "glwrapper.h"
#include <QFileDialog>
#include <QString>

MeshExaminer::MeshExaminer():m_drawPointsStatus(false), m_drawEdgesStatus(true), m_drawFacesStatus(false)
{

}

MeshExaminer::~MeshExaminer()
{

}

void MeshExaminer::resetMesh(const TriMesh &mesh, bool needNormalize)
{
    updateMesh(mesh);

    if(needNormalize){
        TriMesh::Point maxCoord, minCoord;
        if(meshBoundingBox(minCoord, maxCoord)){
            setScene( (OpenMesh::Vec3f)((minCoord + maxCoord)*0.5), 0.5*(maxCoord - minCoord).norm());
        }
        else{
            setScene( OpenMesh::Vec3f(0, 0, 0), 1);
        }
    }
}

void MeshExaminer::updateMesh(const TriMesh &mesh)
{
    m_meshShow = mesh;
    m_meshShow.request_face_normals();
    m_meshShow.request_vertex_normals();
    m_meshShow.update_normals();
}

void MeshExaminer::draw()
{
    if(m_drawPointsStatus)
    {
        glBegin(GL_POINTS);
        for (TriMesh::VertexIter v_it = m_meshShow.vertices_begin();
             v_it != m_meshShow.vertices_end(); v_it++)
        {
            TriMesh::Normal normal = m_meshShow.normal(*v_it);
            TriMesh::Point  point = m_meshShow.point(*v_it);
            TriMesh::Color  color = m_meshShow.color(*v_it);
            glColor4f(color[0],color[1],color[2],1);
            glNormal3f(normal[0], normal[1], normal[2]);
            glVertex3f(point[0], point[1], point[2]);
        }
        glEnd();
    }
    if(m_drawEdgesStatus)
    {
        for(TriMesh::FaceIter f_it = m_meshShow.faces_begin();
                    f_it != m_meshShow.faces_end(); f_it++)
                {
                    glBegin(GL_LINE_LOOP);
                    for(TriMesh::FaceHalfedgeIter fh_it = m_meshShow.fh_iter(*f_it);
                        fh_it.is_valid(); fh_it++)
                    {
                        TriMesh::VertexHandle toV = m_meshShow.to_vertex_handle(*fh_it);
                        TriMesh::Normal normal = m_meshShow.normal(toV);
                        TriMesh::Point point = m_meshShow.point(toV);
                        glColor3f(0.3f, 0.3f, 0.3f);
                        glNormal3f(normal[0], normal[1], normal[2]);
                        glVertex3f(point[0], point[1], point[2]);
                    }
                    glEnd();
                }
    }
    if(m_drawFacesStatus)
    {

    }
}

bool MeshExaminer::meshBoundingBox(TriMesh::Point &minCoord, TriMesh::Point &maxCoord)
{
    if(m_meshShow.n_vertices() == 0){
        return false;
    }

    TriMesh::ConstVertexIter cv_it = m_meshShow.vertices_begin(), cv_end(m_meshShow.vertices_end());
    minCoord = m_meshShow.point(*cv_it);
    maxCoord = minCoord;

    for( ++ cv_it ; cv_it != cv_end; ++ cv_it){
        minCoord.minimize(m_meshShow.point(*cv_it));
        maxCoord.maximize(m_meshShow.point(*cv_it));
    }

    return true;
}
