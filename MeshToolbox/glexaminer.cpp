#include "glexaminer.h"
#include "glwrapper.h"
#include <math.h>
#include <QMouseEvent>
#include <QWheelEvent>
#include <iostream>

GLExaminer::GLExaminer()
    :m_lastPointOk(false), m_leftButtonDown(false), m_rightButtonDown(false)
{}


GLExaminer::~GLExaminer()
{}

void GLExaminer::init()
{
  // OpenGL state
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//  glClearColor(0.6f, 0.6f, 0.5f, 0.0f);
  glDisable( GL_DITHER );
  glEnable( GL_DEPTH_TEST );
  glEnable(GL_DOUBLEBUFFER);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_LINE_SMOOTH);

  // some performance settings
  // glEnable( GL_CULL_FACE );
//  glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE );
//  glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE );


  // material
//  GLfloat mat_a[] = {0.2, 0.2, 0.2, 1.0};
//  GLfloat mat_d[] = {0.4, 0.4, 0.4, 1.0};
//  GLfloat mat_s[] = {0.8, 0.8, 0.8, 1.0};
//  GLfloat shine[] = {128.0};
//  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat_a);
//  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat_d);
//  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_s);
//  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);


  // lighting
//  glLoadIdentity();

//  GLfloat pos1[] = { 0.1, 0.1, -0.02, 0.0};
//  GLfloat pos2[] = {-0.1, 0.1, -0.02, 0.0};
//  GLfloat pos3[] = { 0.0, 0.0, 0.1, 0.0};
//  GLfloat col1[] = {.05, .05, .6, 1.0};
//  GLfloat col2[] = {.6, .05, .05, 1.0};
//  GLfloat col3[] = {1.0, 1.0, 1.0, 1.0};

//  glEnable(GL_LIGHTING);
//  glEnable(GL_LIGHT0);
//  glLightfv(GL_LIGHT0,GL_POSITION, pos1);
//  glLightfv(GL_LIGHT0,GL_DIFFUSE,  col1);
//  glLightfv(GL_LIGHT0,GL_SPECULAR, col1);

//  glEnable(GL_LIGHT1);
//  glLightfv(GL_LIGHT1,GL_POSITION, pos2);
//  glLightfv(GL_LIGHT1,GL_DIFFUSE,  col2);
//  glLightfv(GL_LIGHT1,GL_SPECULAR, col2);

//  glEnable(GL_LIGHT2);
//  glLightfv(GL_LIGHT2,GL_POSITION, pos3);
//  glLightfv(GL_LIGHT2,GL_DIFFUSE,  col3);
//  glLightfv(GL_LIGHT2,GL_SPECULAR, col3);

  // add
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);

  // scene pos and size
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glGetDoublev(GL_MODELVIEW_MATRIX, m_modelviewMatrix);
  setScene(OpenMesh::Vec3f(0.0, 0.0, 0.0), 1.0);

  // projection
  m_near = 0.0001f;
  m_far  = 1000.0f;
  m_fovy = 45.0f;
}

void GLExaminer::reshape(int w, int h)
{
  m_width  = w;
  m_height = h;
  glViewport(0, 0, w, h);
  updateProjectionMatrix();
}

void GLExaminer::updateProjectionMatrix()
{
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective(m_fovy, (GLfloat)m_width/(GLfloat)m_height, m_near, m_far);
  glGetDoublev( GL_PROJECTION_MATRIX, m_projectionMatrix);
  glMatrixMode( GL_MODELVIEW );
}

void GLExaminer::setScene(const OpenMesh::Vec3f& cog, float radius )
{
  m_center = cog;
  m_radius = radius;

  m_near  = 0.01 * m_radius;
  m_far   = 10.0 * m_radius;
  updateProjectionMatrix();

  viewAll();
}
void GLExaminer::viewAll()
{
  translate( OpenMesh::Vec3f( -(m_modelviewMatrix[0]*m_center[0] +
              m_modelviewMatrix[4]*m_center[1] +
              m_modelviewMatrix[8]*m_center[2] +
              m_modelviewMatrix[12]),
            -(m_modelviewMatrix[1]*m_center[0] +
              m_modelviewMatrix[5]*m_center[1] +
              m_modelviewMatrix[9]*m_center[2] +
              m_modelviewMatrix[13]),
            -(m_modelviewMatrix[2]*m_center[0] +
              m_modelviewMatrix[6]*m_center[1] +
              m_modelviewMatrix[10]*m_center[2] +
              m_modelviewMatrix[14] +
              3.0*m_radius) ) );
}

bool GLExaminer::mapToSphere(const OpenMesh::Vec2i& v2D, OpenMesh::Vec3f& v3D )
{
  if ( (v2D[0] >= 0) && (v2D[0] <= m_width) &&
       (v2D[1] >= 0) && (v2D[1] <= m_height) )
  {
    double x  = (double)(v2D[0] - 0.5*m_width)  / (double)m_width;
    double y  = (double)(0.5*m_height - v2D[1]) / (double)m_height;
    double sinx         = sin(M_PI * x * 0.5);
    double siny         = sin(M_PI * y * 0.5);
    double sinx2siny2   = sinx * sinx + siny * siny;

    v3D[0] = sinx;
    v3D[1] = siny;
    v3D[2] = sinx2siny2 < 1.0 ? sqrt(1.0 - sinx2siny2) : 0.0;

    return true;
  }
  else
    return false;
}

void GLExaminer::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton || event->button() == Qt::RightButton){
        m_lastPoint2D = OpenMesh::Vec2i(event->x(), event->y());
        m_lastPointOk = mapToSphere( m_lastPoint2D, m_lastPoint3D );

        if( event->button() == Qt::LeftButton ){
            m_leftButtonDown = true;
        }
        if(event->button() == Qt::RightButton){
            m_rightButtonDown = true;
        }
    }
}

void GLExaminer::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton || event->button() == Qt::RightButton){
        m_lastPointOk = false;

        if( event->button() == Qt::LeftButton ){
            m_leftButtonDown = false;
        }
        if(event->button() == Qt::RightButton){
            m_rightButtonDown = false;
        }
    }
}

void GLExaminer::wheelEvent(QWheelEvent *event)
{
    float dx = event->delta() * 0.5;
    zoom(dx);
}

void GLExaminer::mouseMoveEvent(QMouseEvent* event)
{
    if(event->buttons() == Qt::LeftButton){
        rotation(event->x(), event->y());
    }
    else if(event->buttons() == Qt::RightButton){
        translation(event->x(), event->y());
    }

    if(event->buttons() == Qt::LeftButton || event->buttons() == Qt::RightButton){
        m_lastPoint2D = OpenMesh::Vec2i(event->x(), event->y());
        m_lastPointOk = mapToSphere(m_lastPoint2D, m_lastPoint3D);
    }
}

void GLExaminer::rotation(int x, int y)
{
  if (m_lastPointOk)
  {
    OpenMesh::Vec2i  newPoint2D;
    OpenMesh::Vec3f  newPoint3D;
    bool   newPointOK;

    newPoint2D = OpenMesh::Vec2i(x, y);
    newPointOK = mapToSphere(newPoint2D, newPoint3D);

    if (newPointOK)
    {
      OpenMesh::Vec3f axis      = OpenMesh::cross(m_lastPoint3D, newPoint3D);
      float cos_angle = OpenMesh::dot(m_lastPoint3D, newPoint3D);

      if (fabs(cos_angle) < 1.0)
      {
        float angle = 2.0*acos(cos_angle) * 180.0 / M_PI;
        rotate(axis, angle);
      }
    }
  }
}

void GLExaminer::translation(int x, int y)
{
  float dx = x - m_lastPoint2D[0];
  float dy = y - m_lastPoint2D[1];

  float z = - ((m_modelviewMatrix[ 2]*m_center[0] +
        m_modelviewMatrix[ 6]*m_center[1] +
        m_modelviewMatrix[10]*m_center[2] +
        m_modelviewMatrix[14]) /
           (m_modelviewMatrix[ 3]*m_center[0] +
        m_modelviewMatrix[ 7]*m_center[1] +
        m_modelviewMatrix[11]*m_center[2] +
        m_modelviewMatrix[15]));

  float aspect = (float)m_width / (float)m_width;
  float up     = tan(m_fovy/2.0f*M_PI/180.f) * m_near;
  float right  = aspect*up;

  translate(OpenMesh::Vec3f(2.0*dx/m_width*right/m_near*z,
          -2.0*dy/m_height*up/m_near*z,
          0.0f));
}

void GLExaminer::zoom(float x)
{
  float h  = m_height;
  translate(OpenMesh::Vec3f(0.0, 0.0, m_radius * x * 3.0 / h));
}

void GLExaminer::translate(const OpenMesh::Vec3f& trans )
{
  glLoadIdentity();
  glTranslated( trans[0], trans[1], trans[2] );
  glMultMatrixd( m_modelviewMatrix );
  glGetDoublev( GL_MODELVIEW_MATRIX, m_modelviewMatrix);
}

void GLExaminer::rotate(const OpenMesh::Vec3f& axis, float angle )
{
  OpenMesh::Vec3f t( m_modelviewMatrix[0]*m_center[0] +
       m_modelviewMatrix[4]*m_center[1] +
       m_modelviewMatrix[8]*m_center[2] +
       m_modelviewMatrix[12],
       m_modelviewMatrix[1]*m_center[0] +
       m_modelviewMatrix[5]*m_center[1] +
       m_modelviewMatrix[9]*m_center[2] +
       m_modelviewMatrix[13],
       m_modelviewMatrix[2]*m_center[0] +
       m_modelviewMatrix[6]*m_center[1] +
       m_modelviewMatrix[10]*m_center[2] +
       m_modelviewMatrix[14] );

  glLoadIdentity();
  glTranslatef(t[0], t[1], t[2]);
  glRotated( angle, axis[0], axis[1], axis[2]);
  glTranslatef(-t[0], -t[1], -t[2]);
  glMultMatrixd(m_modelviewMatrix);
  glGetDoublev(GL_MODELVIEW_MATRIX, m_modelviewMatrix);
}
