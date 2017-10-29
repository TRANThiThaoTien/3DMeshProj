#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "glviewer.h"

class GLViewer;
class DataManager;
class ioThread;

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void init();
    void createActions();
    void createMenus();
    void createStatusBar();
    void setActionStatus(bool value);

private slots:
    void importMesh();
    void clearMesh();

    void needToUpdateGL(bool value);

private:
    Ui::MainWindow *_ui;

private:
    QMenu   *m_menuFile;
    QMenu   *m_menuDisplay;
    QMenu   *m_menuHelp;

    QAction *m_actionImportMesh;
    QAction *m_actionClearMesh;

    QAction *m_actionPointsDisplay;
    QAction *m_actionEdgesDisplay;
    QAction *m_actionFacesDisplay;

    QToolBar *m_toolbarFile;
    QToolBar *m_toolbarOpenglInfo;
    QToolBar *m_toolbarMeshStatus;

    QLabel   *m_labelOperationInfo;

private:
    GLViewer    *m_openglViewer;
    DataManager *m_dataManager;
    ioThread    *m_ioThread;
};

#endif // MAINWINDOW_H
