#ifndef CASTING_H
#define CASTING_H

#include <QDebug>

class Car {
public:
    void makeSound() {
        qInfo() << "Dynamic Cast: Car says Vroom Vroom...";
    }
};

void RunCastingExamples();

#endif // CASTING_H
