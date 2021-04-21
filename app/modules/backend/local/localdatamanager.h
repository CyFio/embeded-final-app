/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:17:12 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: localdatamanager.h
 * Project: embeded final supervisor
 * Description: 
 */

#ifndef LOCALDATAMANAGER_H
#define LOCALDATAMANAGER_H

#include <QObject>

class QSqlDatabase;

class LocalDataManager : public QObject
{
    Q_OBJECT
public:
    struct config
    {
        QString db_dir;
        QString db_filename;
    };
    explicit LocalDataManager(QObject *parent = nullptr);
    ~LocalDataManager();
    int SetUp(const QString& db_dir, const QString& db_filename);
    int SetUp(const config&);
    inline QSqlDatabase& GetDB()const {return *db;}

public slots:

signals:

private:
    QSqlDatabase* db = nullptr;
};

#endif // LOCALDATAMANAGER_H
