/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:16:54 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: imgdatamanager.cpp
 * Project: embeded final supervisor
 * Description: 
 */

#include "imgdatamanager.h"
#include "localdatamanager.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>
#include <QPixmap>
#include <QDebug>
#include <QSqlError>
#include <QListWidgetItem>
#include "backend/remote/remotecamera.h"

ImgDataManager::ImgDataManager(QObject *parent, const QString& path) : QObject(parent),
    dir("")
{
    dir.mkpath(path);
    dir.cd(path);
}

ImgDataManager::~ImgDataManager()
{

}

int ImgDataManager::SetUp(LocalDataManager &manager)
{
    this->db_manager = &manager;
    if(this->db_manager != nullptr)
    {
        QSqlDatabase& db = db_manager->GetDB();
        if(db.isOpen())
        {
            db.exec("CREATE TABLE IF NOT EXISTS captures ("
                     "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                     "msecs_from_utc INTEGER NOT NULL DEFAULT 0, "
                     "file_name VARCHAR(64) NOT NULL DEFAULT 'helloworld.jpg')");
        }
        return 1;
    }
    return 0;
}

void ImgDataManager::on_img_received(QDateTime time)
{
    RemoteCamera* cam = qobject_cast<RemoteCamera*>(sender());
    if(cam)
    {
         QString filename = dir.dirName()+ "/" + time.toString("yyyy-MM-dd HH-mm-ss-zzz")+".jpg";
         QPixmap pic = QPixmap::fromImage(cam->GetImage());
         if(pic.save(filename))
         {
             QSqlDatabase& db = db_manager->GetDB();
             if(db.isOpen())
             {
                 int64_t msecs_from_utc = time.toMSecsSinceEpoch();
                 db.exec(QString("INSERT INTO captures (msecs_from_utc, file_name)""VALUES('%1','%2')").arg(msecs_from_utc).arg(filename));
             }
         }
    }
}

void ImgDataManager::on_list_filter_query(QDateTime from, QDateTime to, QListWidget &list)
{
    int64_t msecs_from = from.toMSecsSinceEpoch();
    int64_t msecs_to = to.toMSecsSinceEpoch();
    QSqlDatabase& db = db_manager->GetDB();
    if(db.open()){
        QSqlQuery select_result(db);
        bool succeed = select_result.exec(
                    QString(
                        "SELECT file_name from captures WHERE msecs_from_utc BETWEEN %1 AND %2").arg(msecs_from).arg(msecs_to)
                    );
        list.clear();
        if(!succeed)
        {
            qDebug() << select_result.lastError().text();
        }
        while(select_result.next())
        {
//            qDebug() << select_result.value(0).toString();
            QListWidgetItem* item = new QListWidgetItem;
            item->setText(select_result.value(0).toString());
            list.addItem(item);
        }
        list.setCurrentRow(list.count() > 0 ? 0: -1);
//        qDebug() << "the query exec is " << succeed;
//        qDebug() << db.lastError().text();
//        qDebug() << "the query is select: " << select_result.isSelect() ;
//        qDebug() << "the query is valid: " << select_result.isValid() ;
//        qDebug() << "the contains " << select_result.size() ;
    }

}
