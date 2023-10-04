#include <QCoreApplication>
using namespace std;

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
QObject& createObjectOnStack(string name) {
    QObject stackObj; // Allocate a QObject on the stack. C++ manages that for us!
    stackObj.setObjectName(name);
    return stackObj; // Return the object.
}

//everytime you use new, your are allocating on the Heap, not on the stack
QObject* createObjectOnHeap(string name) {
    QObject* heapObj = new QObject; // Allocate a QObject on the heap. We will have to manage this!
    heapObj->setObjectName(name);
    return heapObj; // Return the pointer.
    //you created an object and return a pointer to it.. good luck managing its lifecycle now!
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

    auto o1 = createObjectOnHeap("OnHeap");
    qInfo() << o1;
    delete o1;

    //Compiler won´t let you assign the variable below due to scope
    //error: Call to deleted constructor of 'QObject' which has been explicitly marked deleted here
    //auto o2 = createObjectOnStack("OnStack");

    return a.exec();
}
