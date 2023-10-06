#include "animal.h"
#include <iostream>
#include <QDebug>

using namespace std;

Animal::Animal(string name, QObject *parent): QObject(parent){
    qInfo() << name << "Animal Created on addr:" << this;
    this->_name = name;
}

Animal::~Animal()
{
    qInfo() << _name << "Animal Destroyed on addr:" << this;
}

void Animal::Walk()
{
    qInfo() << _name << "Animal is walking";
}

string Animal::GetName()
{
    return _name;
}

