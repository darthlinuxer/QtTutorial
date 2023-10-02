#include <QCoreApplication>
#include "Lambdas.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    BasicLambdas();
    LambdaWithParameters();
    LambdaCapturingVariables();
    ActionExample([]() { qInfo() << "Hello from Action without parameters!"; });
    ActionExampleWithTwo([](int x, int y) {
      qInfo() << "Hello from Action with 2 parameters: " << x + y;
    });

    int result = FuncExampleWithTwo([](int x, int y) { return x + y; });
    qInfo() << "Func result was:" << result;
    return a.exec();
}

