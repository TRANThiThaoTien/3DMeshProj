#ifndef GLWRAPPER_H
#define GLWRAPPER_H

#include <QtOpenGL>
#include <OpenMesh/Core/Geometry/VectorT.hh>

// Mac OS X
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>

// Windows
#elif _WIN32
#  include <stdlib.h>
#  include <GL/GL.h>
#  include <GL/GLU.h>

// Unix
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#endif

namespace GL {
//=============================================================================


//-------------------------------------------------------------------- glVertex

/// Wrapper: glVertex for OpenMesh::Vec2i
inline void glVertex(const OpenMesh::Vec2i& v)  { glVertex2i(v[0], v[1]); }
/// Wrapper: glVertex for OpenMesh::Vec2f
inline void glVertex(const OpenMesh::Vec2f& v)  { glVertex2fv(v.data()); }
/// Wrapper: glVertex for OpenMesh::Vec2d
inline void glVertex(const OpenMesh::Vec2d& v)  { glVertex2dv(v.data()); }

/// Wrapper: glVertex for OpenMesh::Vec3f
inline void glVertex(const OpenMesh::Vec3f& v)  { glVertex3fv(v.data()); }
/// Wrapper: glVertex for OpenMesh::Vec3d
inline void glVertex(const OpenMesh::Vec3d& v)  { glVertex3dv(v.data()); }

/// Wrapper: glVertex for OpenMesh::Vec4f
inline void glVertex(const OpenMesh::Vec4f& v)  { glVertex4fv(v.data()); }
/// Wrapper: glVertex for OpenMesh::Vec4d
inline void glVertex(const OpenMesh::Vec4d& v)  { glVertex4dv(v.data()); }



//------------------------------------------------------------------- glTexCoord

/// Wrapper: glTexCoord for 1D float
inline void glTexCoord(float t) { glTexCoord1f(t); }
/// Wrapper: glTexCoord for 1D double
inline void glTexCoord(double t) { glTexCoord1d(t); }

/// Wrapper: glTexCoord for OpenMesh::Vec2f
inline void glTexCoord(const OpenMesh::Vec2f& t) { glTexCoord2fv(t.data()); }
/// Wrapper: glTexCoord for OpenMesh::Vec2d
inline void glTexCoord(const OpenMesh::Vec2d& t) { glTexCoord2dv(t.data()); }

/// Wrapper: glTexCoord for OpenMesh::Vec3f
inline void glTexCoord(const OpenMesh::Vec3f& t) { glTexCoord3fv(t.data()); }
/// Wrapper: glTexCoord for OpenMesh::Vec3d
inline void glTexCoord(const OpenMesh::Vec3d& t) { glTexCoord3dv(t.data()); }

/// Wrapper: glTexCoord for OpenMesh::Vec4f
inline void glTexCoord(const OpenMesh::Vec4f& t) { glTexCoord4fv(t.data()); }
/// Wrapper: glTexCoord for OpenMesh::Vec4d
inline void glTexCoord(const OpenMesh::Vec4d& t) { glTexCoord4dv(t.data()); }



//--------------------------------------------------------------------- glNormal

/// Wrapper: glNormal for OpenMesh::Vec3f
inline void glNormal(const OpenMesh::Vec3f& n)  { glNormal3fv(n.data()); }
/// Wrapper: glNormal for OpenMesh::Vec3d
inline void glNormal(const OpenMesh::Vec3d& n)  { glNormal3dv(n.data()); }



//---------------------------------------------------------------------- glColor

/// Wrapper: glColor for OpenMesh::Vec3f
inline void glColor(const OpenMesh::Vec3f&  v)  { glColor3fv(v.data()); }
/// Wrapper: glColor for OpenMesh::Vec3uc
inline void glColor(const OpenMesh::Vec3uc& v)  { glColor3ubv(v.data()); }

/// Wrapper: glColor for OpenMesh::Vec4f
inline void glColor(const OpenMesh::Vec4f&  v)  { glColor4fv(v.data()); }
/// Wrapper: glColor for OpenMesh::Vec4uc
inline void glColor(const OpenMesh::Vec4uc&  v) { glColor4ubv(v.data()); }



//-------------------------------------------------------------- glVertexPointer

/// Wrapper: glVertexPointer for OpenMesh::Vec2f
inline void glVertexPointer(const OpenMesh::Vec2f* p)
{ ::glVertexPointer(2, GL_FLOAT, 0, p); }
/// Wrapper: glVertexPointer for OpenMesh::Vec2d
inline void glVertexPointer(const OpenMesh::Vec2d* p)
{ ::glVertexPointer(2, GL_DOUBLE, 0, p); }

/// Wrapper: glVertexPointer for OpenMesh::Vec3f
inline void glVertexPointer(const OpenMesh::Vec3f* p)
{ ::glVertexPointer(3, GL_FLOAT, 0, p); }
/// Wrapper: glVertexPointer for OpenMesh::Vec3d
inline void glVertexPointer(const OpenMesh::Vec3d* p)
{ ::glVertexPointer(3, GL_DOUBLE, 0, p); }

/// Wrapper: glVertexPointer for OpenMesh::Vec4f
inline void glVertexPointer(const OpenMesh::Vec4f* p)
{ ::glVertexPointer(4, GL_FLOAT, 0, p); }
/// Wrapper: glVertexPointer for OpenMesh::Vec4d
inline void glVertexPointer(const OpenMesh::Vec4d* p)
{ ::glVertexPointer(4, GL_DOUBLE, 0, p); }

/// original method
inline void glVertexPointer(GLint n, GLenum t, GLsizei s, const GLvoid *p)
{ ::glVertexPointer(n, t, s, p); }



//-------------------------------------------------------------- glNormalPointer

/// Wrapper: glNormalPointer for OpenMesh::Vec3f
inline void glNormalPointer(const OpenMesh::Vec3f* p)
{ ::glNormalPointer(GL_FLOAT, 0, p); }
/// Wrapper: glNormalPointer for OpenMesh::Vec3d
inline void glNormalPointer(const OpenMesh::Vec3d* p)
{ ::glNormalPointer(GL_DOUBLE, 0, p); }

/// original method
inline void glNormalPointer(GLenum t, GLsizei s, const GLvoid *p)
{ ::glNormalPointer(t, s, p); }



//--------------------------------------------------------------- glColorPointer

/// Wrapper: glColorPointer for OpenMesh::Vec3uc
inline void glColorPointer(const OpenMesh::Vec3uc* p)
{ ::glColorPointer(3, GL_UNSIGNED_BYTE, 0, p); }
/// Wrapper: glColorPointer for OpenMesh::Vec3f
inline void glColorPointer(const OpenMesh::Vec3f* p)
{ ::glColorPointer(3, GL_FLOAT, 0, p); }

/// Wrapper: glColorPointer for OpenMesh::Vec4uc
inline void glColorPointer(const OpenMesh::Vec4uc* p)
{ ::glColorPointer(4, GL_UNSIGNED_BYTE, 0, p); }
/// Wrapper: glColorPointer for OpenMesh::Vec4f
inline void glColorPointer(const OpenMesh::Vec4f* p)
{ ::glColorPointer(4, GL_FLOAT, 0, p); }

/// original method
inline void glColorPointer(GLint n, GLenum t, GLsizei s, const GLvoid *p)
{ ::glColorPointer(n, t, s, p); }



//------------------------------------------------------------ glTexCoordPointer

/// Wrapper: glTexCoordPointer for float
inline void glTexCoordPointer(const float* p)
{ ::glTexCoordPointer(1, GL_FLOAT, 0, p); }
/// Wrapper: glTexCoordPointer for OpenMesh::Vec2d
inline void glTexCoordPointer(const double* p)
{ ::glTexCoordPointer(1, GL_DOUBLE, 0, p); }

/// Wrapper: glTexCoordPointer for OpenMesh::Vec2f
inline void glTexCoordPointer(const OpenMesh::Vec2f* p)
{ ::glTexCoordPointer(2, GL_FLOAT, 0, p); }
/// Wrapper: glTexCoordPointer for OpenMesh::Vec2d
inline void glTexCoordPointer(const OpenMesh::Vec2d* p)
{ ::glTexCoordPointer(2, GL_DOUBLE, 0, p); }

/// Wrapper: glTexCoordPointer for OpenMesh::Vec3f
inline void glTexCoordPointer(const OpenMesh::Vec3f* p)
{ ::glTexCoordPointer(3, GL_FLOAT, 0, p); }
/// Wrapper: glTexCoordPointer for OpenMesh::Vec3d
inline void glTexCoordPointer(const OpenMesh::Vec3d* p)
{ ::glTexCoordPointer(3, GL_DOUBLE, 0, p); }

/// Wrapper: glTexCoordPointer for OpenMesh::Vec4f
inline void glTexCoordPointer(const OpenMesh::Vec4f* p)
{ ::glTexCoordPointer(4, GL_FLOAT, 0, p); }
/// Wrapper: glTexCoordPointer for OpenMesh::Vec4d
inline void glTexCoordPointer(const OpenMesh::Vec4d* p)
{ ::glTexCoordPointer(4, GL_DOUBLE, 0, p); }

/// original method
inline void glTexCoordPointer(GLint n, GLenum t, GLsizei s, const GLvoid *p)
{ ::glTexCoordPointer(n, t, s, p); }



//-----------------------------------------------------------------------------


/** Nice wrapper that outputs all current OpenGL errors to std::cerr.
    If no error is present nothing is printed.
**/
inline void glCheckErrors()
{
//  GLenum error;
//  while ((error = glGetError()) != GLnO_ERROR)
//  {
//    std::cerr << "GL error: " << gluErrorString(error) << std::endl;
//  }
}


//=============================================================================
}

#endif // GLWRAPPER_H

