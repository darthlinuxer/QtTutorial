#ifndef LAMBDAS_H
#define LAMBDAS_H

#include <functional>
void BasicLambdas();
void LambdaWithParameters();
void LambdaCapturingVariables();
void ActionExample(std::function<void()> action);
void ActionExampleWithTwo(std::function<void(int,int)> action);
int FuncExampleWithTwo(std::function<int(int,int)> func);

#endif // LAMBDAS_H
