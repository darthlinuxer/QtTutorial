#ifndef QFILEEXAMPLE_H
#define QFILEEXAMPLE_H

#include <QDebug>
#include <QFile>
#include <QDateTime>

class QFileExample
{
    void ReadAll(QFile &file)
    {
        qInfo() << "------- Read all: not recommended for large files -----";
        if(!file.isReadable()) return;
        file.seek(0);
        qInfo() << file.readAll(); //this is going to print raw data unformatted
    }

    void ReadLines(QFile &file){
        qInfo() << "------- Read Lines: recommended for large files -----";
        if(!file.isReadable()) return;
        file.seek(0);
        QTextStream in(&file);
        while (!in.atEnd()) {
            qInfo() << in.readLine(); //will read up to the first \n
        }
    }

    void ReadChunks(QFile &file, int numberOfChars){
        qInfo() << "------------------- Read Chunks --------------------";
        if(!file.isReadable()) return;
        file.seek(0);
        QTextStream in(&file);
        while (!in.atEnd()) {
            qInfo() << in.read(numberOfChars);
        }
    }


public:
    QFileExample(){
        qInfo() << "QFileExample created at:" << this;
    }
    ~QFileExample(){
        qInfo() << "QFileExample destroyed at:" << this;
    }

    void RunExample()
    {
        qInfo() << "============== QFile Example ==============================";
        QString filename = "test.txt"; //will write to the local project dir
        QFile file(filename);

        if(!file.open(QIODevice::ReadWrite)) //another important mode is QIODevice::Append
        {
            qInfo() << "Error: " << file.errorString();
            return;
        }

        QString now = QDateTime::currentDateTime().toString();

        QByteArray data;
        data.append(now.toUtf8());
        data.append(" : ");
        data.append(("Hello World \n"));
        file.write(data);
        qInfo() << "Wrote Hello World";
        qInfo() << "File Pos: " << file.pos();

        data.clear();
        data.append(now.toUtf8());
        data.append(" - ");
        QString specialChars = ": speçi@l chars needs encoding!";
        data.append(specialChars.toLocal8Bit());

        data.append("\n");
        data.append(now.toUtf8());
        data.append(" - ");
        data.append(specialChars.toUtf8());
        file.write(data);

        qInfo() << "Wrote special chars!";
        qInfo() << "File Pos: " << file.pos();

        ReadAll(file);
        ReadLines(file);
        ReadChunks(file,25);

        file.close();
    }
};



#endif // QFILEEXAMPLE_H
