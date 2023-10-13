#include <QDebug>
#include <iostream>
#include "ErrorAndExceptions.h"

struct MyCustomError: public std::exception
{
    const char* description;
    const char* what() const noexcept
    {
        return "Oops! mycustomException happened! ";
    }
};

void ErrorAndExceptionsExample()
{
    QTextStream qin(stdin);
    QTextStream qout(stdout);
    int value = 0;
    do {
      try {
        std::cin.clear();
        qInfo() << "Type a number:";
        qin.flush();
        QString input = qin.readLine();
        value = input.toInt();
        if (value < 0)
          throw std::invalid_argument("Value should be greater than 0");
        if (value == 100) {
            MyCustomError e;
            e.description = "I guess you don't follow rules";
            throw e;
        }
        if (value > 10 and value < 20)
          throw QString("Value should not be greater than 10 and less than 20");
        if (value > 20)
          throw std::out_of_range("wow this is way out of range");

        throw value;
      } catch (QString e) {
        qInfo() << "Caught a QString: " << e;
      } catch (int e) {
        qInfo() << "Caught an int: " << e;
      } catch (MyCustomError const &e) {
        qInfo() << e.what() << " -> " << e.description;
      } catch (std::exception const &e) {
        qInfo() << "Caught a Generic Exception: " << e.what();
      } catch (...) {
        qInfo() << "Caught something...";
      }
    } while (value != 1);
    qInfo() << "Ok, quitting and returning to the main menu";
}
