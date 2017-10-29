#include "glviewer.h"
#include <QFileDialog>
#include <QColorDialog>

GLViewer::GLViewer(QWidget *parent) : QGLWidget(parent)
{
    m_examiner = new MeshExaminer();
}
GLViewer::~GLViewer()
{
    if(m_examiner) delete m_examiner;
    m_examiner = NULL;
}
void GLViewer::pointsDisplay(bool value)
{
    m_examiner->setDrawPointsStatus(value);
    this->updateGL();
}
void GLViewer::edgesDisplay(bool value)
{
    m_examiner->setDrawEdgesStatus(value);
    this->updateGL();
}
void GLViewer::facesDisplay(bool value)
{
    m_examiner->setDrawFacesStatus(value);
    this->updateGL();
}

void GLViewer::mousePressEvent(QMouseEvent *event)
{
    m_examiner->mousePressEvent(event);
}

void GLViewer::mouseReleaseEvent(QMouseEvent *event)
{
    m_examiner->mouseReleaseEvent(event);
}

void GLViewer::mouseMoveEvent(QMouseEvent *event)
{
    m_examiner->mouseMoveEvent(event);
    this->updateGL();
}

void GLViewer::wheelEvent(QWheelEvent *event)
{
    m_examiner->wheelEvent(event);
    this->updateGL();
}

void GLViewer::mouseDoubleClickEvent(QMouseEvent*)
{
}

void GLViewer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_examiner->draw();
}

void GLViewer::initializeGL()
{
    m_examiner->init();
}

void GLViewer::resizeGL(int w, int h)
{
    m_examiner->reshape(w, h);
}
void GLViewer::updateMesh(const TriMesh &mesh)
{
    m_examiner->updateMesh(mesh);
}

void GLViewer::resetMesh(const TriMesh &mesh, bool needNormalize)
{
    m_examiner->resetMesh(mesh, needNormalize);
}
