/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:17:44 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: remotecamera.h
 * Project: embeded final supervisor
 * Description: 
 */

#ifndef REMOTECAMERA_H
#define REMOTECAMERA_H

#include <QObject>
#include <QImage>
#include <QDateTime>
#include "transmittion/mymqttclient.h"

class RemoteCamera : public QObject
{
    Q_OBJECT
public:
    explicit RemoteCamera(QObject *parent = nullptr);
    bool Setup(MyMQTTClient* client, float interval);
    const QImage& GetImage()const {return frames[index];}
    float GetInterval()const {return interval;}

signals:
    void interval_changed(float);
    void img_received(QDateTime);

public slots:
    void on_interval_changed(float interval);
private:
    float interval;
    int index = 0;
    int width = 640;
    int height = 480;
    QImage frames[2];
    MyMQTTClient* client;
    static void img_receive(QObject* this_ptr, const QString& topic, MQTTAsync_message* message);
    static void interval_receive(QObject* this_ptr, const QString& topic, MQTTAsync_message* message);
};

#endif // REMOTECAMERA_H
