#include <QDebug>
#include "Generics.h"
#include <QObject>

template<class T> void CopyAndPrint(T value) {
    qInfo() << "Copy and Print: " << typeid(T).name() << " value: " << value << " addr:" << &value;
}

template<class T> void Print(const T& value) {
    qInfo() << "Print: " << typeid(T).name() << " value: " << value << " addr:" << &value;
}

template <class T, class U>
class TemplatedCalculator {
public:
  T Add(T a, U b) { return a + b; }
};

void GenericsExample()
{
  int i = 1;
  double pi = 3.1415;
  QString hello = "Hello World";
  QObject object;
  object.setObjectName("Object 1");

  qInfo() << " int addr:" << &i
          << " double addr:" << &pi
          << " text addr:" << &hello
          << " object addr: " << &object;
  CopyAndPrint<int>(i);
  CopyAndPrint<double>(pi);
  CopyAndPrint<QString>(hello);
  //CopyAndPrint<QObject>(object); //it will not compile if you uncomment because QObjects cannot be copied
  Print<int>(i);
  Print<double>(pi);
  Print<QString>(hello);
  Print<QObject*>(&object); //QObjects cannot be copied so you need to pass its address);

  qInfo() << "\n=============TEMPLATE CLASSES====================";

  TemplatedCalculator<int,int> intCalc;
  TemplatedCalculator<double, int>doubleCalc;
  TemplatedCalculator<QString, QString> stringCalc;
  qInfo() << intCalc.Add(1,2);
  qInfo() << doubleCalc.Add(1.2,2.5);
  qInfo() << stringCalc.Add("Hello"," World!");

}
