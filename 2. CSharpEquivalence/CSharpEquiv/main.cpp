#include <QThread>
#include "Lambdas.h"
#include <QCoreApplication>
#include <iostream>
#include <string>
#include <QTimer>

void PrintMenu(){
    QTextStream qin(stdin);
    QTextStream qout(stdout);
    QString menu = "\n Menu: "
                  "\n 0. Exit "
                  "\n 1. Process Lambdas, Actions and Funcs"
                  "\n 2. Process Events"
                  "\n 3. Tuples"
                  "\n 4. Interfaces"
                  "\n 5. Linq"
                  "\n 6. Async Await"
                  "\n 7. Extension Methods"
                  "\n 8. Try Catch and Exception Handling"
                  "\n 9. Reflection"
                  "\n 10. Attributes"
                  "\n Enter your Choice: \n";
    qout << menu;
    qout.flush();
}

void readInput() {
    QTextStream qin(stdin);
    QTextStream qout(stdout);
    int choice=0;
    do {
      system("cls");
      PrintMenu();
      QString input = qin.readLine();
      choice = input.toInt();
      qout << "Chosen option: " << choice;
      switch (choice) {
      case 0:
        QCoreApplication::quit();
        break;
      case 1:
        LambdaExamples();
        break;
      }
    } while (choice != 0);
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    //wanna see how a timer works ?
    QTimer::singleShot(1000, &a, [](){ //miliseconds, context, lambda function
        readInput();
    });
    return a.exec();
}
