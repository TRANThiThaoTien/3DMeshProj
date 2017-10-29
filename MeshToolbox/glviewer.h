#ifndef GLVIEWER_H
#define GLVIEWER_H

#include <QWidget>
#include <QtOpenGL>
#include <QColorDialog>
#include "meshexaminer.h"


class GLViewer : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLViewer(QWidget *parent = 0);
    ~GLViewer();

    void updateMesh(const TriMesh &_mesh);
    void resetMesh(const TriMesh &_mesh, bool _needNormalize = false);

    MeshExaminer* getExaminer(){
        return m_examiner;
    }

signals:

public slots:
    void pointsDisplay(bool value);
    void edgesDisplay(bool value);
    void facesDisplay(bool value);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

    void initializeGL();
    void resizeGL(int _w, int _h);
    void paintGL();

private:
    MeshExaminer *m_examiner;
};

#endif // GLVIEWER_H
