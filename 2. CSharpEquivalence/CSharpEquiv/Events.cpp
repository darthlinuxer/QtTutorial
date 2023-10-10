#include <QObject>
#include <QDebug>
#include <QVariant>
#include "Events.h"

template <typename T> void EventPublisher::TriggerEvent(const T &data) {
  QVariant variant = QVariant::fromValue(data);
  emit MyEvent(variant);
}

void EventSubscriber::OnMyEventReceived(const QVariant &data) {
  int value = data.value<int>();
  qDebug() << "Event received with value:" << value;
}

void EventExample(){
    EventPublisher publisher;
    EventSubscriber subscriber;

//    QObject::connect(&publisher, &EventPublisher::MyEvent,
//                     &subscriber, // Adding the context object here
//                     [&subscriber](const QVariant &data) {
//                       subscriber.OnMyEventReceived(data); // Specify the expected type here
//                     });

    QObject::connect(&publisher, &EventPublisher::MyEvent,
                     &subscriber,  &EventSubscriber::OnMyEventReceived);


    publisher.TriggerEvent<int>(42);  // Emit an int
}
