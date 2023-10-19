#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QDir>

class Logger: public QObject
{
    Q_OBJECT

public:
    explicit Logger(QObject* parent = nullptr):QObject(parent) {}

    inline static bool logging = false;
    inline static QString filename =  QDir::currentPath() + QDir::separator() + "log.txt";
    inline static const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER = qInstallMessageHandler(nullptr);

    static void Attach(){
        Logger::logging = true;
        qInstallMessageHandler(Logger::MessageHandler);
    }

    static void Detach(){
        Logger::logging = false;
        qInstallMessageHandler(nullptr);
    }

    static void MessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
    {
        if(!Logger::logging) return;
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

        QFile file(Logger::filename);
        if(!file.open(QIODevice::Append)) return;
        QTextStream ts(&file);
        ts << QDateTime::currentDateTime().toString()
           << " - " << txt
           << " file:" << context.file << " line:" << context.line << "\r\n";
        ts.flush();
        file.close();
        (*QT_DEFAULT_MESSAGE_HANDLER)(type, context, msg);
    }

};

#endif // LOGGER_H
