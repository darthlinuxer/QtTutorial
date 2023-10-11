#include "mythread.h"
#include "qdebug.h"

MyThread::MyThread() {}

void MyThread::run() {

  while (internalCounter < 3) {

    qInfo() << "Example 1: Thread Id:" << this->currentThreadId()
            << "Internal Counter: " << internalCounter;
    internalCounter++;
    QThread::sleep(1);
  }
}
