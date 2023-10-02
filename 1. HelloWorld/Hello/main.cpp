#include <QCoreApplication>
#include <QDebug> //required for qInfo() command;
#include <iostream> //required for std::cout but not for std::printf
#include "Variables/VariablesInit.h"
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
    QCoreApplication a(argc, argv);

    std::printf("Hello World from Std Library using printf");
    std::cout << "\nHello World using another command from Std\t<<need to add iostream library>>" << std::endl;
    qInfo() << "Hello World using Q class... always use Q libraries instead of C++";
    qInfo() << "Now... Calling VariableInit method from another file";

    VariableInit(); //go inside this method to see how variables are defined
    VariableSizes();

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

    return a.exec();
}
