/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:17:31 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: remoteadc.cpp
 * Project: embeded final supervisor
 * Description: 
 */

#include "remoteadc.h"
#include <QDebug>

RemoteADC::RemoteADC(QObject *parent) : QObject(parent)
{

}

bool RemoteADC::Setup(MyMQTTClient *client, float interval)
{
    if(client == nullptr)return false;
    this->client = client;
    this->interval = interval;
    this->client->Subscribe("resistance/data");
    this->client->Subscribe("interval/down");
    this->client->Register_Receive("resistance/data", this, resistance_receive);
    this->client->Register_Receive("interval/down", this, interval_receive);
    return true;
}

void RemoteADC::on_interval_changed(float interval)
{
    this->interval = interval;
    this->client->Publish("interval/up", (void*)(&(this->interval)),sizeof (this->interval));
    emit interval_changed(this->interval);
}

void RemoteADC::resistance_receive(QObject *this_ptr, const QString &topic, MQTTAsync_message *message)
{
    RemoteADC* adc = qobject_cast<RemoteADC*>(this_ptr);
    if(adc != nullptr)
    {
        adc->resistance = *((int*)message->payload);
        qDebug() << adc->resistance;
        adc->client->Publish("resistance/feedback",  (void*)"666", 4);
//        qDebug() << adc;
        emit adc->resistance_changed(adc->resistance, QDateTime::currentDateTime());
    }
}

void RemoteADC::interval_receive(QObject *this_ptr, const QString &topic, MQTTAsync_message *message)
{
    RemoteADC* adc = qobject_cast<RemoteADC*>(this_ptr);
    if(adc != nullptr)
    {
        adc->interval = *((float*)message->payload);
        emit adc->interval_changed(adc->interval);
    }
}
