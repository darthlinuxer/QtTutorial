#include <QCoreApplication>
#include "settingsexample.h"
#include "qbufferexample.h"
#include "qfileexample.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //QSettings are used to store read data from the registry or .ini files
    SettingsExample settingExample(a);
    settingExample.RunExample();

    qInfo() << "============= Qt IO Classes =====================";
    //Qbuffer inherits from QIO and stores in Memory
    QBufferExample bufferExample;
    bufferExample.RunExample();

    //QFile inherits from QIO and stores data in file
    QFileExample fileExample;
    fileExample.RunExample();



    return a.exec();
}