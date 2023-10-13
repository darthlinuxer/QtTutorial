#include <QDebug>
#include <iostream>
#include "ErrorAndExceptions.h"

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
          throw std::runtime_error("Value should be greater than 0");
        if (value > 10)
          throw QString("Value should not be greater than 10");
        throw value;
      } catch (QString e) {
        qInfo() << "Caught a QString: " << e;
      } catch (int e) {
        qInfo() << "Caught an int: " << e;
      } catch (std::exception e) {
        qInfo() << "Caught an Exception: " << e.what();
      } catch (...) {
        qInfo() << "Caught something...";
      }
    } while (value != 1);
    qInfo() << "Ok, quitting and returning to the main menu";
}
