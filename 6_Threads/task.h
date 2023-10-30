#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QRunnable>

class Task : public QObject, public QRunnable
{
    Q_OBJECT
    inline static int count=0;
public:
    explicit Task(QObject *parent = nullptr):QObject(parent){
        qInfo() << "Task created at : " << this << QThread::currentThread()->objectName();
    }
    ~Task(){
        qInfo() << "Task destroyed at : " << this << QThread::currentThread()->objectName();
    }

signals:


    // QRunnable interface
public:
    void run() override {
        QThread::currentThread()->setObjectName("Thread"+QString::number(count++));
        qInfo() << "Starting " << QThread::currentThread() << " to count 1 to 5";
        for(int i=1; i<=5; i++) { qInfo() << i << " on thread " << QThread::currentThread();}
    }
};

#endif // TASK_H
