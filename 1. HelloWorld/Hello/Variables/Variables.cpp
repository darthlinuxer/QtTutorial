#include "VariablesInit.h"
#include <iostream>
#include <QVariant> //required for QVariant command;
#include <QDebug> //required for qInfo() command/;

void VariableInit(){

    qInfo() << "--------------Variables -----------------------";
    int x = 10, alpha = 2, beta = 3; //multiple variable definition in one line
    float y=10.2f;
    double c = 10.4;
    bool b = true;
    char z = 'a';

    qInfo() << "int x + alpha + beta = " << x + alpha + beta;
    qInfo() << "Typecasting float to int: y = " << (int)y; //typecasting like C#
    qInfo() << "Typecasting using lib: y = " << static_cast<int>(y); //typecasting not quite like C#
    qInfo() << "TypeCasting using Qt command: string b = " << QVariant(b).toString(); //typecasting use Qt command
    qInfo() << "Ternary operator: b = " << ((b) ? "true" : "false"); //ternary operator like C#
    qInfo() << "Summing different types: int x+ float y+ char z = "
            << x + b + z; // yes you can sum different types if these type can
        // be automatically converted to each other
}

void VariableSizes(){
    qInfo() << "Size of char : " << sizeof(char) << " byte";
    qInfo() << "char minimum value: " << CHAR_MIN ;
    qInfo() << "char maximum value: " << CHAR_MAX ;
    qInfo() << "Size of int : " << sizeof(int) << " bytes";
    qInfo() << "Size of signed long int : " << sizeof(signed long int) << " bytes";
    qInfo() << "Size of signed short int : " << sizeof(signed short int) << " bytes";
    qInfo() << "Size of unsigned long int : " << sizeof(unsigned long int) << " bytes";
    qInfo() << "Size of unsigned short int : " << sizeof(unsigned short int) << " bytes";
    qInfo() << "signed int minimum value: " << INT_MIN ;
    qInfo() << "signed int maximum value: " << INT_MAX ;
    qInfo() << "char maximum value: " << CHAR_MAX ;
    qInfo() << "Size of float : " << sizeof(float) << " bytes";
    qInfo() << "Size of double : " << sizeof(double) << " bytes";
    qInfo() << "Size of wchar_t : " << sizeof(wchar_t) << " bytes";
}

int sumInts(int a, int b) {
    a = a+1; //nothing happens externally
    return a + b;
}

int multiplyInts(int a, int b){
    return a*b;
}

int sumPointers(int* a, int* b) {
    *a = *a+1; //a will change externally
    return *a + *b;
}

int sumArray(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

int Invoke(int x, int y, int (*func)(int, int)) {
    return func(x, y);
}
