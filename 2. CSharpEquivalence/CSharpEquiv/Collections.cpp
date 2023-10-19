#include <QList>
#include <QVector>
#include <QStack>
#include <QQueue>
#include <QSet>
#include <QMap>
#include <QMultiMap>
#include <QHash>
#include <QMultiHash>
#include <QDebug>
#include "Collections.h"
#include "qobject.h"
#include <QRandomGenerator>

class MyClass {
public:
  MyClass() {
    qInfo() << "An Object of type MyClass was created at : " << this;
  }
  ~MyClass() {
    qInfo() << "An Object of type MyClass was destroyed at : " << this;
  }
};

void CollectionExample() {
    // QList
    qInfo() << "===================   QList =====================================";
    QList<int> list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    list.append(11);
    list << 12 << 13 << 14 << 15 << 16 << 16 << 16;
    list.prepend(0);
    qInfo() << list;
    qInfo() << "length, size, and count, are the same: " << list.length() << " "<< list.size() << " " << list.count();
    qInfo() << "But count can be used to count a specific item in the list: counting 16:" << list.count(16);
    list.removeAt(0);
    list.remove(16); //remove a single 16
    list.removeAll(16); //remove all 16
    list.replace(15,99);
    qInfo() << "removed one of the 0's at position 0, removed all 16, and replaced 15 by 99 \n" << list;
    qInfo() << "At position 2 get 5 items inclusive: " << list.sliced(2,5);
    std::function<bool(int)> predicate1 =  [](int value){ return value > 3; };
    list.removeIf(predicate1);
    qInfo() << "Removed all values above 3 ->" << list;
    list.clear();
    qInfo() << "Cleared list: " << list.length() << " "<< list.size() << " " << list.count();

    list.reserve(10); //attempts to allocate memory to this number of elements
    for(int i=0;i<10;i++) {list.push_front(QRandomGenerator::global()->bounded(1000));}

    qInfo() << "Unsorted List: " << list;
    std::sort(list.begin(), list.end());
    qInfo() << "Sorted List: " << list;
    std::reverse(list.begin(), list.end());
    qInfo() << "Reverse List: " << list;

    // Readonly Collection
    const QList<int> constList = list;
    qInfo() << "Readonly QList:" << constList;
    qInfo() << "IsEqual reverse and readonly ?" << std::equal(list.begin(), list.end(), constList.begin());

    //Copying
    QList<int> list2;
    list2.resize(list.size());
    std::copy(list.begin(), list.end(), list2.begin());
    qInfo() << "IsEqual list and its copy ?" << std::equal(list.begin(), list.end(), list2.begin());

    // QVector
    qInfo() << "===================   QVector is the same as QList ===========================";
    QVector<int> vector;
    vector << 1 << 2 << 3 << 4 << 5;
    qInfo() << "QVector:" << vector;
    for(int &value : vector) { value *= 2; }
    qInfo() << "Transformed QVector:" << vector;

    // QSet
    qInfo() << "===================   QStringList inherits from QList ============";
    QStringList strings = {"Camilo","was","here"};
    qInfo() << strings ;
    strings.replaceInStrings("a","@");
    strings.sort();
    qInfo() << "Replace all a's for @ and sorted: " << strings ;
    QString text = strings.join(" ");
    qInfo() << text;
    qInfo() << "Filtered all words with C:" << strings.filter("C");
    qInfo() << "Does it contain C@milo ? " << strings.contains("C@milo");
    qInfo() <<" Position: " << strings.indexOf("C@milo");
    qInfo() <<" Value: " << strings.at(strings.indexOf("C@milo"));

    qInfo() << "===================   QList with with OBJECTS ================";
    QList<MyClass*> list3 = {new MyClass, new MyClass};
    qInfo() << "List of MyClass objs: Action: Just created : count : " << list3.count();
    qDeleteAll(list3);
    qInfo() << "List of MyClass objs: Action: after qDeleteAll : count : " << list3.count();
    list3.clear();
    qInfo() << "List of MyClass objs: Action: after clear the list: count() : " << list3.count();

    qInfo() << "===================   QList with QSharedPointer to deal with OBJECTS ================";
    QList<QSharedPointer<MyClass>> list4 = {QSharedPointer<MyClass>(), QSharedPointer<MyClass>()};
    qInfo() << "List of SharedPointers of MyClass objs: Action: Just created : count : " << list4.count();
    list4.clear();
    qInfo() << "List of SharedPointers of MyClass objs: Action: after clear the list: count() : " << list4.count();

    // QStack
    qInfo() << "===================   QStack =====================================";
    QStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.pop();
    qInfo() << "QStack:" << stack;

    // QQueue
    qInfo() << "===================   QQueue =====================================";
    QQueue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.dequeue();
    qInfo() << "QQueue:" << queue;

    // QSet
    qInfo() << "===================   QSets are very fast because they make a hash under the hood ============";
    QSet<QString> set = {"Camilo","was","here"};
    qInfo() << set ;
    qInfo() << "Does it contain camilo ? " << set.contains("Camilo");
    set << "again";
    set << "Camilo"; //this will not be added because it is already in the Set
    qInfo() << "Does this order make sense? " << set;
    qInfo() << "Sets order things according to its internal hash";
    set.insert("2023"); //it will add where it wants.. not necessarily in the beginning or the end
    qInfo() << "Added 2023: " << set;

    // QMap = Dictionary in C#
    qInfo() << "===================   QMap =====================================";
    QMap<QString, int> map = {{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}};
    map.insert("six",6);
    //Unlike C# you can add a key that does not exist simply by setting it
    map["seven"]=7;

    std::function<bool(const QString&, int&)> predicate2 =  [](const QString& key, int& value){ return value < 3; };
    //PREDICATE ABOVE EVEN THOUGH CORRECTLY DEFINED DIDN´T WORK.. WILL SEARCH FOR A SOLUTION
    //map.removeIf(predicate2);
    qInfo() << "QMap:" << map;
    foreach(QString key, map.keys())
    {
        qInfo() << "key:" << key << "  value:"<< map.value(key);
    }

    //QMap with Objects
    qInfo() << "===================   QMap with OBJECTS =====================================";
    //You will have to manually take care of the pointers
    QMap<int,QObject*> map2 = {{1, new QObject}, {2, new QObject}};
    qInfo() << "map object counter: " << map2.count();
    qDeleteAll(map2); // calls Delete C++ operator on all pointers in the list
    qInfo() << "qDeleteAll: map2 object counter: " << map2.count(); // count is still 2 why ?
    // Accessing deleted pointers (dangling pointers)
    // qInfo() <<  map2.value(1); // undefined behavior : this might crash the program
    // delete map2.value(1); // crash or undefined behavior // Double deletion
    map2.clear();
    qInfo() << "Clear: map2 object counter: " << map2.count();

    // QMultiMap
    qInfo() << "===================   QMultiMap =====================================";
    QMultiMap<QString, int> multiMap;
    multiMap.insert("one", 1);
    multiMap.insert("one", 2);
    qInfo() << "QMultiMap:" << multiMap;

    // QHash
    qInfo() << "===================   QHash =====================================";
    QHash<QString, int> hash = {{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}};
    //hash.removeIf(predicate2);
    qInfo() << "QHash:" << hash;

    // QMultiHash
    qInfo() << "===================   QMultiHash =====================================";
    QMultiHash<QString, int> multiHash;
    multiHash.insert("one", 1);
    multiHash.insert("one", 2);
    qInfo() << "QMultiHash:" << multiHash;

}
