#ifndef VARIABLESINIT_H
#define VARIABLESINIT_H

void VariableInit();
void VariableSizes();
int sumInts(int a, int b);
int multiplyInts(int a, int b);
int sumPointers(int *a, int *b);
int sumArray(int arr[], int size);
int Invoke(int x, int y, int (*func)(int, int));

enum MyCustomColorEnum { red, green, blue };

#endif // VARIABLESINIT_H
