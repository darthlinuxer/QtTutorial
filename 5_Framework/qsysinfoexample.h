#ifndef QSYSINFOEXAMPLE_H
#define QSYSINFOEXAMPLE_H
#include <QSysInfo>
#include <QDebug>

class QSysInfoExample
{
public:
    void RunExample(){
        QSysInfo sys;
        qInfo() << "System info:";
        qInfo() << "Boot id: " << sys.bootUniqueId();
        qInfo() << "Build: " << sys.buildAbi();
        qInfo() << "Cpu: " << sys.buildCpuArchitecture();
        qInfo() << "Kernel: " << sys.kernelVersion();
        qInfo() << "Host: " << sys.machineHostName();
        qInfo() << "Product: " << sys.prettyProductName();
        qInfo() << "Type: " << sys.productType();
        qInfo() << "Version: " << sys.productVersion();

#ifdef Q_OS_LINUX
        qInfo() << "Running on linux!";
#elif defined(Q_OS_WIN)
        qInfo() << "Running on Windows!";
#elif defined(Q_OS_MACX)
        qInfo() << "Running on Mac";
#else
        qInfo() << "Unknown OS Code";
#endif
    }
};


#endif // QSYSINFOEXAMPLE_H
