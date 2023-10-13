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
    qInfo() << "\n------------- Static Cast examples are done at compile time------------------";
    Animal *animalPtr1 = new Animal("Animal");
    Animal *animalPtr2 = new Dog("Buster");
    qInfo()<< "Created animalPtr1 from Animal class at " << animalPtr1;
    qInfo()<< "Created animalPtr2 from Dog class at " << animalPtr2;
    Dog *staticcastedAnimal1 = static_cast<Dog*>(animalPtr1); // Will fail because animalPtr1 is not pointing to a Dog object
    Dog *staticcastedAnimal2 = static_cast<Dog*>(animalPtr2); // Will succeed because animalPtr2 is pointing to a Dog object
    //Car* staticcastedCar = static_cast<Car*>(animalPtr1); // Compiler won´t allow because of inheritance
    qInfo()<< "Created DOG staticcastedAnimal1 from animalPtr1 at " << staticcastedAnimal1;
    qInfo()<< "Created DOG staticcastedAnimal2 from animalPtr2 at " << staticcastedAnimal2;
    if (staticcastedAnimal1) {
        qInfo() << "Successfull Static Cast example converting animalPtr1 to staticcastAnimal1, but is this a DOG ???";
        staticcastedAnimal1->MakeSound();
    } else {
        qCritical() << "ERROR: Static Cast example converting animalPtr1 to staticcastAnimal1 FAILED!";
    }

    if (staticcastedAnimal2) {
        qInfo() << "Successfull Static Cast example converting animalPtr2 to staticcastAnimal2";
        staticcastedAnimal2->MakeSound();
    } else {
        qCritical() << "ERROR: Static Cast example converting animalPtr2 to staticcastAnimal2 FAILED!";
    }

    qInfo() << "\n------------- Dynamic Cast examples are done in runtime ------------------";
    Dog *dynamiccastedAnimal1 = dynamic_cast<Dog*>(animalPtr1); // Will fail because animalPtr1 is not pointing to a Dog object
    Dog *dynamiccastedAnimal2 = dynamic_cast<Dog*>(animalPtr2); // Will succeed because animalPtr2 is pointing to a Dog object
    Car* dynamiccastedCar = dynamic_cast<Car*>(animalPtr1); // Will fail because Car is not in the inheritance hierarchy of Animal
    qInfo()<< "Created DOG dynamiccastedAnimal1 from animalPtr1 at " << dynamiccastedAnimal1;
    qInfo()<< "Created DOG dynamiccastedAnimal2 from animalPtr2 at " << dynamiccastedAnimal2;
    qInfo()<< "Created CAR dynamiccastedCar from animalPtr1 at " << dynamiccastedCar;

    if (dynamiccastedAnimal1) {
        qInfo() << "Successfull Dynamic Cast example converting animalPtr1 to dynamiccastAnimal1";
        dynamiccastedAnimal1->MakeSound();
    } else {
        qCritical() << "ERROR: Dynamic Cast example converting animalPtr1 to dynamiccastAnimal1 FAILED!";
    }

    if (dynamiccastedAnimal2) {
        qInfo() << "Successfull Dynamic Cast example converting animalPtr2 to dynamiccastAnimal2";
        dynamiccastedAnimal2->MakeSound();
    } else {
        qCritical() << "ERROR: Dynamic Cast example converting animalPtr2 to dynamiccastAnimal2 FAILED!";
    }

    if (dynamiccastedCar) {
        dynamiccastedCar->makeSound();
    } else {
        qCritical() << "ERROR: Dynamic Cast: Dynamic cast Animal to Car failed.";
    }

    qInfo() << "\n------------- Explicit Cast examples can lead to undesirable effects  ------------------";
    qInfo("a) Type casting a pure animal object to a Dog!");
    Dog *snoopy = (Dog *)animalPtr1;
    qInfo()<< "Created Snoopy at " << snoopy << " from animalPtr1 at: " << animalPtr1;
    snoopy->MakeSound(); // this is totally unsafe.. animalPtr1 is purelly an
                         // Animal class

    qInfo("b) Type casting an animal object to a Car! WOW, HOW IS THAT ALLOWED ?");
    Car *ford = (Car *)animalPtr1;
    qInfo()<< "Created a Ford Car at " << ford << " from animalPtr1 at: " << animalPtr1;
    ford->makeSound();

    qInfo("c) Type casting an animal object created as dog but downgraded to a Dog!");
    Dog *buster = (Dog *)animalPtr2;
    qInfo()<< "Created Buster at " << buster << " from animalPtr2 at: " << animalPtr2;
    buster->MakeSound(); // normal box unbox in C# to downcast

    qInfo() << "DANGER: All typecasted successed because they all have MakeSound method...\n"
               "even though Car and Animal does not have any relation through inheritance, the cast worked\n"
               "NEVER USE EXPLICIT CAST UNLESS YOU ARE ABSOLUTELY SURE IT WILL WORK \n"
               "With static and dynamic you can check the result of the cast before using it";

    qInfo() << "\n------------- ReInterpret Cast examples  ------------------";
    int *intPointer = reinterpret_cast<int *>(animalPtr2);
    qInfo() << "Int Pointer: " << intPointer;
    qInfo() << "Animal Pointer: " << animalPtr1;
    Dog *dog = reinterpret_cast<Dog *>(intPointer);
    qInfo() << "Dog Pointer: " << animalPtr1 << " but, does it bark ?";
    dog->MakeSound();

    qInfo() << "\n------------- QObject Cast examples  ------------------";
    Dog* rex = new Dog("Rex");
    Animal* rexTheDog = qobject_cast<Animal*>(rex);
    qInfo() <<"Derived Class to Base class conversion -> Rex addr:"<<rex <<" Animal addr:"<<rexTheDog;
    rexTheDog->MakeSound();
    //rexTheDog->WagTail(); //this method does not exist on Animal pointer. If you uncomment compiler will not build
    Dog* rex2 = static_cast<Dog*>(rexTheDog);
    //Dog is not marked explicit as QObject , downcast will only work with static or dynamic cast
    qInfo() <<"Base Class to Derived class conversion -> Animal addr:"<<rexTheDog <<" Rex addr:"<<rex2;
    rex2->WagTail();


    qInfo() << "\n------------- CONCLUSION  ------------------";
    qInfo() << "Implicit cast -> C++ takes care of it";
    qInfo() << "Explicit cast -> we tell C++ what to do";
    qInfo() << "Static cast -> the operator does a nonpolymorphic cast";
    qInfo() << "Dynamic cast -> the operator will ensure inheritance is good";
    qInfo() << "Reinterpret cast -> the operator convert the type to a different type";
    qInfo() << "QObject cast -> work with QObjects and takes away a lot of the complexity";

    delete animalPtr1;
    delete animalPtr2;
    delete rex;
}
