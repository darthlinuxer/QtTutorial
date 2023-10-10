#include "animal.h"
#include <iostream>
#include <QDebug>
#include <QVariant>
#include <QMetaEnum>

using namespace std;

Animal::Animal(string name, QObject *parent): QObject(parent){
    this->_name = name;
    qInfo() << name << "Animal Created on addr:" << this;

    //Creating a timer to decrease animal happiness on idle time
    connect(&_timer, &QTimer::timeout, //source
            this, &Animal::DecreaseHappinessOnIdleTime,
            Qt::QueuedConnection); //destination
    this->_timer.setInterval(1000);
    this->_timer.start();
}

Animal::~Animal()
{
    qInfo() << _name << "Animal Destroyed on addr:" << this;
    disconnect(&_timer, &QTimer::timeout, this, &Animal::DecreaseHappinessOnIdleTime);
}


AnimalStatus Animal::animalStatus() const
{
    return m_animalStatus;
}

void Animal::setAnimalStatus(AnimalStatus newAnimalStatus)
{
    if (m_animalStatus == newAnimalStatus)
        return;
    qInfo() << GetName() << " new status: " << this->AnimalStatusToString(newAnimalStatus);
    m_animalStatus = newAnimalStatus;
    qInfo() << "Animal is " << this->AnimalStatusToString(newAnimalStatus)
            << ">>>>> NOTIFYING CARETAKER ABOUT THIS "
               "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    emit animalStatusChanged(this);
}

void Animal::DecreaseHappinessOnIdleTime()
{
    qInfo() << GetName() << " is getting unhappy because of idle time";
    decreaseHappyLevel(10);
}

int Animal::hungryLevel() const
{
    return _hungryLevel;
}

void Animal::increaseHungryLevel(int increaseBy)
{
    qInfo() << this->GetName() << " Hungriness: " << _hungryLevel <<", and will be increased by " << increaseBy;
    _hungryLevel+=increaseBy;
    if(_hungryLevel>100) {
        _hungryLevel=100;
    }
    qInfo() << this->GetName() << " Hungry is now at " << _hungryLevel;
    if(_hungryLevel>50) {
        qInfo() << this->GetName() << " is officially Hungry.. someone has to do something about it";
        this->setAnimalStatus(AnimalStatus::hungry);
    }
}

int Animal::happyLevel() const
{
    return _happyLevel;
}

void Animal::decreaseHappyLevel(int decreaseBy)
{
    _happyLevel -= decreaseBy;
    if(_happyLevel<0) {
        _happyLevel = 0;
    }

    qInfo() << this->GetName() << " Happiness is now at " << _happyLevel;

    if(_happyLevel<50){
        qInfo() << this->GetName() << " is SAD";
        this->setAnimalStatus(AnimalStatus::sad);
    }
    if(_happyLevel>=50){
        qInfo() << this->GetName() << " is Happy";
        this->setAnimalStatus(AnimalStatus::happy);
    }
}

int Animal::thirst() const
{
    return _thirst;
}

void Animal::increaseThirst(int increaseBy)
{
    qInfo() << this->GetName() << " Thirst: " << _thirst <<", and will be increased by " << increaseBy;
    _thirst+=increaseBy;
    if(_thirst>100){
        _thirst = 100;
    }
    qInfo() << this->GetName() << " Thirst is now at " << _thirst;

    if(_thirst>=50){
        qInfo() << this->GetName() << " is officially Thirsty.. someone has to do something about it";
        this->setAnimalStatus(AnimalStatus::thirsty);
    }
}

void Animal::Walk()
{
    qInfo() << _name << "Animal walked 1m and stopped";
    _metersWalked++;
    this->increaseHungryLevel(20);
    this->increaseThirst(20);
}

void Animal::Walk(int meters)
{
    _metersWalked += meters;
    qInfo() << _name << "Animal walked " << meters << "m and stopped. Today it walked in total:" << _metersWalked;
    // You can set properties directly or using setProperty method
    // this->setAnimalStatus(AnimalStatus::tired); //setting directly
    this->setProperty("animalStatus", QVariant::fromValue(AnimalStatus::tired));
    this->increaseHungryLevel(meters * 0.5);
    this->increaseThirst(meters * 0.2);
}

string Animal::GetName()
{
    return _name;
}

void Animal::Sleep()
{
    this->setAnimalStatus(AnimalStatus::sleeping);
    qInfo() << _name << "Animal is sleeping";
    this->_metersWalked = 0;
}

void Animal::Eat()
{
    qInfo() << _name << "Animal is Eating";
    this->_hungryLevel = 0;
}

void Animal::Play()
{
    qInfo() << _name << "Animal is Playing";
    this->setAnimalStatus(AnimalStatus::happy);
    this->_happyLevel = 100;
    this->_timer.stop();
}

void Animal::DrinkWater()
{
    qInfo() << _name << "Animal is Drinking Water";
    this->_thirst = 0;
}

