#include <QCoreApplication>
#include "PointersAndMemory.h"
#include "PropertiesAndEvents.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    PointersAndMemoryExample(a);
    PropertiesAndEventsExample(a);

    return a.exec();
}
