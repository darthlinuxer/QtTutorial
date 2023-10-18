#ifndef QDATASTREAMEXAMPLE_H
#define QDATASTREAMEXAMPLE_H

#include <QDebug>
#include <QFile>
#include <QDataStream>
#include <QSharedPointer>

class PersonData{
public:
    PersonData(){
        qInfo()<< "PersonData created at:" << this;
    }
    PersonData(const QString name, int age, int height){
        qInfo()<< "PersonData created at:" << this;
        this->name = name;
        this->age = age;
        this->height = height;
    }
    ~PersonData(){
         qInfo()<< "PersonData destroyed at:" << this;
    }
    QString name;
    int age;
    int height;

    //Overload for QDebug
    friend QDebug operator<<(QDebug& dbg, const PersonData &data){
        // The QDebugStateSaver class is used to save and restore the state of a
        // QDebug object. When you create a QDebugStateSaver object by passing a
        // QDebug instance to its constructor, it saves the current state of
        // that QDebug object. When the QDebugStateSaver object goes out of
        // scope (or is explicitly destroyed), it restores the QDebug object to
        // its original state.
        QDebugStateSaver saver(dbg);
        dbg << "Person: " << data.name << " , age:" << data.age
            << " , height:" << data.height;
        return dbg;
    }

    // Overload for QDataStream (Serialization)
    friend void operator<<(QDataStream& out, const PersonData& data) {
         out << data.name << data.age << data.height;
    }

    // Overload for QDataStream (Deserialization)
    friend void operator>>(QDataStream& in, PersonData& data) {
         in >> data.name >> data.age >> data.height;
    }
};

class QDataStreamExample
{
private:
    void SaveBinaryDataToFile(QFile &file, PersonData &data)
    {
         qInfo() << "Saving persondata to file:" << data;
         QDataStream stream(&file);
         stream.setVersion(QDataStream::Qt_6_0);
         stream << data;
         if (!file.flush()) {
             qInfo() << "error: " << file.errorString();
         }
    }

    QSharedPointer<PersonData> ReadBinaryFromFile(QFile &file)
    {
         QDataStream stream(&file);
         stream.setVersion(QDataStream::Qt_6_0);

         //QSharedPointer<PersonData> personptr = QSharedPointer<PersonData>::create();
         auto personptr = QSharedPointer<PersonData>(new PersonData);
         stream >> *(personptr.data());
         return personptr;
    }


public:
    QDataStreamExample(){
        qInfo()<< "QDataStreamExample created at:" << this;
    }
    ~QDataStreamExample(){
        qInfo()<< "QDataStreamExample destroyed at:" << this;
    }

    void RunExample(){
        qInfo() << "============== QDataStream Example ==============================";
        QString filename = "test.bin"; //will write to the local project dir
        QFile file(filename);

        if(!file.open(QIODevice::ReadWrite)) //another important mode is QIODevice::Append
        {
            qInfo() << "Error: " << file.errorString();
            return;
        }

        PersonData person1("Anakin",23,184); //created on the Stack
        PersonData person2("Leia",23,178); //created on the Stack

        SaveBinaryDataToFile(file, person1);
        SaveBinaryDataToFile(file, person2);

        file.seek(0);
        auto person3 = ReadBinaryFromFile(file);
        auto person4 = ReadBinaryFromFile(file);
        qInfo() << "Person read from file: " << *person3.data();
        qInfo() << "Person read from file: " << *person4.data();
    }
};


#endif // QDATASTREAMEXAMPLE_H
