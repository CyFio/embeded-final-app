/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:17:37 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: remoteadc.h
 * Project: embeded final supervisor
 * Description: 
 */

#ifndef REMOTEADC_H
#define REMOTEADC_H

#include <QObject>
#include <QDateTime>
#include "transmittion/mymqttclient.h"

class RemoteADC : public QObject
{
    Q_OBJECT
public:
    explicit RemoteADC(QObject *parent = nullptr);
    bool Setup(MyMQTTClient* client, float interval);
    int GetResistance()const {return resistance;}
    float GetInterval()const {return interval;}

signals:
    void interval_changed(float);
    void resistance_changed(int, QDateTime);

public slots:
    void on_interval_changed(float interval);

private:
    float interval = 1.0f;
    int resistance = -1;
    MyMQTTClient* client;
    static void resistance_receive(QObject* this_ptr, const QString& topic, MQTTAsync_message* message);
    static void interval_receive(QObject* this_ptr, const QString& topic, MQTTAsync_message* message);
};

#endif // REMOTEADC_H
