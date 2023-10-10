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
                     Qt::AutoConnection);
    QObject::connect(cat, &Animal::animalStatusChanged,
                     zookeeper, &ZooKeeper::animalStatusChanged,
                     Qt::AutoConnection);

    dog->MakeSound();
    cat->MakeSound();
    for (int i = 1; i <= 5; i++) {
      qInfo() << "------------------ STEP "<< i <<" of 5 ------------------------------";
      dog->Walk(i*20);
      cat->Walk(i*10);
      QThread::sleep(1);
    }
    dog->MakeSound();
    cat->MakeSound();
    //delete zookeeper;
}
