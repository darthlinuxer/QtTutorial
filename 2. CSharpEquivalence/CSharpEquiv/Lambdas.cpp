#include "Lambdas.h"
#include <QDebug>

void BasicLambdas() {
    // Anonymous Function
    auto func = []() { qDebug() << "Hello, world!"; };
    qInfo() << "Type of Anonymoys Function = " << typeid(func).name();
    func();

    // Lambda with 2 parameters
    auto lambda = [](int x, int y) { return x + y; };
    qInfo() << "Type of Lambda = " << typeid(lambda).name();
    qInfo() << "Calling Lambda(2,3) = " << lambda(2, 3);

    // Func with 2 parameters
    std::function<int(int, int)> add = [](int x, int y) { return x + y; };
    qInfo() << "Type of Func = " << typeid(add).name();
    qInfo() << "Calling Func add(2,3) = " << add(2, 3);

    // Action with 2 parameters
    std::function<void(int, int)> doSomething = [](int x, int y) {
        qInfo() << "Calling Action doSomething (2,3) have internal result = "
                << x + y;
    };
    qInfo() << "Type of Action = " << typeid(doSomething).name();
    doSomething(2,3);

    // Predicate
    auto is_even = [](int n) { return n % 2 == 0; };
    qInfo() << "Type of Predicate = " << typeid(is_even).name();
    qInfo() << "Is 2 Even ? " << is_even(2);
}
void LambdaWithParameters() {
    auto add = [](int a, int b) { return a + b; };
    int sum = add(5, 3);
    qInfo() << "Lambda With Parameters: " << sum;
}
void LambdaCapturingVariables() {
    int multiplier = 2;
    auto multiply = [multiplier](int a) { return a * multiplier; };
    int result = multiply(5);  // Result will be 10
    qInfo() << "Lambda Capturing Variables: " << result;
}
void ActionExample(std::function<void()> action) { action(); }
void ActionExampleWithTwo(std::function<void(int, int)> action, int x, int y) {
    action(x,y);
}
int FuncExampleWithTwo(std::function<int(int, int)> func, int x, int y) {
    return func(x,y);
}
