#include "zookeeper.h"
#include "qdebug.h"

ZooKeeper::ZooKeeper(QObject *parent)
    : QObject{parent}
{

}

void ZooKeeper::animalStatusChanged(Animal *animal)
{
    auto status = animal ->animalStatus();
    if(status == AnimalStatus::tired){
        qInfo() << "Janitor saw <<"<< animal -> GetName()<<" animal and recommend not to make it walk any further";
    }
    if(status == AnimalStatus::hungry){
        qInfo() << "Janitor saw " << animal -> GetName() << "was Hungry and fed it";
        animal->Eat();
    }
    if(status == AnimalStatus::thirsty){
        qInfo() << "Janitor saw "<<animal->GetName()<<" was Thirsty animal and gave it water";
        animal->DrinkWater();
    }
    if(status == AnimalStatus::sad){
        qInfo() << "Janitor saw "<<animal->GetName()<<" was Sad animal and played with it";
        animal->Play();
    }

}
