#include "worker.h"
#include <QThread>
#include <QDebug>

Worker::Worker(QObject *parent):QObject(parent)
{
    qInfo() << "Example 3: Worker created at addr: " << this;
}

Worker::~Worker()
{
    qInfo() <<  "Example 3: Worker destroyed at addr: " << this;
}

void Worker::DoWork()
{
    //Slots are normal Methods with the ability to be connected to signals
    //On this case, this method is prepared to be executed within a Thread linked from the outside
    while(internalCounter < 3){
        qInfo() << "Example 3: Worker ThreadId:" << QThread::currentThreadId() << " counter:" << internalCounter;
        internalCounter++;
        QThread::sleep(1);
    }
    qInfo() << "Example 3: WORK DONE! Emiting signal...";
    emit WorkDone();
}
