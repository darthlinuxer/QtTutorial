#ifndef SETTINGSEXAMPLE_H
#define SETTINGSEXAMPLE_H

#include "qcoreapplication.h"
#include <QDebug>
#include <QSettings>

class SettingsExample
{
    QCoreApplication* app;
    QSettings* setting;

 public:
   SettingsExample(QCoreApplication &a) {
     qInfo() << "SettingsExample created at : " << this;
     this->app = &a;
     app->setApplicationName("TestSetting");
     app->setOrganizationName("MyCompany");
     app->setOrganizationDomain("MyCompany.com");
     setting =
         new QSettings(app->organizationName(), app->applicationName(), app);

     //Storing in file instead of registry.. comment line above and uncomment below
     //QString filename = a.applicationDirPath() + "/settings.ini";
     //setting = new QSettings(filename, QSettings::Format::IniFormat);
     if (setting->allKeys().length() == 0)
       qInfo() << "There are no saved keys yet!";
   };
   ~SettingsExample() { qInfo() << "SettingsExample Destroyed at: " << this; }

   void Save(QString key, QVariant value) {
     if (setting->contains(key)) {
       qInfo() << "Key:" << key << ", already exists in the Registry!";
       return;
     }
     qInfo() << "Trying to save key: " << key << " value:" << value;
     setting->setValue(key, value);
     setting->sync();
     switch (setting->status()) {
     case QSettings::NoError:
       qInfo() << "Saved successfully!";
       break;
     case QSettings::AccessError:
       qCritical() << "Some Error writing to disk!";
       break;
     case QSettings::FormatError:
       qCritical() << "Some Format Error";
       break;
     }
   }

   void Load(QString key) {
     qInfo() << "Key: " << key
             << "  Stored Value:" << setting->value(key).toString();
   }

  void RunExample() {
        qInfo() << "=================== QSettings =========================";
        Save("Camilo height:", 184);
        Save("Best dog breed:", "pincher");
        Info();
        Load("Camilo height:");
        Load("Best dog breed:");
        //Delete all from registry
        DeleteAll();
        //Check to see if it is deleted
        Info();

        /* OUTPUT
         * There are no saved keys yet!
         * =================== QSettings =========================
         * Trying to save key:  "Camilo height:"  value: QVariant(int, 184)
         * Saved successfully!
         * Trying to save key:  "Best dog breed:"  value: QVariant(QString,"pincher")
         * Saved successfully!
         * App Name:  "TestSetting"
         * Organization Name:  "MyCompany"
         * FileName:  "\\HKEY_CURRENT_USER\\Software\\MyCompany\\TestSetting"
         * All Keys: QList("Best dog breed:", "Camilo height:")
         * Key:  "Camilo height:"   Stored Value: "184"
         * Key:  "Best dog breed:"   Stored Value: "pincher"
         * Deleting all the stored keys...
         * App Name:  "TestSetting"
         * Organization Name:  "MyCompany"
         * FileName:  "\\HKEY_CURRENT_USER\\Software\\MyCompany\\TestSetting"
         * All Keys: QList()
         * */
  }

  void DeleteAll() {
        qInfo() << "Deleting all the stored keys...";
        setting->clear();
        setting->sync();
  }

  void Info(){
        qInfo() << "App Name: " << setting->applicationName();
        qInfo() << "Organization Name: " << setting->organizationName();
        qInfo() << "FileName: " << setting->fileName();
        qInfo() << "All Keys:" << setting->allKeys();
  }
};

#endif // SETTINGSEXAMPLE_H
