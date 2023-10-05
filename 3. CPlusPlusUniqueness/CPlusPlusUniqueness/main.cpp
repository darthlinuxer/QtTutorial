#include <QCoreApplication>
using namespace std;

class Person {
private:
    QString _name;

public:
    Person(QString name) : _name(name) {}
    void SetName(QString name) { _name = name; }
    QString GetName() const { return _name; }

    // Overload the << operator for QDebug for stack-allocated objects
    friend QDebug operator<<(QDebug debug, const Person& person) {
        QDebugStateSaver saver(debug);
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

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

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

    // Stack
    Person p2 = createObjectOnStack("Camilo OnStack"); // Receive a copy of the object
    qDebug() << "External Stack person : " << p2; // Use the copy

    qInfo() << "\nHeap Person was expected to have the same memory address but Stack no!"
               "\nCheck the addresses of the Stack Person inside and "
               "outside: Why are they the same ? \n\n";
    QString explanation =
        "In C++, when you return an object by value, the compiler often optimizes away "
        "the actual copy operation, a technique known as Return Value Optimization (RVO). "
        "This is a standard compiler optimization to avoid the overhead of copying an object"
        "from the function's stack frame to the calling function's stack frame. Instead, the compiler"
        " constructs the object directly in the memory location where it will "
        "be used by the calling function."
        "In this case, stackObj is constructed directly in the memory location "
        "for p2, so they end up having the"
        "same address. This is why you see the same address for both stackObj and p2."
        " This is an optimization, and according to the C++ standard, the "
        "compiler is allowed to perform this as"
        "long as the program's observable behavior remains unchanged (the as-if rule).";
    qInfo() << explanation;
    return a.exec();
}
