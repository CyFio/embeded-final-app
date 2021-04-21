/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:17:04 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: imgdatamanager.h
 * Project: embeded final supervisor
 * Description: 
 */

#ifndef IMGDATAMANAGER_H
#define IMGDATAMANAGER_H

#include <QObject>
#include <QDir>
#include <QDateTime>
#include <QListWidget>

class LocalDataManager;

class ImgDataManager : public QObject
{
    Q_OBJECT
public:
    explicit ImgDataManager(QObject *parent = nullptr, const QString& path = "captures");
    ~ImgDataManager();
    int SetUp(LocalDataManager& manager);

public slots:
    void on_img_received(QDateTime time);
    void on_list_filter_query(QDateTime from, QDateTime to, QListWidget& list);
signals:


private:
    LocalDataManager* db_manager;
    QDir dir;

};

#endif // IMGDATAMANAGER_H
