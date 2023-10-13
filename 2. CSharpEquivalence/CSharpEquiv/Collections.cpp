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

void CollectionExample() {
    // QList
    qInfo() << "===================   QList =====================================";
    QList<int> list = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    list.append(11);
    list.prepend(0);
    list.removeAt(0);
    std::function<bool(int)> predicate1 =  [](int value){ return value > 3; };
    list.removeIf(predicate1);
    qInfo() << "Filtered QList:" << list;

    // Readonly Collection
    const QList<int> constList = list;
    qInfo() << "Readonly QList:" << constList;

    // QVector
    qInfo() << "===================   QVector =====================================";
    QVector<int> vector = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector.append(11);
    qInfo() << "QVector:" << vector;
    for(int &value : vector) { value *= 2; }
    qInfo() << "Transformed QVector:" << vector;

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
    qInfo() << "===================   QSet =====================================";
    QSet<int> set = {20, 1, 5, 2, 3, 4, 5, 5, 5, 5, 6, 7, 7, 8, 8, 9, 9, 10};
    set.removeIf(predicate1);
    qInfo() << "QSet:" << set;

    // QMap = Dictionary in C#
    qInfo() << "===================   QMap =====================================";
    QMap<QString, int> map = {{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}};
    map.insert("six",6);
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
    qDeleteAll(map2); // Deleting pointers
    qInfo() << "qDeleteAll: map2 object counter: " << map2.count(); // count is still 2
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
