#include "workerwiththreadencapsulated.h"
#include "qdebug.h"

WorkerWithThreadEncapsulated::WorkerWithThreadEncapsulated(QObject *parent)
    : QObject{parent}
{
    qInfo() << "Example 4: Worker created at addr: "<< this << " ThreadId: "<< this->thread()->currentThreadId();
  // create timers, sockets, etc...
  m_thread.reset(new QThread);
  this->moveToThread(m_thread.get()); // will move this object to the secondary thread
  this->m_timer.moveToThread(m_thread.get()); //move the timer to the secondary thread
  connect(
      m_thread.get(), &QThread::started, this, [this]{
        qInfo() << "Example 4: SUB ThreadId:" << QThread::currentThreadId() << " started";
        m_timer.setInterval(500); // 500ms
        m_timer.start();
      });
  connect(m_thread.get(), &QThread::finished, [](){qInfo() << "Example 4: SUB ThreadId:"<<QThread::currentThreadId()<<" finished";});
  connect(&m_timer, &QTimer::timeout, this, &WorkerWithThreadEncapsulated::DoWork, Qt::QueuedConnection);
  m_thread->start();
  qInfo() << "Example 4: WorkerWithThreadEncapsulated started thread with id " << m_thread.get()->currentThreadId();
}

WorkerWithThreadEncapsulated::~WorkerWithThreadEncapsulated()
{
    qInfo() << "Example 4: Worker with thread encapsulated was destroyed at " << this;
    QMetaObject::invokeMethod(this, "CleanUp"); //will call this method in the secondary thread
    m_thread->wait(); //wait for the CleanUp to be done
}

void WorkerWithThreadEncapsulated::DoWork()
{
    qInfo() << "Example 4: Counting in the background: counter "<< counter <<" of 5";
    counter++;
    if(counter >=5) {
        qInfo() << "Example 4: WORK DONE! Emiting signal...";
        emit WorkDone();
    }
}

void WorkerWithThreadEncapsulated::CleanUp()
{
    //delete timers, sockets, etc...
    //m_timer is on the stack... C++ will take care to delete it when this thread finishes
    m_timer.stop();
    m_thread->quit();
}
