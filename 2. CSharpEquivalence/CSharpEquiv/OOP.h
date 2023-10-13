#ifndef OOP_H
#define OOP_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <QObject>
#include <QMetaObject>
#include <QMetaMethod>

using namespace std;

/*
 * in C++, assigning = 0 to a virtual function makes it a pure virtual function.
 * This means that the function has no implementation in the base class and must be overridden
 * by any non-abstract derived class. Making a function pure virtual also makes the class abstract,
 * meaning you cannot create an instance of it.
 * */
class IMovable {
public:
    virtual void Move() = 0;
};

class IMakeSound {
public:
    virtual void MakeSound() = 0;
};

class IAnimal : public IMovable, public IMakeSound {};
class IDestroyableAnimal : public IAnimal {
  public:
    /*
        In C++, even pure virtual destructors need a definition.
        This is because the destructor of the base class is always called when a derived
        object is destroyed. When you delete an object through a pointer to a base
        class, the base class destructor is called after the derived class destructor.
        LESSON.. EVEN THOUGH WE ARE TRYING TO MIMIC A C# INTERFACE, THIS IS NOT AN
        INTERFACE.. IT IS A CLASS. ALL CLASSES HAVE A DESTRUCTOR
*/
    //virtual because this will be overriden in derived classes
    virtual ~IDestroyableAnimal() {  cout << "IDestroyableAnimal Destructor called " << endl; }
};

class Janitor : public QObject {
    Q_OBJECT //this is a Macro. Macros are a feature of Qt.
    //Macros are placeholders for code that will be injected by the Qt MOC - Meta Object Compiler
    //No need to know what MOC is or do, just know that this is needed everytime you need to use
    //Qt advanced features like signals and slots
public slots:
    void HandleAnimalEvent(string name) {
        cout << name << " event handled by Janitor." << endl;
    }
};

//Animal defines pure virtual methods from IAnimal, therefore it is not abstract anymore and it can be instantiated
//but if you add single method as virtual and make it equals 0, it turns the class abstract.
class Animal : public QObject, public IAnimal {
    Q_OBJECT
private:
    string _name;
    //inline only available in C++ 17.
    //without inline you have to manually initialize the value of the variable
    //Check your version on CMakeLists.txt -> set(CMAKE_CXX_STANDARD 17)
    static inline int _numberOfAnimals = 0;

public:
    Animal(string name) : _name(name) {
        _numberOfAnimals++;
    }
    virtual ~Animal() {
        cout << "Destructor called for " << _name << endl;
        _numberOfAnimals--;
    }
    virtual void MakeSound() { cout << _name << " makes a sound." << endl; }
    virtual void Move() { cout << _name << " moves." << endl; }
    string GetName() { return _name; }
    void SetName(string name) { _name = name; }

    static void PrintActiveAnimals() { qInfo() << "Current active animals:" << _numberOfAnimals;}

    virtual void PrintClassType() //C# typeof(this).name;
    {
        // Using C++ typeid
        cout << _name << " is class type (C++): " << typeid(*this).name() << endl;

        // Using Qt's metaObject
        qInfo() << _name << " is class type (Qt):" << this->metaObject()->className();
    }
signals:
    void AnimalEvent(string name);
};

//You can define the methods here like Animal, or leave it to be defined in the .cpp file
class Dog : public Animal {
public:
    Dog(string name);
    void MakeSound() override;
    void Move() override;
};

class Cat : public Animal {
public:
    Cat(string name);
    void MakeSound() override;
    void Move() override;
};

class Horse : public IDestroyableAnimal {
private:
    string _name;
public:
    Horse(string name);
    virtual ~Horse() override {
        cout << "Destructor called for " << _name << endl;
    }
    void MakeSound() override;
    void Move() override;
};

void OOPExample();

#endif // OOP_H
