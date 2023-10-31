#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QThreadPool>
#include <QSharedPointer>
#include <QtConcurrent>
#include <QSemaphore>
#include <QMutex>
#include <QFuture>
#include <QFutureWatcher>
#include "counter.h"
#include "someclass.h"
#include "task.h"
#include "producer.h"
#include "consumer.h"
#include "TestSlot.h"


int Test(){
    qInfo() << "QtConcurrent: Started thread " << QThread::currentThread();
    int value = 0;
    for(int i=0;i<10;i++) value+=i;
    return value;
}

int DoMap(int value)
{
    int num = value * 10;
    qInfo() << "Mapped " << value << " to " << num << " on thread " << QThread::currentThread();
    return num;
}

void DoMapVoid(int value)
{
    int num = value * 10;
    qInfo() << "Mapped " << value << " to " << num << " on thread " << QThread::currentThread();
}

void PrintName(std::string name, int max)
{
    for(int i=0; i<max; i++) qInfo()<< "Hello " << name << ":" << i << " -> from thread " << QThread::currentThread();
}

void dostuff(int value)
{
    for (int i = 0;i < 5; i++)
    {
        QThread::currentThread()->msleep(100);
        qInfo() << "Thread: " << value << " = " << i;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qInfo() << "============= Example 1: Creating a simple thread and doing some work =============";
    QThread::currentThread()->setObjectName("Main Thread");
    QThread worker;
    worker.setObjectName("Worker Thread");

    qInfo() << QThread::currentThread() << " is running..";
    QScopedPointer<SomeClass> scopedPtrToObj(new SomeClass());
    SomeClass *obj = scopedPtrToObj.data();
    qInfo() << "Moving SomeClass object to another thread : " << &worker;
    obj->moveToThread(&worker); //classes that have parent cannot be moved

    qInfo() << "Connecting Signal from Thread Worker to Slot DoWork on SomeClass object ";
    QObject::connect(&worker, &QThread::started, obj, &SomeClass::DoWork);
    QObject::connect(obj, &SomeClass::WorkDone, &worker, &QThread::quit, Qt::DirectConnection);
    QObject::connect(&worker, &QThread::finished, []() {qInfo() << "Worker thread has finished.";});
    qInfo() << "Starting Worker Thread... ";
    worker.start();
    qInfo() << QThread::currentThread() << " is ready to do something else...";
    worker.wait();

    qInfo() << "\n\n============= Example 2: Working with ThreadPool =============";
    qInfo() << "Max Threads according to the number of cpu cores: " << QThreadPool::globalInstance()->maxThreadCount();
    for(int i=1; i<=10; i++){
        Task *task = new Task(); //this pointer will be managed by the Threadpool
        task->setAutoDelete(true);  //setAutoDelete comes from QRunnable inheritance
        if (!QThreadPool::globalInstance()->tryStart(task)) {
            qWarning() << "Could not start task" << i;
        }
    }
    QThreadPool::globalInstance()->waitForDone();

    qInfo() << "\n\n============= Example 3: Working with ThreadPool and QMutex =============";
    QThreadPool pool = QThreadPool::globalInstance();
    QMutex mutex;
    int value = 0;
    for(int i=1; i<=10; i++){
        Counter* c = new Counter(&mutex, &value);
        c->setAutoDelete(true);  //setAutoDelete comes from QRunnable inheritance
        if (!pool.tryStart(c)) {
            qWarning() << "Could not start Counter" << i;
        }
    }
    pool.waitForDone();

    qInfo() << "\n\n============= Example 4: Working with ThreadPool and Producer Consumer =============";
    value = 0;
    QWaitCondition wait;
    Producer* producer = new Producer(&mutex, &wait, &value);
    Consumer* consumer = new Consumer(&mutex, &wait, &value);
    producer->setAutoDelete(true);
    consumer->setAutoDelete(true);
    pool.start(consumer);
    pool.start(producer);
    pool.waitForDone();

    qInfo() << "\n\n============= Example 5: Working with ThreadPool and QSemaphore =============";
    //4 threads will be created but only 2 threads will at the same time modify elements in a list of integers
    QList<int> list(10, 0); //create a list of 10 elements and fill them up with 0´s
    QAtomicInt index(0); //create a variable to be safely shared between all threads
    QSemaphore semaphore(2); // Allow 2 threads to enter the critical section

    qInfo() << "List size = " << list.size();

    auto modifyList = [&] {
        while(true) {
            semaphore.acquire();
            int i = index.fetchAndAddAcquire(1); //get current i and add 1 afte
            if(i>=list.size()) {
                semaphore.release();
                break;
            }
            qInfo() << QThread::currentThread() << " acquired semaphore";
            list[i] = QRandomGenerator::global()->bounded(100);
            qInfo() << QThread::currentThread() <<" List[" << i << "] = " << list[i];
            semaphore.release();
            qInfo() << QThread::currentThread() << " released semaphore";
        }
        qInfo() << QThread::currentThread() << " is quitting...";
        QThread::currentThread()->quit();
    };

    QThread thread1;
    thread1.setObjectName("Thread 1");
    QObject::connect(&thread1, &QThread::started, modifyList);

    QThread thread2;
    thread2.setObjectName("Thread 2");
    QObject::connect(&thread2, &QThread::started, modifyList);

    QThread thread3;
    thread3.setObjectName("Thread 3");
    QObject::connect(&thread3, &QThread::started, modifyList);

    QThread thread4;
    thread4.setObjectName("Thread 4");
    QObject::connect(&thread4, &QThread::started, modifyList);

    thread1.start();
    thread2.start();
    thread3.start();
    thread4.start();

    thread1.wait();
    thread2.wait();
    thread3.wait();
    thread4.wait();

    qInfo() << "\n\n============= Example 6: Working with Concurrency =============";
    QFuture<void> future0 = QtConcurrent::run(&PrintName, "Camilo", 5);
    qInfo() << "Doing something else...";
    future0.waitForFinished();
    qInfo() << "Done..";
    qInfo() << "Starting QFuture with a returned value, .result blocks the thread until finished";

    QFuture<int> future1 = QtConcurrent::run(&Test);
    QFuture<int> future2 = QtConcurrent::run(&Test);
    QFuture<int> future3 = QtConcurrent::run(&Test);
    qInfo() << "Future 1 Sum: " << future1.result();
    qInfo() << "Future 2 Sum: " << future2.result();
    qInfo() << "Future 3 Sum: " << future3.result();

    qInfo() << "\n\n============= Example 7: Working with QtConcurrency blocking a thread=============";
    QList<int> values;
    for(int i=0; i<5; i++) values << i;
    qInfo() << "Starting...";
    //Will run each value on different threads in a ThreadPool but will block execution until finished
    QList<int> mappedList = QtConcurrent::blockingMapped(values, &DoMap);
    qInfo() << "Finished...";
    qInfo() << mappedList;

    qInfo() << "\n\n============= Example 8: Working with QtConcurrency in multiple threads returning a value =============";
    values.clear();
    for(int i=0; i<5; i++) values << i;
    qInfo() << "Starting...";
    //Will run each value on different threads in a ThreadPool, return a value and will not block execution of main thread
    QFuture<int> future4 = QtConcurrent::mapped(values, &DoMap);
    qInfo() << "Back to main Thread...";
    qInfo() << future4.results(); //blocks the main thread

    qInfo() << "\n\n============= Example 9: Working with QtConcurrency in multiple threads not returning a value =============";
    values.clear();
    for(int i=0; i<5; i++) values << i;
    qInfo() << "Starting...";
    //Will run each value on different threads in a ThreadPool, does not block main thread, values are returned by ref
    QFuture<void> future5 = QtConcurrent::map(values, &DoMapVoid);
    qInfo() << "Back to main Thread...";
    future5.waitForFinished(); //blocks the main thread
    qInfo() << values;

    qInfo() << "\n\n============= Example 10: Working with QFutureWatcher connecting signals and slots =============";
    values.clear();
    for(int i=0; i<5; i++) values << i;
    qInfo() << values;

    QFutureWatcher<void> watcher;
    TestSlot test;
    QObject::connect(&watcher, &QFutureWatcher<void>::finished, &test, &TestSlot::Finished, Qt::DirectConnection);

    qInfo() << "Starting...";
    QFuture<void> voidMap = QtConcurrent::map(values, &DoMapVoid);
    watcher.setFuture(voidMap);
    qInfo() << "Back on Main Thread...";
    watcher.waitForFinished(); //blocking execution

    qInfo() << "Done";
    qInfo() << mappedList;
    qInfo() << watcher.isFinished();

    qInfo() << "\n\n============= Example 11: Working with Iterators =============";
    values.clear();
    for(int i=0; i<3; i++) values << i;
    QFuture<int> future6 = QtConcurrent::mapped(values, &DoMap);

    //iterating each value using QFutureIterator
    QFutureIterator<int> iter(future6);
    while(iter.hasNext()) qInfo() << "QFutureIterator style: " << iter.next();

    //iterating each value in normal C++ Style
    for(int i =0; i< future6.results().length(); i++) qInfo() << "index style: " << future6.resultAt(i);

   //Iteration Qt style
    foreach(int i, future6.results()) qInfo() << "Qt style: " << i;

    qInfo() << "\n\n============= Example 12: Running multiple QFutures =============";
    QFutureSynchronizer<void> sync;
    for(int i = 0; i < 2; i++)
    {
        QFuture<void> f = QtConcurrent::run(&dostuff,i);
        sync.addFuture(f);
    }

    //sync.waitForFinished();
    //waitForFinished called in the QFutureSynchronizer deconstructor

    return a.exec();
}

