#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glviewer.h"
#include "datamanager.h"
#include "iothread.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    setWindowTitle("3D MeshToolbox");
    setGeometry(250, 50, 880, 660);
    init();
    createActions();
    createMenus();
    createStatusBar();

    QVBoxLayout *layout_left = new QVBoxLayout;
    layout_left->addStretch(2);
    QHBoxLayout *layout_main = new QHBoxLayout;
    layout_main->addLayout(layout_left);
    layout_main->addWidget(m_openglViewer);
    layout_main->setStretch(1,1);
    this->centralWidget()->setLayout(layout_main);
}

MainWindow::~MainWindow()
{
    {
        if(m_openglViewer != NULL)
            delete m_openglViewer;
        m_openglViewer = NULL;

        if(m_dataManager != NULL)
            delete m_dataManager;
        m_dataManager = NULL;

    }
}
void MainWindow::init(){
    m_openglViewer = new GLViewer(this);
    m_dataManager = new DataManager();
    m_ioThread = new ioThread(m_dataManager);
    m_ioThread->m_ioType = ioThread::kNon;
    connect(m_ioThread, SIGNAL(needToUpdateGL(bool)), this, SLOT(needToUpdateGL(bool)));

}
void MainWindow::createActions(){
    m_actionImportMesh = new QAction(this);
    m_actionImportMesh->setText("Import");
    m_actionImportMesh->setStatusTip("Import Mesh");
    connect(m_actionImportMesh, SIGNAL(triggered()), this, SLOT(importMesh()));

    m_actionClearMesh = new QAction(this);
    m_actionClearMesh->setText("Clear");
    m_actionClearMesh->setStatusTip("Clear Mesh.");
    connect(m_actionClearMesh, SIGNAL(triggered()), this, SLOT(clearMesh()));

    m_actionPointsDisplay = new QAction(this);
    m_actionPointsDisplay->setText("Points");
    m_actionPointsDisplay->setStatusTip("Points Display.");
    connect(m_actionPointsDisplay, SIGNAL(toggled(bool)), m_openglViewer, SLOT(pointsDisplay(bool)));

    m_actionEdgesDisplay = new QAction(this);
    m_actionEdgesDisplay->setText("Edges");
    m_actionEdgesDisplay->setStatusTip("Edges Display.");
    connect(m_actionEdgesDisplay, SIGNAL(toggled(bool)), m_openglViewer, SLOT(edgesDisplay(bool)));


    m_actionFacesDisplay = new QAction(this);
    m_actionFacesDisplay->setText("Faces");
    m_actionFacesDisplay->setStatusTip("Faces Display.");
    connect(m_actionFacesDisplay, SIGNAL(toggled(bool)), m_openglViewer, SLOT(facesDisplay(bool)));
}
void MainWindow::createMenus()
{
    m_menuFile = menuBar()->addMenu(tr("File"));
    m_menuFile->addAction(m_actionImportMesh);
    m_menuFile->addSeparator();
    m_menuFile->addAction(m_actionClearMesh);

    m_menuDisplay = menuBar()->addMenu(tr("Display"));
    m_menuDisplay->addAction(m_actionPointsDisplay);
    m_menuDisplay->addAction(m_actionEdgesDisplay);
    m_menuDisplay->addAction(m_actionFacesDisplay);

}
void MainWindow::createStatusBar()
{
    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
    m_labelOperationInfo = new QLabel();
    m_labelOperationInfo->setMinimumSize(m_labelOperationInfo->sizeHint());


    statusBar()->addWidget(m_labelOperationInfo);
    connect(m_ioThread, SIGNAL(statusShowMessage(QString)), m_labelOperationInfo, SLOT(setText(QString)));
}
void MainWindow::setActionStatus(bool value)
{
    m_actionImportMesh->setEnabled(value);
    m_actionClearMesh->setEnabled(value);
}
void MainWindow::importMesh()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Import Mesh"), "../Models", tr(" *.obj *.off *.ply"));

    if(filename.isNull())
    {
        return;
    }

    m_ioThread->setFileName(filename);
    m_ioThread->m_ioType = ioThread::kImport;
    m_ioThread->start();
}
void MainWindow::clearMesh()
{
    setActionStatus(false);
    m_actionImportMesh->setEnabled(true);

    m_dataManager->clearMesh();
    m_openglViewer->resetMesh(m_dataManager->getMesh());
    m_openglViewer->updateGL();
    setActionStatus(false);
    m_actionImportMesh->setEnabled(true);

}

void MainWindow::needToUpdateGL(bool value)
{
    m_openglViewer->resetMesh(m_dataManager->getMesh(), value);
    m_openglViewer->updateGL();
}
