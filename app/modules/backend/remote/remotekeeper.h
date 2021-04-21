/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:17:50 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: remotekeeper.h
 * Project: embeded final supervisor
 * Description: 
 */

#ifndef REMOTEKEEPER_H
#define REMOTEKEEPER_H

#include <QObject>
#include "transmittion/mymqttclient.h"

class QTimer;


class RemoteKeeper : public QObject
{
    Q_OBJECT
public:
    explicit RemoteKeeper(QObject *parent = nullptr);
    ~RemoteKeeper();
    int Setup(MyMQTTClient* client);
    int GetScore() const {return score;}


signals:
    void ScoreChanged(int score);

private:
    int score;
    MyMQTTClient* client = nullptr;
    QTimer* timer;

    static void on_heartbeat(QObject *this_ptr, const QString &topic, MQTTAsync_message *message);
private slots:
    void heartcheck();
};

#endif // REMOTEKEEPER_H
