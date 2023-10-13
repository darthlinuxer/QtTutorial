#include <QDebug>
#include "Casting.h"
#include "OOP.h"

void RunCastingExamples()
{
    qInfo() << "------------------------------CASTING----------------------------------";
    double x = 5.75;
    int y = x;
    qInfo() << "Implicit Casting: Double x = " << x << " -> int y = x = " << y; //With implicit C++ is managing the conversion
    qInfo() << "Explicit Casting: y = (int)x =  "<< (int)x; //With explicit if there is an impossible conversion C++ compiler will inform

    //dynamic_cast<> is particularly useful in polymorphic scenarios where you need to ensure type safety during downcasting
    Animal *animalPtr1 = new Animal("Animal");
    Animal *animalPtr2 = new Dog("Buster");
    qInfo()<< "Created animalPtr1 at " << animalPtr1;
    qInfo()<< "Created animalPtr2 at " << animalPtr2;
    qInfo() << "------------- Dynamic Cast examples ------------------";
    Dog *castedAnimal1 = dynamic_cast<Dog*>(animalPtr1); // Will fail because animalPtr1 is not pointing to a Dog object
    Dog *castedAnimal2 = dynamic_cast<Dog*>(animalPtr2); // Will succeed because animalPtr2 is pointing to a Dog object
    Car* castedCar = dynamic_cast<Car*>(animalPtr1); // Will fail because Car is not in the inheritance hierarchy of Animal
    qInfo()<< "Created castedAnimal1 at " << castedAnimal1;
    qInfo()<< "Created castedAnimal2 at " << castedAnimal2;
    qInfo()<< "Created castedCar at " << castedCar;



    if (castedAnimal1) {
        castedAnimal1->MakeSound();
    } else {
        qInfo() << "Dynamic Cast: Dynamic cast Animal to Dog failed.";
    }

    if (castedAnimal2) {
        qInfo() << "Successfull Dynamic Cast example:";
        castedAnimal2->MakeSound();
    } else {
        qInfo() << "Dynamic Cast: Dynamic cast Animal to Dog failed.";
    }

    if (castedCar) {
        castedCar->makeSound();
    } else {
        qInfo() << "Dynamic Cast: Dynamic cast Animal to Car failed.";
    }

    qInfo() << "But do you need dynamic cast for downcasting ? ";
    qInfo("Type casting a pure animal object to a Dog!");
    Dog *snoopy = (Dog *)animalPtr1;
    qInfo()<< "Created Snoopy at " << snoopy << " from animalPtr1 at: " << animalPtr1;
    snoopy->MakeSound(); // this is totally unsafe.. animalPtr1 is purelly an
                         // Animal class

    qInfo("Type casting an animal object to a Car!");
    Car *ford = (Car *)animalPtr1;
    qInfo()<< "Created a Ford Car at " << ford << " from animalPtr1 at: " << animalPtr1;
    ford->makeSound();

    qInfo("Type casting an animal object created as dog but downgraded to a Dog!");
    Dog *buster = (Dog *)animalPtr2;
    qInfo()<< "Created Buster at " << buster << " from animalPtr2 at: " << animalPtr2;
    buster->MakeSound(); // normal box unbox in C# to downcast


    qInfo() << "All typecasted successed because they all have MakeSound method.. even though Car and Animal "
               "does not have relation at all through inheritance";

    delete animalPtr1;
    delete animalPtr2;
}
