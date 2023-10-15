#include <QCoreApplication>
#include <QObject>
#include <iostream>
#include "animal.h"
#include "dog.h"
#include "cat.h"
#include "zoo.h"
using namespace std;

class Person {
private:
    QString _name;

public:
    Person(QString name) : _name(name) { qInfo() << "Constructor: just created " << name;}
    ~Person() { qInfo() << "Destructor: just destroyed " << _name; }

    void SetName(QString name) { _name = name; }
    QString GetName() const { return _name; }

    //Equivalent to operator overload on C#. What this operator will do in conjunction with QDebug
    //is to create a similar of ToString() on C#..
    //Basically I am telling C++ how to print the object on the screen if I send it to one of the
    //QDebug classes like qInfo()
    //When a function or another class is declared as a friend of a class,
    //it can access the private and protected members of that class, even though it is not a member
    //of that class itself.
    friend QDebug operator<<(QDebug debug, const Person& person) {
        //Saves the settings used by QDebug, and restores them upon destruction
        QDebugStateSaver saver(debug);
        //The QDebugStateSaver ensures that this change is only temporary and does not affect other uses of
        //the QDebug object.
        debug.nospace() << "Person(Address: " << &person << ", Name: " << person.GetName() << ")";
        return debug;
    }

};

void modifyValue(int *ptr) {
    *ptr = 10; // Modifies the value pointed to by ptr.
}

void modifyReference(int &ref) {
    ref = 20; // Modifies the value referred to by ref.
}

int* createIntOnHeap() {
    int* heapVar = new int; // Allocate an integer on the heap. Always remember to delete the object after use
    *heapVar = 5; // Assign it a value.
    qDebug() << "Internal Heap variable value:" << *heapVar;
    qDebug() << "Internal Heap variable address:" << heapVar;
    return heapVar; // Return the pointer.
}

int createIntOnStack() {
    int stackVar = 10; // Allocate an integer on the stack. C++ manages that for us!
    qDebug() << "Internal Stack variable value:" << stackVar;
    qDebug() << "Internal Stack variable address:" << &stackVar;
    return stackVar; // Return the value.
}

//Local created variables cannot outlive the method where it was created..
//compiler will warn you try to reference it outside
Person createObjectOnStack(QString name) {
    Person stackObj(name); // Allocate a QObject on the stack. Don´t use new. C++ manages that for us!
    stackObj.SetName("aka Darth Linuxer on the Stack"); // hmm Method called like C#
    qDebug() << stackObj;
    return stackObj; // Return the object.
}

//everytime you use new, your are allocating on the Heap, not on the stack
Person* createObjectOnHeap(QString name) {
    Person* heapObj = new Person(name); // Allocate a QObject on the heap. We will have to manage this!
    heapObj->SetName("aka Darth Linuxer on the Heap"); //look how pointers reference internal methods using arrow ->
    qDebug() << *heapObj;
    return heapObj; // Return the pointer.. good luck managing its lifecycle now! MEMORY LEAK POTENTIAL
}


//Pointers and Addresses are interchangeable
//See on Main how we can send an address to this method instead of a pointer variable
void PrintMsg(QString *msg)
{
    qInfo() << "Inside method PrintMsg: msg variable received as pointer has this memory addr:" << msg << "  Size:" << msg -> length();
}

void AutoDeleteOnHeapDemonstration(){
    qInfo() << "USING SMART POINTERS:";
    //SMART POINTERS
    /*
     * Only one std::unique_ptr can point to a particular object.
     * When a std::unique_ptr goes out of scope or is explicitly reset, it automatically
     * deletes the object it points to.
     * Use Cases: It is suitable when you have a single, well-defined owner for the object,
     * and you want to transfer ownership or ensure that there are no multiple pointers trying
     * to manage the same object.
     * */
    unique_ptr<Person> p1 = std::make_unique<Person>("I am Unique");
    qDebug() << "UNIQUE pointer:" << *p1;
    unique_ptr<Person> p1a = std::move(p1);
    qDebug() << "MOVED a UNIQUE pointer:" << *p1a;
    //qDebug() << *p1; //Compiler will warn you p1 is null because pointer was moved

    /*
     * shared_ptr represents shared ownership of a dynamically allocated object.
     * It means multiple std::shared_ptr instances can point to the same object.
     * The object will be deleted only when the last std::shared_ptr pointing to it is destroyed or reset.
     * */
    shared_ptr<Person> p2 = std::make_shared<Person>("I am Shared");
    qDebug() << "p2: Shared pointer: " << *p2;
    qDebug() << "p2: Count number of pointers pointing to this object : " << p2.use_count(); //output 1

    shared_ptr<Person> p3(p2);
    qDebug() << "Action: Creating a p3 passing a p2";
    qDebug() << "p3: Shared pointer: " << *p3;
    qDebug() << "p3: Count number of pointers pointing to this object : " << p3.use_count(); //output 2
    qDebug() << "p2: Count number of pointers pointing to this object : " << p2.use_count(); //output 2

    shared_ptr<Person> p4 = std::move(p2);
    qDebug() << "Action: p2 was moved to p4!";
    qDebug() << "p2: Count number of pointers pointing to this object : " << (p2 ? p2.use_count() : 0); //output 0
    qDebug() << "p3: Count number of pointers pointing to this object : " << p3.use_count(); //output 2
    qDebug() << "p4: Count number of pointers pointing to this object : " << p4.use_count(); //output 2

    p3.reset();
    qDebug() << "Action: RESETed p3!";
    qDebug() << "p3: Count number of pointers pointing to this object : " << p3.use_count(); //output 2
    qDebug() << "p4: Count number of pointers pointing to this object : " << p4.use_count(); //output 2

}

void DemonstratingPersonOnStackBeingAutoDeletedByCPluPlus(){
    Person p2 = createObjectOnStack("Camilo OnStack"); // Receive a copy of the object
    qDebug() << "External Stack person : " << p2; // Use the copy
    //See how p2 does not need a delete like p1? objects on Stack are automatically managed by C++
    //and will be cleaned when the program stops using it.
}

void PointersAndMemoryExample(QCoreApplication& a)
{

    qInfo() << "------------------------POINTERS AND REFERENCES----------------------------------";
    int x = 5;
    qDebug() << "x = 5: What x holds ? " << x;
    qDebug() << "What is x address ? " << &x;

    // Pointers: A pointer is the holder of a memory address.
    // the pointer variable below is created to hold the memory address of the x variable
    int *pointer = &x; // pointer points to the address of x.
    qDebug() << "int *pointer = &x. What is the pointer value ? (points to the address of x) " << pointer;
    qDebug() << "What pointer points to ? (points to the value of x) " << *pointer;
    qDebug() << "What is pointer memory address ? " << &pointer;
    modifyValue(pointer);
    qDebug() << "After modifyValue x = :" << x; //so yes you can modify an external variable by pointer

    // References
    int &reference = x; // no reference variable is created.. under the hood is always x;
    qDebug() << "int &reference = x. What is reference value ? (should be value of x)" << reference;
    qDebug() << "What is reference address ? (should be address of x, because it is same as x)" << &reference;
    modifyReference(reference);
    qDebug() << "After modifyReference:" << x; //this is the same as byRef in C#

    //Pointer and Addresses are interchangeable. A pointer of something receives an adress of otherthings of the same type
    QString msg = "This is a message to test how an address can be sent to a Method expecting a pointer";
    qInfo() << "\nTesting how ADDRESS and POINTERS are interchangeable:";
    qInfo() << "You can send a variable address to any method expecting a Pointer if they are the same type";
    qInfo() << "Local Msg variable created on Stack has address: " << &msg << "  Size:" << msg.length();
    PrintMsg(&msg); //I am sending an adress to a method expecting a pointer.. it will compile;
    qInfo() << "Check how addresses are the same internally and externally of PrintMsg: " << &msg;
    qInfo() << "It is no different as if you first create the pointer and assigning it to variable address";
    QString *msgPtr = &msg;
    PrintMsg(msgPtr);

    qInfo() << "-----------------------------HEAP AND STACK ----------------------------------------";
    // Heap
    int* heapVar = createIntOnHeap();
    qDebug() << "External Heap variable value:" << *heapVar;
    qDebug() << "External Heap variable address:" << heapVar;

    // Stack
    int copiedstackVarValue = createIntOnStack();
    qDebug() << "External Stack variable value:" << copiedstackVarValue;
    qDebug() << "External Stack variable address:" << &copiedstackVarValue;
    delete heapVar; // Don't forget to delete heap-allocated variables!

    qInfo()<<"---------------NOW HEAP and STACK using Person Object--------------";

    // Heap
    Person* p1 = createObjectOnHeap("Camilo OnHeap");
    qDebug() << "External Heap person : " << *p1; // Use pointer directly
    delete p1;
    //qInfo() << p1->GetName(); //Compiler will allow you to do this but p1 is a dangling pointer now.. points to nothing

    // Stack
    DemonstratingPersonOnStackBeingAutoDeletedByCPluPlus();
    //The scope of this function will end here.. C++ will clean the stack
    //See on the logs the call to Destructor: just destroyed  "aka Darth Linuxer on the Stack"...
    //nobody called that.. c++ did .

    qInfo()
        << "Note: \n"
           "a) Heap Person was expected to have the same memory address but Stack no!\n"
           "b) Check the addresses of the Stack Person inside and outside: Why are they the same ? \n"
           "- if values are passed by value, C++ is making a copy how address can be the same?\n\n"
           "Explanation: \n"
           "In C++, when you return an object by value, the compiler often optimizes away "
           "the actual copy operation, a technique known as Return Value Optimization (RVO). "
           "This is a standard compiler optimization to avoid the overhead of copying an object"
           "from the function's stack frame to the calling function's stack frame. Instead, the compiler"
           " constructs the object directly in the memory location where it will "
           "be used by the calling function. In this case, stackObj is constructed directly in the memory "
           "location for p2, so they end up having the same address. This is why you see the same address for both "
           "stackObj and p2. This is an optimization, and according to the C++ standard, the "
           "compiler is allowed to perform this as long as the program's observable behavior remains unchanged (the "
           "as-if rule).";

    qInfo() << "-----------------------AUTOMATIC MEMORY MANAGEMENT----------------------";
    qInfo() << "Sure C++ have advanced methods to clean objects allocated on the HEAP when they are not used anymore";
    AutoDeleteOnHeapDemonstration();

    qInfo() << "-------------------AUTOMATICALLY CLEANING LINKED OBJECTS------------------";

    Zoo* zoo = new Zoo(&a); //&a is defined on line 92.. it is this Qt app lifecycle that is now linked to zoo.
    Dog* dog = new Dog("Snoopy", zoo); //if zoo is destroyed, bye bye Snoopy as well.
    dog->MakeSound();
    Cat* cat = new Cat("Garfield", zoo);
    cat->MakeSound();
    zoo->AddAnimal(dog);
    zoo->AddAnimal(cat);
    for(Animal* animal : zoo->GetAnimals())
    {
        animal->Walk();
    }
    delete zoo;
    //Now even if you forget to delete zoo, because zoo was created with a pointer to &a which is this
    //Qt application defined on line 92:    QCoreApplication a(argc, argv);
    //when a is destroyed everything is destroyed..
    //Lesson: When doing compositions, always link the parents... so that when the parent is deleted
    //all linked components will be deleted as well.
}
