#ifndef GLEXAMINER_H
#define GLEXAMINER_H

#include <OpenMesh/Core/Geometry/VectorT.hh>
class QMouseEvent;
class QWheelEvent;

class GLExaminer
{
public:
    GLExaminer();
    virtual ~GLExaminer();

    void  setScene(const OpenMesh::Vec3f &center, float radius);
    void  viewAll();

    virtual void draw() = 0;
    virtual void init();
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void wheelEvent(QWheelEvent*);
    virtual void reshape(int w, int h);

protected:

    // updates projection matrix
    void updateProjectionMatrix();
    // translate the scene and update modelview matrix
    void translate(const OpenMesh::Vec3f& trans);
    // rotate the scene (around its center) and update modelview matrix
    void rotate(const OpenMesh::Vec3f& axis, float angle);

    // virtual trackball: map 2D screen point to unit sphere
    bool mapToSphere(const OpenMesh::Vec2i &point, OpenMesh::Vec3f &result);

    // mouse processing functions
    void rotation(int x, int y);
    void translation(int x, int y);
    void zoom(float x);

protected:
    int  m_width, m_height;

    // scene position and dimension
    OpenMesh::Vec3f    m_center;
    float    m_radius;

    // projection parameters
    float    m_near, m_far, m_fovy;

    // OpenGL matrices
    double   m_projectionMatrix[16],
    m_modelviewMatrix[16];

    // trackball helpers
    OpenMesh::Vec2i    m_lastPoint2D;
    OpenMesh::Vec3f    m_lastPoint3D;
    bool     m_lastPointOk;
    bool     m_leftButtonDown, m_rightButtonDown;
    int      m_modifiers;
};

#endif // GLEXAMINER_H
