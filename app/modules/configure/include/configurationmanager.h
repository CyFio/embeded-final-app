/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:18:15 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: configurationmanager.h
 * Project: embeded final supervisor
 * Description: 
 */

#ifndef CONFIGUATIONMANAGER_H
#define CONFIGUATIONMANAGER_H
#include <QString>
#define DEFAULT_CONFIGURE_PATH ":/config/config.json"
#define CONFIGURE_PATH "config.json"

class QJsonArray;
class QJsonObject;

class ConfigurationManager
{
public:
//    Singleton
    ~ConfigurationManager();
    ConfigurationManager(const ConfigurationManager&)=delete;
    ConfigurationManager& operator=(const ConfigurationManager&)=delete;
//    Get Instance
    static ConfigurationManager& Get()
    {
        static ConfigurationManager instance;
        return instance;
    }
    int Query_Int(const QString& url);
    double Query_Double(const QString& url);
    QString Query_String(const QString& url);
    QJsonArray Query_Array(const QString& url);
    QJsonObject Query_Object(const QString& url);
private:
    ConfigurationManager();
    QJsonObject* configs;
};

#endif // CONFIGUATIONMANAGER_H
