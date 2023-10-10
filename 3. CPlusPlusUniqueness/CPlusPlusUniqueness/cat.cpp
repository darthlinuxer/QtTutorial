#include "cat.h"
#include <iostream>
#include <QDebug>

using namespace std;


Cat::Cat(string name, QObject *parent): Animal(name,parent)
{
    qInfo() << GetName() << " Cat Created on addr: " << this;
}

Cat::~Cat()
{
    qInfo() << GetName() << " Cat Destroyed on addr: " << this;
}

void Cat::MakeSound()
{
    qInfo() << GetName() << " just said: Meow Meow Meow ";
}
