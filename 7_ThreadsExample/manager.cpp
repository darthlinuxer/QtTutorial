#include "manager.h"
#include "worker.h"

Manager::Manager(QObject *parent) : QObject(parent)
{
    qInfo() << "Created Manager at " << QThread::currentThread();

}

Manager::~Manager()
{
    qInfo() << "Destroyed Manager at " << QThread::currentThread();
    quit();
}

void Manager::process()
{
    QFuture<void> value = QtConcurrent::run(Manager::createWorker,this);
}

void Manager::quit()
{
    qInfo() << QThread::currentThread() << " is Stopping Manager";
    emit stop();
}

void Manager::createWorker(Manager *manager)
{
    qInfo() << "Manager is Creating a Worker on " << QThread::currentThread();
    Worker* worker = new Worker();
    //connect(manager,&Manager::start, worker, &Worker::start, Qt::QueuedConnection); // Qt::QueuedConnection
    connect(manager,&Manager::stop, worker, &Worker::stop, Qt::QueuedConnection); // Qt::QueuedConnection
    worker->start();
}
