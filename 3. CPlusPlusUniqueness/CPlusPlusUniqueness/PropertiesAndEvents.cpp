#include "zoo.h"
#include "zookeeper.h"
#include "cat.h"
#include "dog.h"
#include "animal.h"
#include <QCoreApplication>
#include <thread>

void PropertiesAndEventsExample(QCoreApplication& a)
{
    qInfo() << "---------------------------PROPERTIES AND EVENTS EXAMPLE--------------------------";
    ZooKeeper* zookeeper = new ZooKeeper(); //Created on the HEAP but lifecycle is tied to Zoo

    Dog* dog = new Dog("Buster the Dog", zookeeper); //if zoo is destroyed, bye bye Snoopy as well.
    Cat* cat = new Cat("Tom the Cat", zookeeper);

    QObject::connect(dog, &Dog::animalStatusChanged,
                     zookeeper, &ZooKeeper::animalStatusChanged,
                     Qt::QueuedConnection);
    QObject::connect(cat, &Cat::animalStatusChanged,
                     zookeeper, &ZooKeeper::animalStatusChanged,
                     Qt::QueuedConnection);

    dog->MakeSound();
    cat->MakeSound();
    for (int i = 0; i <= 5; i++) {
      dog->Walk(i*10);
      cat->Walk(i*5);
      std::this_thread::sleep_for(std::chrono::seconds(5)); // Time Delay
    }
    dog->MakeSound();
    cat->MakeSound();
    dog->Walk(500);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //Time Delay
    dog->Walk(500);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //Time Delay
    cat->Walk(100);

    delete zookeeper;

}
