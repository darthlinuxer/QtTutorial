#ifndef QTIMEREXAMPLE_H
#define QTIMEREXAMPLE_H

#include <QTimer>
#include <QDebug>
#include <QDateTime>

class QTimerExample: public QObject
{
    Q_OBJECT
    inline static int count = 0;
    inline static int timeouts = 0;
    QTimer _timer;

    void RunSingleShot(){
        qInfo() << count++ <<" : Single shot timer example was called";
    }

    void Timeout(){
        if(timeouts>5) {_timer.stop(); return; }
        timeouts++;
        qInfo() << "Interval timer example : " << QDateTime::currentDateTime().time().toString();
    }


public:
    void RunExample(){
        qInfo() << "=================TIMERS=====================";
        // Using a lambda function
        QTimer::singleShot(1000, this, [this](){ RunSingleShot(); });

        // Using Qt's QObject::destroyed signal as an example
        QTimer::singleShot(2000, this, &QTimerExample::RunSingleShot);

        // Using a locally defined pointer to the method
        void (QTimerExample::*methodPtr)() = &QTimerExample::RunSingleShot;
        QTimer::singleShot(3000, this, methodPtr);

        _timer.setInterval(1000);
        connect(&_timer, &QTimer::timeout, this, &QTimerExample::Timeout);
        _timer.start();

    }
};

#endif // QTIMEREXAMPLE_H
