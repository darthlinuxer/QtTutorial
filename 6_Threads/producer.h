#ifndef PRODUCER_H
#define PRODUCER_H

#include <QObject>
#include <QMutex>
#include <QWaitCondition>
#include <QRunnable>
#include <QRandomGenerator>
#include <QThread>
#include <QDebug>

class Producer: public QRunnable
{
    QMutex* _mutex;
    QWaitCondition* _wait;
    int* _value;
public:
    Producer(QMutex* mutex, QWaitCondition* wait, int* value){
        QThread::currentThread()->setObjectName("Producer");
        qInfo() << "Producer created at " << QThread::currentThread();
        _mutex = mutex;
        _wait = wait;
        _value = value;
    }
    ~Producer(){
        qInfo() << "Producer destroyed at " << QThread::currentThread();
    }

    // QRunnable interface
public:
    void run() override{
        qInfo() << QThread::currentThread() << " is running a Producer...";
        _mutex->lock();
        *_value = QRandomGenerator::global()->bounded(1000);
        qInfo() << QThread::currentThread() << " produced number " << *_value;
        _mutex->unlock();
        _wait->wakeAll();
        qInfo() << QThread::currentThread() << " producer notified all he finished";
    }
};

#endif // PRODUCER_H
