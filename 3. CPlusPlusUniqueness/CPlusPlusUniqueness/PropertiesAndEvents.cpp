#include "zoo.h"
#include "zookeeper.h"
#include "cat.h"
#include "dog.h"
#include "animal.h"
#include <QCoreApplication>
#include <QThread>

void PropertiesAndEventsExample(QCoreApplication& a)
{
    qInfo() << "---------------------------PROPERTIES AND EVENTS EXAMPLE--------------------------";
    ZooKeeper* zookeeper = new ZooKeeper(&a); //Created on the HEAP but lifecycle is tied to main app

    Animal* dog = new Dog("Buster the Dog", zookeeper); //if zookeeper is destroyed, bye bye Buster as well.
    Animal* cat = new Cat("Tom the Cat", zookeeper);

    QObject::connect(dog, &Animal::animalStatusChanged,
                     zookeeper, &ZooKeeper::animalStatusChanged,
                     Qt::QueuedConnection);
    QObject::connect(cat, &Animal::animalStatusChanged,
                     zookeeper, &ZooKeeper::animalStatusChanged,
                     Qt::QueuedConnection);

    dog->MakeSound();
    cat->MakeSound();
    for (int i = 0; i <= 5; i++) {
      dog->Walk(i*10);
      cat->Walk(i*5);
      QThread::sleep(1);
    }
    dog->MakeSound();
    cat->MakeSound();
    dog->Walk(500);
    QThread::sleep(1);
    dog->Walk(500);
    QThread::sleep(1);
    cat->Walk(100);

    delete zookeeper;

}
