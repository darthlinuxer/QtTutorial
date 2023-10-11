#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class Worker : public QObject {
  Q_OBJECT
  int internalCounter = 0;

public:
  Worker(QObject *parent = nullptr);
  ~Worker();

public:
signals:
  void WorkDone();

public slots:
  void DoWork();
};

#endif // WORKER_H
