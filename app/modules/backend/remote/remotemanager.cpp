/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:17:57 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: remotemanager.cpp
 * Project: embeded final supervisor
 * Description: 
 */

#include "remotemanager.h"
#include "remoteadc.h"
#include "remotecamera.h"
#include "remotekeeper.h"

RemoteManager::RemoteManager(QObject *parent) :
    QObject(parent),
    adc(new RemoteADC),keeper(new RemoteKeeper),camera(new RemoteCamera),client(new MyMQTTClient)
{

}

RemoteManager::~RemoteManager()
{
    delete adc;
    delete camera;
    delete keeper;
    delete client;
}

bool RemoteManager::Setup(const QString &addr, const QString &client_id, const QString &user_name, const QString &password, float interval)
{
    if(!client->Setup(addr, client_id))
        return false;
    if(!client->Connect(user_name, password))
        return false;
    for(int i = 0; i < 300; ++i)
    {
        if(client->Get_State() == MyMQTTClient::CLIENT_STATES::CLIENT_STARTED)
        {
            adc->Setup(client, interval);
            camera->Setup(client, interval);
            keeper->Setup(client);
            return true;
        }
        usleep(100000);
    }
    return false;
}
