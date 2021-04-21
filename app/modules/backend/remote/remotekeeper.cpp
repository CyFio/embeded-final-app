/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:17:47 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: remotekeeper.cpp
 * Project: embeded final supervisor
 * Description: 
 */

#include "remotekeeper.h"

#include <QTimer>

RemoteKeeper::RemoteKeeper(QObject *parent) : QObject(parent),
    score(0), timer(new QTimer(this))
{
//    timer->setInterval(1000);
    timer->setSingleShot(false);

    connect(timer, &QTimer::timeout, this, &RemoteKeeper::heartcheck);

}

RemoteKeeper::~RemoteKeeper()
{
    this->timer->stop();
    this->timer->deleteLater();
}

int RemoteKeeper::Setup(MyMQTTClient *client)
{
    if(client == nullptr)return 0;
    this->client = client;
    this->client->Subscribe("heartbeat/down");
    this->client->Register_Receive("heartbeat/down", this, on_heartbeat);
    this->timer->start(1000);
    return 1;
}

void RemoteKeeper::on_heartbeat(QObject *this_ptr, const QString &topic, MQTTAsync_message *message)
{
    RemoteKeeper* keeper = qobject_cast<RemoteKeeper*>(this_ptr);
    if(keeper)
    {
        keeper->score = 3;
        emit keeper->ScoreChanged(keeper->score);
    }
}

void RemoteKeeper::heartcheck()
{
    (this->score > 0)&&(--this->score);
    emit ScoreChanged(this->score);
    this->client->Publish("heartbeat/up", (void*)"haha", 4);
}
