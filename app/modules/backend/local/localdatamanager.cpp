/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:17:08 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: localdatamanager.cpp
 * Project: embeded final supervisor
 * Description: 
 */

#include "localdatamanager.h"
#include <QSqlDatabase>
#include <QDir>
LocalDataManager::LocalDataManager(QObject *parent) : QObject(parent)
{

}

LocalDataManager::~LocalDataManager()
{
    this->db->close();
    delete this->db;
}

int LocalDataManager::SetUp(const QString &db_dir, const QString& db_filename)
{
    QDir dir;
    this->db = new QSqlDatabase(QSqlDatabase::addDatabase(("QSQLITE")));
    dir.mkpath(db_dir);
    QString filename = db_dir + '/' + db_filename;
    db->setDatabaseName(filename);
    db->open();
    return db->isOpen();
}

int LocalDataManager::SetUp(const LocalDataManager::config & cfg)
{
    return SetUp(cfg.db_dir, cfg.db_filename);
}
