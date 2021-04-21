/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:18:34 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: mymqttclient.h
 * Project: embeded final supervisor
 * Description: 
 */

#ifndef MYMQTTCLIENT_H
#define MYMQTTCLIENT_H

#include <QObject>
#include "MQTTAsync.h"
#if !defined(_WIN32)
#include <unistd.h>
#else
#include <windows.h>
#endif

#if defined(_WRS_KERNEL)
#include <OsWrapper.h>
#endif
#include <QVector>
#include <QMap>


class MyMQTTClient : public QObject
{
    Q_OBJECT
public:
    explicit MyMQTTClient(QObject *parent = nullptr);
    ~MyMQTTClient();
    typedef enum{
        CLIENT_UNINITIALIZED = 0,
        CLIENT_INIITIALIZED,
        CLIENT_STARTING,
        CLIENT_STARTED,
        CLIENT_FINISHED,
        CLIENT_DESTROYED
    }CLIENT_STATES;
//    static QVector<MyMQTTClient*> client_list;
    bool Setup(const QString& addr, const QString& client_id);
    bool Connect(const QString& user_name, const QString& password);
    bool Disconnect(MQTTAsync_onSuccess* onDisconnect = nullptr, MQTTAsync_onFailure* onDisconnectFailure = nullptr);
    typedef void Receive_Callback_t(QObject* object, const QString& topic, MQTTAsync_message* message);
    struct receive_register_t{
      QObject* object;
      Receive_Callback_t* callback;
      bool operator==(const receive_register_t& other)const
      {
          return object == other.object && callback == other.callback;
      }
    };
    CLIENT_STATES Get_State()const {return state; }
    bool Subscribe(const QString& topic, int QOS = 1);
    bool unSubscribe(const QString& topic);
    bool Register_Receive(const QString& topic, QObject* object, Receive_Callback_t callback);
    bool Resign_Receive(const QString& topic, QObject* object);
    bool Publish(const QString& topic, void* payload, int payloadlen, void* context = nullptr, MQTTAsync_onSuccess* onSuccess = nullptr, MQTTAsync_onFailure* onFailure = nullptr,int QOS = 1);
signals:

private:
    CLIENT_STATES state;
    MQTTAsync client;
    QMap<QString, QVector<receive_register_t>> receive_callbacks;
    static void on_connection_lost(void* ptr_this, char* cause);
    static int on_message_arrived(void* ptr_this, char* topicName, int topicLen, MQTTAsync_message* message);
    static void on_connect_fail(void* ptr_this, MQTTAsync_failureData* response);
    static void on_connect_success(void* ptr_this, MQTTAsync_successData* response);
    static void on_subscription_success(void* ptr_this, MQTTAsync_successData* response);
    static void on_subscription_fail(void* ptr_this, MQTTAsync_failureData* response);
    int ret_code;
};

#endif // MYMQTTCLIENT_H
