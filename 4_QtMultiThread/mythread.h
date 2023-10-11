#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread {

public:
  MyThread();

    // QThread interface
protected:
    void run() override;
    int internalCounter = 0;
};

#endif // MYTHREAD_H
