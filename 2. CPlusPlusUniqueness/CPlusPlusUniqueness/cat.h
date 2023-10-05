#ifndef CAT_H
#define CAT_H

#include "animal.h"

class Cat : public Animal
{
public:
    explicit Cat(string name, QObject *parent = nullptr);
    ~Cat();

    void MakeSound() override;
};

#endif // CAT_H
