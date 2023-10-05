#ifndef DOG_H
#define DOG_H

#include "animal.h"

class Dog : public Animal
{
public:
    explicit Dog(std::string name, QObject *parent = nullptr);
    ~Dog();

    void MakeSound() override;

};

#endif // DOG_H
