#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <QObject>
#include <QMetaObject>
#include <QMetaMethod>
#include "OOP.h"

using namespace std;

Dog::Dog(string name) : Animal(name) {}
void Dog::MakeSound() { cout << GetName() << " barks." << endl; }
void Dog::Move() {
    Animal::Move(); // Call the base class's Move method
    cout << GetName() << " runs." << endl;
}

Cat::Cat(string name) : Animal(name) {}
void Cat::MakeSound() { cout << GetName() << " meows." << endl; }
void Cat::Move() { cout << GetName() << " walks." << endl; }

/*
In C++, even pure virtual destructors need a definition.
This is because the destructor of the base class is always called when a derived object is destroyed.
When you delete an object through a pointer to a base class, the base class destructor is called after
the derived class destructor.
THEN.. EVEN THOUGH WE ARE TRYING TO MIMIC A C# INTERFACE, THIS IS NOT AN INTERFACE.. IT IS A CLASS
*/
IDestroyableAnimal::~IDestroyableAnimal() {
    cout << "BASE Destructor called " << endl;
}

Horse::Horse(string name) : _name(name) {}
void Horse::MakeSound() { cout << _name << " neighs." << endl; }
void Horse::Move() { cout << _name << " walks." << endl; }
Horse::~Horse() { cout << "Destructor called for " << _name << endl; }


void OOPExample() {
    Animal* myAnimal1 = new Dog("Fido"); //Dog derives from abstract Animal which derives from IAnimal
    Janitor janitor;
    QObject::connect(myAnimal1, SIGNAL(AnimalEvent(string)), &janitor, SLOT(HandleAnimalEvent(string))); //Event
    myAnimal1->MakeSound();
    myAnimal1->Move();
    emit myAnimal1->AnimalEvent("FIDO Pooped");
    delete myAnimal1; //Abstract classes have destructors, IAnimal does not have a destructor and that will be problematic

    Animal* myAnimal2 = new Cat("Tom");
    //Previous defined Janitor subscribed to another animal
    QObject::connect(myAnimal2, SIGNAL(AnimalEvent(string)), &janitor, SLOT(HandleAnimalEvent(string)));
    myAnimal2->MakeSound();
    myAnimal2->Move();
    emit myAnimal2->AnimalEvent("Tom Pooped");
    delete myAnimal2;

    IAnimal* myLeakyPet= new Cat("Whiskers"); //Now, how can you destroy this animal ?
    myLeakyPet->MakeSound();
    myLeakyPet->Move();
    //myLeakyPet caused a memory leak because the destructor cannot be called since it is not defined in the Interface

    IDestroyableAnimal* myPet2 = new Horse("Garfield"); //Horse derives from IAnimal
    myPet2->MakeSound();
    myPet2->Move();
    delete myPet2;

}
