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

    //How about make a connection with the Slot in QCoreApplication so
    //that if an AnimalDied Signal is emited the application will quit
    //This connection had to be made through lambdas because the slot EXIT
    //requires an int argument and returns an int
    //Signals and Slots are required to have the same signature and AnimalDied signal
    //does not have any argument and returns a void
    QObject::connect(
        cat, &Animal::animalDied, &a,[]() { QCoreApplication::exit(-1);},
        Qt::QueuedConnection);

    QObject::connect(
        dog, &Animal::animalDied, &a, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    //NOW RUN THE PROGRAM AND MAKE THE ANIMAL WALK 500m
    //CHECK THE LOGS TO SEE THAT THE EXIT CODE OF THE APPLICATION IS -1 !!!
    //WHY IT DIDN´T QUIT IMMEDIATELY AFTER ANIMAL DIED SIGNAL WAS EMMITED ?

    dog->MakeSound();
    cat->MakeSound();
    QTextStream qin(stdin);
    QString input;
    int meters = 0;
    for (int i = 1; i <= 2; i++) {
      qInfo() << "*****************************************************************************";
      qInfo() << "Do you want the animals to walk how many Km ? ";
      input = qin.readLine();
      qInfo() << "-----------------------------------------------------------------------------";
      meters = input.toInt();
      dog->Walk(meters);
      cat->Walk(meters);
      QThread::sleep(1);
    }
    //read the logs carefully and see why the Animal timer that has started on his constructor was only
    //active AFTER the for loop above ended
    //Reason: TIMERS work on the same thread as the main program.. unless you start it in another thread
    //it will always be in sync.

    dog->MakeSound();
    cat->MakeSound();
    //delete zookeeper;
}
