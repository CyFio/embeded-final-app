/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:17:19 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: localmanager.h
 * Project: embeded final supervisor
 * Description: 
 */

#ifndef LOCALMANAGER_H
#define LOCALMANAGER_H

#include <QObject>
//#include "localdatamanager.h"

class LocalDataManager;
class RDataManager;
class ImgDataManager;

class LocalManager : public QObject
{
    Q_OBJECT
public:
    struct config{
        QString db_dir;
        QString db_name;

    };
    explicit LocalManager(QObject *parent = nullptr);
    ~LocalManager();
    RDataManager* Get_RDataManager(){ return rdata_manager;}
    ImgDataManager* Get_ImgDataManager(){return imgdata_manager;}
    LocalDataManager* Get_DBManager(){return db_manager;}
    int Setup(config& cfg);

signals:

private:
    LocalDataManager* db_manager;
    RDataManager* rdata_manager;
    ImgDataManager* imgdata_manager;
};

#endif // LOCALMANAGER_H
