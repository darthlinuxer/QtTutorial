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

void CollectionExample() {
    // QList
    QList<int> list = {1, 2, 3};
    list.append(4);
    list.prepend(0);
    list.removeAt(0);
    qInfo() << "QList:" << list;

    // QVector
    QVector<int> vector = {1, 2, 3};
    vector.append(4);
    qInfo() << "QVector:" << vector;

    // QStack
    QStack<int> stack;
    stack.push(1);
    stack.pop();
    qInfo() << "QStack:" << stack;

    // QQueue
    QQueue<int> queue;
    queue.enqueue(1);
    queue.dequeue();
    qInfo() << "QQueue:" << queue;

    // QSet
    QSet<int> set = {1, 2, 3};
    set.insert(4);
    qInfo() << "QSet:" << set;

    // QMap
    QMap<QString, int> map;
    map.insert("one", 1);
    map.remove("one");
    qInfo() << "QMap:" << map;

    // QMultiMap
    QMultiMap<QString, int> multiMap;
    multiMap.insert("one", 1);
    multiMap.insert("one", 2);
    qInfo() << "QMultiMap:" << multiMap;

    // QHash
    QHash<QString, int> hash;
    hash.insert("one", 1);
    qInfo() << "QHash:" << hash;

    // QMultiHash
    QMultiHash<QString, int> multiHash;
    multiHash.insert("one", 1);
    multiHash.insert("one", 2);
    qInfo() << "QMultiHash:" << multiHash;

    // Readonly Collection
    const QList<int> constList = list;
    qInfo() << "Readonly QList:" << constList;
}
