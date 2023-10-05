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


void OOPExample() {

    Animal::PrintActiveAnimals(); //static method;
    // Creates a DOG object on the HEAP.. which is UNMANAGED memory.
    Animal* snoopy = new Dog("Snoopy the Dog on the HEAP"); //Dog derives from abstract Animal which derives from IAnimal
    Janitor janitor;
    QObject::connect(snoopy, SIGNAL(AnimalEvent(string)), &janitor, SLOT(HandleAnimalEvent(string))); //Event
    snoopy->MakeSound();
    snoopy->Move();
    emit snoopy->AnimalEvent("Snoopy Pooped");
    snoopy->PrintActiveAnimals();
    snoopy->PrintClassType();
    delete snoopy; //Delete calls the Destructor. IAnimal does not have a destructor and that will be problematic
    Animal::PrintActiveAnimals();

    //Now things will be interesting.. it is possible to call the same methods of an object using pointers and refs
    Cat myCat("Tom the Cat on Stack"); //Just created a Cat on the Stack Memory.. which is managed C++ region.
    Animal* animalPtr = &myCat; // Created an Animal pointer to use it polymorphically
    Animal& animalRef = myCat; // References can be used with polymorphism too...
    //Previous defined Janitor is also subscribed to another animal
    QObject::connect(animalPtr, SIGNAL(AnimalEvent(string)), &janitor, SLOT(HandleAnimalEvent(string)));
    animalPtr->MakeSound(); //check how pointers are used to call internal methods
    animalRef.Move(); //check how references are used to call internal methods (Like C# using dot)
    emit animalPtr->AnimalEvent("Tom Pooped");
    emit animalRef.AnimalEvent("Tom Pooped again!");
    //delete animalPtr; // Compiler will allow you to do this but if you do program will crash on runtime
    //delete animalRef; // Compiler wont allow you do this.
    //The thing is: YOU DO NOT NEED TO DELETE MANAGED OBJECTS ON STACK
    //You should only use delete on pointers that point to objects allocated on the heap using new (check dog above)

    //IAnimal only have hidden non-virtual destructors like all classes
    IAnimal* myLeakyPet= new Cat("Whiskers the Cat on the HEAP"); //how can you destroy this animal ?
    myLeakyPet->MakeSound();
    myLeakyPet->Move();
    //the next delete command will crash the program in runtime if you uncomment and run.
    //delete myLeakyPet; //Compiler message: Delete called on 'IAnimal' that is abstract but has non-virtual destructor
    //myLeakyPet caused a memory leak because the destructor cannot be called.
    //to fix this you can to define a virtual ~IAnimal() {} on the IAnimal interface... then you can call delete .
    //This is how it is done in the IDestroyableAnimal Interface.. check below.

    //Horse derives from IDestroyableAnimal which derives from IAnimal
    IDestroyableAnimal* seaBiscuit = new Horse("Garfield the Horse on the HEAP");
    seaBiscuit->MakeSound();
    seaBiscuit->Move();
    delete seaBiscuit;

}
