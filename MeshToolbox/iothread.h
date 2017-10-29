#ifndef IOTHREAD_H
#define IOTHREAD_H

#include <QThread>
#include <QFileDialog>
#include "datamanager.h"

class ioThread : public QThread
{
    Q_OBJECT
public:
    ioThread(DataManager *m_dataManager);
    ~ioThread();

    enum ioType{kNon, kImport, kExport};

signals:
    void statusShowMessage(QString);
    void setActionAndWidget(bool, bool);
    void needToUpdateGL(bool);

public:
    void setFileName(const QString fileName) {
       m_fileName = fileName;
     }
    void importMeshFromFile(QString &fileName);

public:
    void run();

public:
    QString m_fileName;
    ioType m_ioType;
    QWidget *m_widget;
    DataManager *m_dataManager;
};

#endif // IOTHREAD_H
