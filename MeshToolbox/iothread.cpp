#include "iothread.h"

ioThread::ioThread(DataManager *dataManager)
{
    if(dataManager != NULL)
        m_dataManager = dataManager;
}

ioThread::~ioThread()
{

}
void ioThread::importMeshFromFile( QString &fileName)
{
    emit(setActionAndWidget(false, false));
    emit(statusShowMessage("Now loading mesh"+ fileName + " ..."));
    if(!m_dataManager->importMeshFromFile(fileName.toStdString()))
    {
        emit(statusShowMessage("Loading mesh " + fileName + " failed."));
        return;
    }
    else
        emit(statusShowMessage("Loading mesh " +fileName + " successful."));

    emit(needToUpdateGL(true));
    emit(setActionAndWidget(true, true));
}
void ioThread::run()
{
    if(m_ioType == kImport){
        importMeshFromFile(m_fileName);
    }
}
