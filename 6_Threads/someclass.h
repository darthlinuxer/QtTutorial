#ifndef SOMECLASS_H
#define SOMECLASS_H

#include <QObject>
#include <QThread>
#include <QDebug>

class SomeClass : public QObject
{
    Q_OBJECT
public:
    explicit SomeClass(QObject *parent = nullptr):QObject(parent){
        qInfo() << "Some class created at " << QThread::currentThread();
    }
    ~SomeClass(){
        qInfo() << "Some class destroyed at " << QThread::currentThread();
    }

signals:
    void WorkDone();

public slots:
    void DoWork(){
        qInfo() << "Starting DoWork on SomeClass " << QThread::currentThread();
        for(int i=1; i<=5; i++) { qInfo() << i << " on thread " << QThread::currentThread() ;}
        qInfo() << QThread::currentThread() << " emitting WorkDone()";
        emit WorkDone();
    }

};

#endif // SOMECLASS_H
