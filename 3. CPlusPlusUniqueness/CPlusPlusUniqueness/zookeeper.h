#ifndef ZOOKEEPER_H
#define ZOOKEEPER_H

#include "animal.h"
#include <QObject>

class ZooKeeper : public QObject
{
    Q_OBJECT

public:
    explicit ZooKeeper(QObject *parent = nullptr);
    ~ZooKeeper();

public slots:
    void animalStatusChanged(Animal *animal);
};

#endif // ZOOKEEPER_H
