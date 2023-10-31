#ifndef TESTSLOT_H
#define TESTSLOT_H

#include <QThread>
#include <QDebug>

class TestSlot : public QObject {
    Q_OBJECT

public:
    TestSlot(QObject *parent = nullptr):QObject(parent){
        qInfo() << "Test Slot created at " << QThread::currentThread();
    }
    ~TestSlot(){
        qInfo() << "Test Slot destroyed at " << QThread::currentThread();
    }

public slots:
    void Finished(){
        qInfo() << "Slot Finished from Example 10 called...";
    }
};

#endif // TESTSLOT_H
