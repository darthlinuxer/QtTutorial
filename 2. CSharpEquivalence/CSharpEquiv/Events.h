#ifndef EVENTS_H
#define EVENTS_H


#include <QObject>
#include <QDebug>
#include <QVariant>

class EventPublisher : public QObject {
    Q_OBJECT
public:
    template<typename T>
    void TriggerEvent(const T& data);
signals:
    void MyEvent(const QVariant& data);
};

class EventSubscriber : public QObject {
    Q_OBJECT
public slots:
    void OnMyEventReceived(const QVariant& data);
};

void EventExample();

#endif // EVENTS_H
