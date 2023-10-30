#ifndef CONSUMER_H
#define CONSUMER_H

#include <QObject>
#include <QMutex>
#include <QWaitCondition>
#include <QRunnable>
#include <QRandomGenerator>
#include <QThread>
#include <QDebug>

class Consumer: public QRunnable
{
  QMutex *_mutex;
  QWaitCondition *_wait;
  int *_value;

public:
  Consumer(QMutex *mutex, QWaitCondition *wait, int *value) {
    QThread::currentThread()->setObjectName("Consumer");
    qInfo() << "Consumer created at " << QThread::currentThread();
    _mutex = mutex;
    _wait = wait;
    _value = value;
  }
  ~Consumer(){
    qInfo() << "Consumer destroyed at " << QThread::currentThread();
  }

  // QRunnable interface
  public:
  void run() override{
    qInfo() << QThread::currentThread() << " is running a consumer...";
    _mutex->lock();
    qInfo() << QThread::currentThread() << " locked the mutex...";
    if(*_value == 0) {
        qInfo() << " Consumer is awaiting for a value...";
        _wait->wait(_mutex);
    }
    qInfo() << "Consumed value " << *_value;
  }
};

#endif // CONSUMER_H
