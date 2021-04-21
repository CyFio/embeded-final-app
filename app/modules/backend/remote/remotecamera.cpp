/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:17:40 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: remotecamera.cpp
 * Project: embeded final supervisor
 * Description: 
 */

#include "remotecamera.h"
#include <QDebug>

RemoteCamera::RemoteCamera(QObject *parent) : QObject(parent)
{
    frames[0] = QImage(width, height, QImage::Format_RGB888);
    frames[1] = QImage(width, height, QImage::Format_RGB888);
}

bool RemoteCamera::Setup(MyMQTTClient *client, float interval)
{
    if(client == nullptr)return false;
    this->client = client;
    this->interval = interval;
    this->client->Subscribe("camera/data");
    this->client->Subscribe("interval/down");
    this->client->Register_Receive("camera/data", this, img_receive);
    this->client->Register_Receive("interval/down", this, interval_receive);
    return true;
}

void RemoteCamera::on_interval_changed(float interval)
{
    this->interval = interval;
    this->client->Publish("interval/up", (void*)(&(this->interval)),sizeof (this->interval));
    emit interval_changed(interval);
}

void RemoteCamera::img_receive(QObject *this_ptr, const QString &topic, MQTTAsync_message *message)
{
    RemoteCamera* cam = qobject_cast<RemoteCamera*>(this_ptr);
    if(cam != nullptr)
    {
        qDebug() << "cam image receieved!" << "length = " << message->payloadlen;
//        memcpy(cam->frames[!(cam->index)].bits(),message->payload, cam->width*cam->height*24);
        cam->frames[!(cam->index)] = QImage((uchar*)(message->payload), 640, 480, QImage::Format_RGB888);
        cam->index = !cam->index;
        emit cam->img_received(QDateTime::currentDateTime());
        cam->client->Publish("camera/feedback", (void*)"666", 4);
    }
}

void RemoteCamera::interval_receive(QObject *this_ptr, const QString &topic, MQTTAsync_message *message)
{
    RemoteCamera* cam = qobject_cast<RemoteCamera*>(this_ptr);
    if(cam != nullptr)
    {
        cam->interval = *((float*)message->payload);

        qDebug() << "cam interval received:" << cam->interval;
        emit cam->interval_changed(cam->interval);
    }
}
