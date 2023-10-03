#include "Lambdas.h"
#include <QDebug>

void MethodWithoutParameters(){
    qInfo()<< "Hello from Method Without Parameters";
}

void AddInternally(int x, int y){
    qInfo() << "AddInternally(x+y) = " << x+y;
}

int Add(int x, int y){
    return x+y;
}

void PrintMessage(std::string message){
    qInfo() << message;
}

//What is an Action ? It is a variable which can point to a Method with no Params
template<typename T> std::function<void(T)> actionDelegate;

//what is a Func? It is a variable which can point to Method that returns a Value
template <typename T, typename U> std::function<U(T, T)> funcDelegate;



void LambdaCapturingVariables() {
    int multiplier = 2;
    auto multiply = [multiplier](int a) { return a * multiplier; }; //auto: you let the compiler decide the type
    int result = multiply(5);  // Result will be 10
    qInfo() << "Lambda Capturing Variables: " << result;
}
void PassingActionAsParameter(std::function<void()> action) { action(); }
void PassingActionWith2ArgsAsParam(std::function<void(int, int)> action, int x, int y) {
    action(x,y);
}
int PassingFuncAsParam(std::function<int(int, int)> func, int x, int y) {
    return func(x,y);
}

void BasicLambdas() {
    // Anonymous Function
    auto lambdavoid = []() { qDebug() << "Hello, world!"; }; //auto: you let the compiler decide the type
    qInfo() << "Type of Anonymoys Function = " << typeid(lambdavoid).name();
    lambdavoid();

    // Lambda with 2 parameters
    auto lambdawith2 = [](int x, int y) { return x + y; }; //auto: you let the compiler decide the type
    qInfo() << "Type of Lambda = " << typeid(lambdawith2).name();
    qInfo() << "Calling Lambda(2,3) = " << lambdawith2(2, 3);

    // typed Lambda that returns a result with 2 parameters
    std::function<int(int, int)> add = [](int x, int y) { return x + y; };
    qInfo() << "Type of Func = " << typeid(add).name(); //same as typeof in C#
    qInfo() << "Calling Func add(2,3) = " << add(2, 3);

    // Lambda with 2 parameters that do not return a result. Same as lambdavoid above
    std::function<void(int, int)> doSomething = [](int x, int y) {
        qInfo() << "Calling Action doSomething (2,3) have internal result = " << x + y;
    };
    qInfo() << "Type of Action = " << typeid(doSomething).name();
    doSomething(2,3);

    // Lambda Predicate
    auto is_even = [](int n) { return n % 2 == 0; };
    qInfo() << "Type of Predicate = " << typeid(is_even).name();
    qInfo() << "Is 2 Even ? " << is_even(2);
}

void LambdaExamples(){

    qInfo()<< "============================Lambdas , Actions, Funcs, Delegates ============================";
    BasicLambdas();
    LambdaCapturingVariables();
    PassingActionAsParameter(MethodWithoutParameters);
    PassingActionWith2ArgsAsParam(AddInternally, 2, 3);
    int result = PassingFuncAsParam(Add, 1, 2);
    qInfo() << "Result of PassingFuncAsParam(Add,1,2) = " << result;

    //Generic Delegate with one parameter
    actionDelegate<std::string> = PrintMessage;
    actionDelegate<std::string>("Hello World!");

    //Generic Delegate with 2 parameters
    funcDelegate<int,int> = Add;
    qInfo() << "Func result: " << funcDelegate<int, int>(2,3);
}

