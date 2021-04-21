/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:18:00 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: remotemanager.h
 * Project: embeded final supervisor
 * Description: 
 */

#ifndef REMOTEMANAGER_H
#define REMOTEMANAGER_H

#include <QObject>

class RemoteCamera;
class RemoteADC;
class RemoteKeeper;
class MyMQTTClient;

class RemoteManager : public QObject
{
    Q_OBJECT
public:
    explicit RemoteManager(QObject *parent = nullptr);
    ~RemoteManager();
    bool Setup(const QString& addr, const QString& client_id, const QString& user_name, const QString& password, float interval);
    RemoteCamera* GetCamera(){return camera;}
    RemoteKeeper* GetKeeper(){return keeper;}
    RemoteADC* GetADC(){return adc;}

signals:
private:
    RemoteADC* adc;
    RemoteKeeper* keeper;
    RemoteCamera* camera;
    MyMQTTClient* client;
};

#endif // REMOTEMANAGER_H
