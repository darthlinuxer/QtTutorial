#ifndef WORKERWITHTHREADENCAPSULATED_H
#define WORKERWITHTHREADENCAPSULATED_H

#include <QObject>
#include <QThread>
#include <QTimer>

class WorkerWithThreadEncapsulated : public QObject
{
    Q_OBJECT
    std::unique_ptr<QThread> m_thread;
    //defined a local thread variable that will be automatically deleted because it is a unique pointer
    QTimer m_timer;
    int counter = 0;

public:
    explicit WorkerWithThreadEncapsulated(QObject *parent = nullptr);
    ~WorkerWithThreadEncapsulated();

signals:
    void WorkDone();


public slots:
    void DoWork();
    void CleanUp();
};

#endif // WORKERWITHTHREADENCAPSULATED_H
