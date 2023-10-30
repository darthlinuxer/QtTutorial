#ifndef COUNTER_H
#define COUNTER_H
#include <QRunnable>
#include <QDebug>
#include <QThread>
#include <QMutex>

class Counter: public QRunnable
{
private:
    int* _value;
    QMutex* _mutex;

public:
    Counter(QMutex* mutex, int* value){
        this->_mutex = mutex;
        this->_value = value;
        qInfo() << "Counter created at " << QThread::currentThread();
    }

    ~Counter(){
        qInfo() << "Counter destroyed at " << QThread::currentThread();
    }
    // QRunnable interface
public:
    void run() override
    {

        //Once locker goes out of scope, the mutex will be unlocked
        QMutexLocker locker(_mutex); //if you don´t want to use QMutexLocker, you have to lock and unlock manually
        //_mutex->lock();
        QThread::currentThread()->msleep(50);
        *_value = *_value + 1;
        QThread::currentThread()->setObjectName("Thread"+QString::number(*_value));
        qInfo() << QThread::currentThread() << " value = " << *_value;
        //_mutex->unlock();
    }
};

#endif // COUNTER_H
