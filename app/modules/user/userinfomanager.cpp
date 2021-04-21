/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:18:45 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: userinfomanager.cpp
 * Project: embeded final supervisor
 * Description: 
 */

#include "user/include/userinfomanager.h"
#include <QDir>
#include <QSqlQuery>
#include "configure/include/configurationmanager.h"
#include "algorithm/include/encryption.h"

UserInfoManager::~UserInfoManager()
{
    db->close();
    delete this->db;
}

unsigned int UserInfoManager::Add_User(const QString &username, const QString &password)
{
    if(this->available){
        auto result = db->exec(QString("INSERT INTO users(name, password)""VALUES('%1','%2')").arg(username, Encypt(password, EncyptConfig())));

    }
    return 0;
}

unsigned int UserInfoManager::Find_User(const QString &username) const
{
    return 0;
}

QString UserInfoManager::Find_User(unsigned int user_id) const
{
    return "";
}

bool UserInfoManager::Check_Password(const QString &username, const QString &password) const
{
    return false;
}

bool UserInfoManager::Remove_User(const QString &username)
{
    return false;
}

bool UserInfoManager::Remove_User(unsigned int user_id)
{
    return false;
}

UserInfoManager::UserInfoManager()
{
    ConfigurationManager& config = ConfigurationManager::Get();
    QDir dir;
    UserInfoManager::db = new QSqlDatabase(QSqlDatabase::addDatabase(("QSQLITE")));
    QString path = config.Query_String("database.path");
    dir.mkpath(path);
    QString filename = path + '/' + ConfigurationManager::Get().Query_String("database.name");
    db->setDatabaseName(filename);
    db->open();
    this->available = this->Initialize_UserTable();
}

bool UserInfoManager::Initialize_UserTable()
{
    if(this->db && this->db->isOpen())
    {
        db->exec("CREATE TABLE IF NOT EXISTS users ("
                 "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                 "name VARCHAR(20) NOT NULL, UNIQUE"
                 "password VARCHAR(64) NOT NULL)");
        return true;
    }
    return false;
}
