#include <QCoreApplication>
#include <QDebug> //required for qInfo() command;
#include <iostream> //required for input output
#include "Variables/VariablesInit.h"
#include <QMetaEnum> //required for QMetaEnum command;
#include <thread> //required to delays
/*!
 This Summary is automatically generated if you type slash *!
 But yes, main is where everything starts!
 Check https://doxygen.nl/ to see how documentation can be created from these summaries
 * \brief main The Starting Point
 * \param argc The argument count
 * \param argv The arguments array
 * \return The exit value
 */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv); //this is automatically added with every new project

    std::string name; //variable definition
    qInfo("Hello, what's your name ?");
    std::cin >> name; //Reading from the terminal
    qInfo() << "Hello" << name;
    std::this_thread::sleep_for(std::chrono::seconds(1)); //Time Delay

    qInfo() << "There are multiple ways of printing to a console";
    std::printf("1.\tHello World from Std Library using printf\n");
    std::cout << "2.\tHello World using another command from Std <<need to add iostream library>>" << std::endl;
    qInfo() << "3.\tHello World using qInfo() class... always use Q libraries instead of C++. Why?";
    qDebug() << "Debug: With QLibraries you can intercept these messages later";
    qWarning() <<"Warning: Let´s say you want to log depending of the type of the message";
    qCritical() << "Critical: It is possible to intercept with Q libraries but not with cout";
    qCritical() << "Fatal: But never user qFatal() unless you really want program to crash";
    std::cout << std::endl;

    system("pause"); //from iostream library.
    system("cls"); //clears the screen

    qInfo() << "-----------------------Reading Methods from Other File -------------------------------";
    qInfo() << "Now... Calling VariableInit method from another file";
    VariableInit(); //go inside this method to see how variables are defined
    VariableSizes();

    system("pause"); //from iostream library.
    system("cls"); //clears the screen
    qInfo() << "-----------------------PASSING PARAMETERS -------------------------------";
    // Test sumInts
    int x = 5, y = 10;
    qInfo()  << "sumInts x=5, y=10: " << sumInts(x, y); //Basic way of passing parameters

    // Test sumPointers
    qInfo() << "sumPointers of x and y but x=x+1 " << sumPointers(&x, &y); //Go inside and see how the sum is made
    qInfo()  << "summing the modified Pointer of x: sumInts: " << sumInts(x, y); //This result will be different

    // Test sumArray
    int arr[] = {1, 2, 3, 4, 5};
    //get used to this: Sizeof the array is the entire array divided by the sizeof the first element
    qInfo() << "sumArray: " << sumArray(arr, sizeof(arr)/sizeof(arr[0]));

    // Testing Invoke
    qInfo() << "Passing a Multiply Function: " << Invoke(x,y, &multiplyInts);

    system("pause"); //from iostream library.
    system("cls"); //clears the screen
    qInfo() << "-------------------------ENUMS-----------------------------";
    int color = 0;
    qInfo() << "Choose number between 0..2";
    std::cin >> color;
    (color > 2 || color < 0)? qFatal("This range is invalid!") : qInfo("Valid Range.. go on...");
    MyCustomColorEnum myColor = static_cast<MyCustomColorEnum>(color);

    switch (myColor) {
    case 0:
      qInfo() << "You chose Red";
      break;
    case 1:
      qInfo() << "You chose Green";
      break;
    case 2:
      qInfo() << "You chose Blue";
      break;
    }

    qFatal("Intended crash....");

    return a.exec();
}
