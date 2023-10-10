#include "animal.h"
#include <iostream>
#include <QDebug>
#include <QVariant>

using namespace std;

Animal::Animal(string name, QObject *parent): QObject(parent){
    qInfo() << name << "Animal Created on addr:" << this;
    connect(&_timer, &QTimer::timeout, this, &Animal::DecreaseHappinessOnIdleTime);
    this->_timer.setInterval(1000);
    this->_timer.start();
    qInfo() << "Timer started..";
    this->_name = name;
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
    m_animalStatus = newAnimalStatus;
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
    _hungryLevel+=increaseBy;
    if(_hungryLevel>100) {
        _hungryLevel=100;
    }
    qInfo() << this->GetName() << " Hungry is now at " << _happyLevel;
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
    _thirst+=increaseBy;
    if(_thirst>100){
        _thirst = 100;
    }
    qInfo() << this->GetName() << " Thirst is now at " << _thirst;

    if(_thirst>50){
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
    qInfo() << _name << "Animal walked " << meters << "m and stopped";
    _metersWalked+=meters;
    if(_metersWalked > 10){
        //You can set properties directly or using setProperty method
        //this->setAnimalStatus(AnimalStatus::tired); //setting directly
        this->setProperty("AnimalStatus", QVariant::fromValue(AnimalStatus::tired));
        this->increaseHungryLevel(meters*0.5);
        this->increaseThirst(meters*0.2);
    }
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
}

void Animal::DrinkWater()
{
     qInfo() << _name << "Animal is Drinking Water";
    this->_thirst = 0;
}

