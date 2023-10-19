#ifndef QLOGEXAMPLE_H
#define QLOGEXAMPLE_H

#include <QDebug>
#include <QFile>
#include <QDateTime>

 const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER = qInstallMessageHandler(nullptr);

class QLogExample
{

private:
    static void MessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
    {
        QString txt;
        switch (type) {
        case QtDebugMsg:
            txt = QString("Debug: %1").arg(msg);
            break;
        case QtInfoMsg:
            txt = QString("Info: %1").arg(msg);
            break;
        case QtWarningMsg:
            txt = QString("Warning: %1").arg(msg);
            break;
        case QtCriticalMsg:
            txt = QString("Critical: %1").arg(msg);
            break;
        case QtFatalMsg:
            txt = QString("Fatal: %1").arg(msg);
            break;
        }

        QFile file("log.txt");
        if(!file.open(QIODevice::Append)) return;
        QTextStream ts(&file);
        ts << QDateTime::currentDateTime().toString()
           << " - " << txt
           << " file:" << context.file << " line:" << context.line << "\r\n";
        ts.flush();
        file.close();
        (*QT_DEFAULT_MESSAGE_HANDLER)(type, context, msg);
    }

public:
    QLogExample(){
        qInfo() << "QLogExample created at : " << this;
    }
    ~QLogExample(){
        qInfo() << "QLogExample destroyed at : " << this;
    }

    void RunExample(){
        qInstallMessageHandler(MessageHandler);

        qInfo() << "This is an Info message";
        qDebug() << "This is a Debug message";
        qWarning() << "This is a Warning message";
        qCritical() << "This is a Critical message";
        qFatal() << "This is a Fatal message";

        qInstallMessageHandler(nullptr);
    }
};


#endif // QLOGEXAMPLE_H
