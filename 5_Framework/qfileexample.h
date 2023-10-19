#ifndef QFILEEXAMPLE_H
#define QFILEEXAMPLE_H

#include "qcoreapplication.h"
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QDir>
#include <QStorageInfo>
#include <QThread>
#include <QLockFile>

class QFileExample: public QObject
{
    Q_OBJECT
    inline static int subdir = 0;
    void Write(QFile &file, QString message)
    {
        if(!file.isWritable()) return;

        QTextStream stream(&file);
        stream.setEncoding(QStringConverter::Utf8);
        stream.seek(file.size()); //go to the end of the file;
        stream << "\n" << message;
        stream.flush();
        //Execute this again and see that the text is being appended
    }

    void ReadAll(QFile &file)
    {
        qInfo() << "------- Read all: not recommended for large files -----";
        if(!file.isReadable()) return;

        file.seek(0); //go to the beggining of the file;
        qInfo() << file.readAll(); //this is going to print raw data unformatted
    }

    void ReadLines(QFile &file){
        qInfo() << "------- Read Lines: recommended for large files -----";
        if(!file.isReadable()) return;

        file.seek(0); //go to the beggining of the file;
        QTextStream in(&file);
        while (!in.atEnd()) {
            qInfo() << in.readLine(); //will read up to the first \n
        }
    }

    void ReadChunks(QFile &file, int numberOfChars){
        qInfo() << "------------------- Read Chunks --------------------";
        if(!file.isReadable()) return;

        file.seek(0); //go to the beggining of the file;
        QTextStream stream(&file);
        while (!stream.atEnd()) {
            qInfo() << stream.read(numberOfChars);
        }
    }

    void TreeList(QDir& root)
    {
        subdir++;
        QString separator;
        separator = separator.fill('-',subdir);
        foreach (QFileInfo fi,
                 root.entryInfoList(QDir::Filter::AllEntries |
                                    QDir::Filter::NoDotAndDotDot,
                                    QDir::SortFlag::DirsFirst)) {
            if(fi.isDir())
            {

                qInfo() << separator << "Dir: " << fi.filePath();
                //QDir child(fi.filePath());
                //TreeList(child);
            }
            if(fi.isFile()) qInfo() << separator << "File: " << fi.fileName();
        }
        subdir--;
    }

    void DiskSpace(){
        qInfo() << "-------------------Disk Space-------------------------------------";
        foreach(QStorageInfo storage, QStorageInfo::mountedVolumes())
        {
            qInfo() << "Name: " << storage.name();
            qInfo() << "FileSystem: " << storage.fileSystemType();
            qInfo() << "Total Bytes: " << storage.bytesTotal()/1000/1000 << "Mb";
            qInfo() << "Free Space: " << storage.bytesAvailable()/1000/1000 << "Mb";
            qInfo() << "Device: " << storage.device();
            qInfo() << "Root: " << storage.isRoot();
            qInfo() << "\n";
        }
    }


public:
    QFileExample(){
        qInfo() << "QFileExample created at:" << this;
    }
    ~QFileExample(){
        qInfo() << "QFileExample destroyed at:" << this;
    }

    void RunExample(QCoreApplication &a)
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

        //Everything above will overwrite whatever is in the file
        Write(file, QString("This is another way of writing!")); //but this will append

        ReadAll(file);
        ReadLines(file);
        ReadChunks(file,100);

        file.close();

        qInfo()<< "---------------------Listing Parent Directories-------------------------";
        QDir dir(a.applicationDirPath());
        //dir.cdUp(); //move up to parent directory
        TreeList(dir);

        qInfo()<< "---------------------DISK Info------------------------------------------";
        QStorageInfo root = QStorageInfo::root();
        qInfo() << "root: " << root.rootPath();
        //DiskSpace();
    }

    void RunExampleWithLock() {
        qInfo() << "============== QLockFile Example ==============================";
        QString path = QDir::currentPath() + QDir::separator() + "test.txt";
        QFile file(path);
        QLockFile lock(file.fileName()+'l');
        lock.setStaleLockTime(15000); //in 15 seconds it will unlock automatically if you forget
        if(lock.tryLock())
        {
            qInfo() << "Writing to file...";
            if(!file.open(QIODevice::WriteOnly)) //another important mode is QIODevice::Append
            {
                qInfo() << "Error: " << file.errorString();
                return;
            }
            Write(file, "Hello Locked World!");
            //lock.unlock();
        } else
        {
            qInfo() << "Could not lock the file...";
            qint64 pid;
            QString host;
            QString application;
            if(lock.getLockInfo(&pid, &host, &application)){
                qInfo() << "The file is locked by process id:" << pid;
                qInfo() << "Host: " << host;
                qInfo() <<"Application: " << application;
            } else {
                qInfo() << "File is locked but can't get the info by whom!";
            }
        }
    }
};



#endif // QFILEEXAMPLE_H
