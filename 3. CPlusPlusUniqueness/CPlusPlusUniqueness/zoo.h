#ifndef ZOO_H
#define ZOO_H

#include "animal.h"
#include <QObject>

class Zoo : public QObject
{
    Q_OBJECT
private:
    QList<Animal*> _animals;
public:
    explicit Zoo(QObject *parent = nullptr);
    ~Zoo();

    void AddAnimal(Animal* animal) {
        _animals.append(animal);
    }

    QList<Animal*> GetAnimals();

};

#endif // ZOO_H
