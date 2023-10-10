#include "dog.h"
#include <iostream>
#include <QDebug>

using namespace std;


Dog::Dog(string name, QObject *parent): Animal(name,parent)
{
    qInfo() << GetName() << " Dog Created on addr: " << this;
}

Dog::~Dog()
{
    qInfo() << GetName() << " Dog Destroyed on addr: " << this;
}

void Dog::MakeSound()
{
    qInfo() << GetName() << " just said: Ooof Ooof Ooof ";
}
