#include "manager.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThread::currentThread()->setObjectName("Main Thread");
    Manager manager;
    for(int i = 0; i<3; i++) manager.process();

    qInfo() << QThread::currentThread() << " sleeping for 5s";
    QThread::sleep(5);

    qInfo() << QThread::currentThread() << " manager is quitting....";
    manager.quit();
    return a.exec();
}
