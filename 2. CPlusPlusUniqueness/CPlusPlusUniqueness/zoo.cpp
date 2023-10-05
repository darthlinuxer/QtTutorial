#include "zoo.h"

Zoo::Zoo(QObject *parent): QObject(parent)
{
    std::cout << "Zoo created";
}

Zoo::~Zoo()
{
    std::cout << "Zoo deleted";
}

QList<Animal *> Zoo::GetAnimals()
{
    return _animals;
}
