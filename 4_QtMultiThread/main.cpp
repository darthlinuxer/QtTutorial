#include "mythread.h"
#include "worker.h"
#include "workerwiththreadencapsulated.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //The main Thread is the only one handling the GUI and should never be blocked!
    qInfo() << "Main thread id: " << QThread::currentThreadId();
    qInfo() << "Example 1: Inheriting from QThread and overriding the RUN method =========================";
    MyThread mythread; //Created on the Stack. C++ will manage its auto destruction in the end
    mythread.start();
    mythread.wait();
    //If you remove the wait above thread will continue in the background

    qInfo() << "Example 2: Executing a METHOD in another thread using Lambdas =========================";
    //Another way to create a QThread
    int x = 2, y = 3;
    QThread* thread1 = QThread::create([x,y]{qInfo()<<"Example 2: ThreadId:"<<QThread::currentThreadId()<<"x+y="<<x+y;});
    //Threads also have signals.. you just need to plug in a slot.. on this case I am using a lambda
    QObject::connect(thread1, &QThread::started, [](){qInfo() << "Example 2: ThreadId:"<<QThread::currentThreadId()<<" started";});
    QObject::connect(thread1, &QThread::finished, [](){qInfo() << "Example 2: ThreadId:"<<QThread::currentThreadId()<<" finished";});
    thread1->start();
    thread1->wait();
    delete thread1;

    //Use separate threads for long operations or use event loops to do the work in chunks
    //An Event Loop is necessary when dealing with timers, networking, queued connections, etc...
    //Qt supports per-thread event loops.

    qInfo() << "Example 3: Moving and object to a thread =======================================";
    //Executing a method within a thread
    //This allows us to run code in other threads without subclassing QThread like mythread.cpp on this project
    QThread thread2; //created on the stack. C++ will clean the memory
    Worker* worker = new Worker; //created on the heap
    QObject::connect(&thread2, &QThread::started, worker, &Worker::DoWork, Qt::QueuedConnection);
    //QObject::connect(&thread2, &QThread::started, [worker]{ worker->DoWork();}); //another way of calling DoWork
    QObject::connect(worker, &Worker::WorkDone, &thread2, &QThread::quit, Qt::DirectConnection);
    QObject::connect(&thread2, &QThread::finished, worker, &Worker::deleteLater, Qt::QueuedConnection); //will delete the worker
    worker->moveToThread(&thread2);
    thread2.start();
    thread2.wait();
    //no need to delete thread2.. it is on the stack

    qInfo() << "Example 4: Design Pattern to encapsulate a thread within an object ==========================";
    WorkerWithThreadEncapsulated* worker2 = new WorkerWithThreadEncapsulated();
    bool workFinished = false;
    QObject::connect(worker2, &WorkerWithThreadEncapsulated::WorkDone,
                     [&]{ workFinished = true;});
    while(!workFinished){
        qInfo() << "Example 4: Main Thread awaiting worker to finish";
        QThread::sleep(1);
    }
    delete worker2;
    //if you don´t delete this worker the thread will continue in the background because the cleanup
    //will never be called. CleanUp is called upon destruction of the object.

    qInfo() << "Example 4: continuing execution...";
    return a.exec();
}
