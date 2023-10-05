#ifndef ANIMAL_H
#define ANIMAL_H

#include <QObject>
#include <iostream>

using namespace std;

//Pay attenting to this automatically created class... it has a funny constructor where it added
//a pointer to another QObject
//Automatically created classes can be created if you click on Project with right button and select Add New -> Class
//A popup window will appear where you can select the base class..
//If you delete the base class, everything that inherits from it will be deleted automatically
//But to do this, you must link the classes in the constructor using a pointer to another class
class Animal : public QObject
{
    Q_OBJECT
    std::string _name;
public:
    explicit Animal(std::string name, QObject *parent = nullptr);
    ~Animal();

    void Walk();
    std::string GetName();

    virtual void MakeSound()=0;
    //the method above is a pure virtual method which will
    //transform this to an Abstract class that cannot be instantiated.

signals:

};

#endif // ANIMAL_H
