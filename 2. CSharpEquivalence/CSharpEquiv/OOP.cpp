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

Horse::Horse(string name) : _name(name) {}
void Horse::MakeSound() { cout << _name << " neighs." << endl; }
void Horse::Move() { cout << _name << " walks." << endl; }
Horse::~Horse() { cout << "Destructor called for " << _name << endl; }


void OOPExample() {

    // Creates a DOG object on the HEAP
    Animal* myAnimal1 = new Dog("Fido"); //Dog derives from abstract Animal which derives from IAnimal
    Janitor janitor;
    QObject::connect(myAnimal1, SIGNAL(AnimalEvent(string)), &janitor, SLOT(HandleAnimalEvent(string))); //Event
    myAnimal1->MakeSound();
    myAnimal1->Move();
    emit myAnimal1->AnimalEvent("FIDO Pooped");
    delete myAnimal1; //Abstract classes have destructors, IAnimal does not have a destructor and that will be problematic

    //Now things will be interesting.. it is possible to call the same methods of an object using pointers and refs
    // Create a Cat object on the stack
    Cat myCat("Tom"); //Just created a Cat on the Stack Memory.. which is managed C++ region.
    Animal* animalPtr = &myCat; // Created a pointer to use it polymorphically through a pointer to Animal
    Animal& animalRef = myCat; // References can be used with polymorphism too...
    //Previous defined Janitor subscribed to another animal
    QObject::connect(animalPtr, SIGNAL(AnimalEvent(string)), &janitor, SLOT(HandleAnimalEvent(string)));
    animalPtr->MakeSound(); //check how pointers are used to call internal methods
    animalRef.Move(); //check how references are used to call internal methods
    emit animalPtr->AnimalEvent("Tom Pooped");
    //delete animalPtr; // Compiler will allow you to do this but if you do program will crash on runtime
    //delete animalRef; // Compiler wont allow you do this.
    //The thing is: YOU DO NOT NEED TO DELETE MANAGED OBJECTS ON STACK
    //You should only use delete on pointers that point to objects allocated on the heap using new

    IAnimal* myLeakyPet= new Cat("Whiskers"); //Now, how can you destroy this animal ?
    myLeakyPet->MakeSound();
    myLeakyPet->Move();
    //myLeakyPet caused a memory leak because the destructor cannot be called since it is not defined in the Interface

    IDestroyableAnimal* myPet2 = new Horse("Garfield"); //Horse derives from IAnimal
    myPet2->MakeSound();
    myPet2->Move();
    delete myPet2;

}
