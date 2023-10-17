#ifndef QBUFFEREXAMPLE_H
#define QBUFFEREXAMPLE_H

#include "qdebug.h"
#include <QBuffer>
class QBufferExample
{
public:
    QBufferExample(){
         qInfo() << "QBufferExample created at : " << this;
    }
    ~QBufferExample(){
         qInfo() << "QBufferExample destroyed at : " << this;
    }

    void RunExample(){
         qInfo() << "==============QBuffer Example=====================";
         QBuffer buffer;
         if(!buffer.open(QIODevice::ReadWrite))
         {
             qInfo() << "Failed to open Buffer!";
             return;
         }
         qInfo() << "Buffer position on creation: " << buffer.pos();
         QByteArray data("Hello");
         buffer.seek(0);
         buffer.write(data);
         qInfo() << "Buffer position after writing data: " << buffer.pos();
         buffer.seek(data.length());
         buffer.write(" World!");
         qInfo() << "Buffer position after writing more data: " << buffer.pos();
         qInfo() << "Read All: " << buffer.readAll();
         buffer.seek(0);
         qInfo() << "Read All:" << buffer.readAll();
         buffer.close();

         /* OUTPUT
          * QBufferExample created at :  0x88cbffb0f
          * ==============QBuffer Example=====================
          * Buffer position on creation:  0
          * Buffer position after writing data:  5
          * Buffer position after writing more data:  12
          * Read All:  ""
          * Read All: "Hello World!"
          * */
    }
};

#endif // QBUFFEREXAMPLE_H
