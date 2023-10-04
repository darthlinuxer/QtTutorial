#include <QCoreApplication>
using namespace std;

void modifyValue(int *ptr) {
    *ptr = 10; // Modifies the value pointed to by ptr.
}

void modifyReference(int &ref) {
    ref = 20; // Modifies the value referred to by ref.
}

int* createIntOnHeap() {
    int* heapVar = new int; // Allocate an integer on the heap.
    *heapVar = 5; // Assign it a value.
    return heapVar; // Return the pointer.
}

int createIntOnStack() {
    int stackVar = 10; // Allocate an integer on the stack.
    return stackVar; // Return the value.
}

//Local created variables cannot outlive the method where it was created... but look createOnHeap
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
    // A variable is created to hold the memory address of another variable
    int *pointer = &x; // pointer points to the address of x.
    qDebug() << "int *pointer = &x. What is pointer value ? (points to the address of x) " << pointer;
    qDebug() << "What pointer points to ? (points to the value of x) " << *pointer;
    qDebug() << "What is pointer memory address ? " << &pointer;
    modifyValue(pointer);
    qDebug() << "After modifyValue x = :" << x;

    // References
    int &reference = x; // no reference variable is created.. under the hood is always x;
    qDebug() << "int &reference = x. What reference value ? (should be value of x)" << reference;
    qDebug() << "What is reference address ? (should be address of x)" << &reference;
    modifyReference(reference);
    qDebug() << "After modifyReference:" << x;

    qInfo() << "-----------------------------HEAP AND STACK ----------------------------------------";
    // Heap
    int* heapVar = createIntOnHeap();
    qDebug() << "Heap variable value:" << *heapVar;
    qDebug() << "Heap variable address:" << heapVar;

    // Stack
    int stackVar = createIntOnStack();
    qDebug() << "Stack variable value:" << stackVar;
    qDebug() << "Stack variable address:" << &stackVar;
    delete heapVar; // Don't forget to delete heap-allocated variables!

    auto o1 = createObjectOnHeap("OnHeap");
    qInfo() << o1;
    delete o1;

    //Compiler won´t let you assign the variable below due to scope
    //error: Call to deleted constructor of 'QObject' which has been explicitly marked deleted here
    //auto o2 = createObjectOnStack("OnStack");

    return a.exec();
}
