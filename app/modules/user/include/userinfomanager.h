/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:18:42 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: userinfomanager.h
 * Project: embeded final supervisor
 * Description: 
 */

#ifndef USERINFOMANAGER_H
#define USERINFOMANAGER_H

#include<QString>
#include<QSqlDatabase>

class UserInfoManager
{
public:
//    Singleton
    ~UserInfoManager();
    UserInfoManager(const UserInfoManager&)=delete;
    UserInfoManager& operator=(const UserInfoManager&)=delete;
//    Get Instance
    static UserInfoManager& Get()
    {
        static UserInfoManager instance;
        return instance;
    }
    bool Available() const {return this->available;}
    unsigned int Add_User(const QString& username="hayasaka ai", const QString& password="0402");
    unsigned int Find_User(const QString& username="hayasaka ai") const;
    QString Find_User(unsigned int user_id) const;
    bool Check_Password(const QString& username, const QString& password) const;
    bool Remove_User(const QString& username);
    bool Remove_User(unsigned int user_id);
private:
    UserInfoManager();
    bool Initialize_UserTable();
    QSqlDatabase* db;
    bool available = false;
};

#endif // USERINFOMANAGER_H
