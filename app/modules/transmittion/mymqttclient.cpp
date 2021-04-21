/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:18:28 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: mymqttclient.cpp
 * Project: embeded final supervisor
 * Description: 
 */

#include "mymqttclient.h"
#include <QDebug>

MyMQTTClient::MyMQTTClient(QObject *parent) : QObject(parent)
{
    this->state = CLIENT_UNINITIALIZED;
//    MyMQTTClient::client_list.push_back(this);
}

MyMQTTClient::~MyMQTTClient()
{
//    this->disconnect();
    MQTTAsync_destroy(&client);
//    MyMQTTClient::client_list.removeOne(this);
}

bool MyMQTTClient::Setup(const QString &addr, const QString &client_id)
{
    if(this->state != CLIENT_UNINITIALIZED)
    {
        return false;
    }
//    if ((ret_code = MQTTAsync_create(&client, qPrintable(addr), qPrintable(client_id), MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTASYNC_SUCCESS)
    if ((ret_code = MQTTAsync_create(&client, "host:port", "Supervisor", MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTASYNC_SUCCESS)
    {
        qDebug() <<"fail to create client";
        return false;
    }
    if ((ret_code = MQTTAsync_setCallbacks(client, (void*)this, on_connection_lost, on_message_arrived, nullptr)) != MQTTASYNC_SUCCESS)
    {
        qDebug() <<"client fail to set callbacks";
        MQTTAsync_destroy(&client);
        return false;
    }
    this->state = CLIENT_INIITIALIZED;
    qDebug() <<"client setup successfully";
    return true;
}

bool MyMQTTClient::Connect(const QString &user_name, const QString &password)
{
    if(this->state != CLIENT_INIITIALIZED)
        return false;
    MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
//    conn_opts.username = qPrintable(user_name);
//    conn_opts.password = qPrintable(password);
    conn_opts.username = "your_username";
    conn_opts.password = "password";
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.onSuccess = on_connect_success;
    conn_opts.onFailure = on_connect_fail;
    conn_opts.context = (void*)this;
    if ((ret_code = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
    {
        qDebug()<< "client fail to start connection";
        return false;
    }
    this->state = CLIENT_STARTING;
    qDebug() << "client connection starting...";
    return true;
}

bool MyMQTTClient::Disconnect(MQTTAsync_onSuccess *onDisconnect, MQTTAsync_onFailure *onDisconnectFailure)
{
    MQTTAsync_disconnectOptions disc_opts = MQTTAsync_disconnectOptions_initializer;
    disc_opts.onSuccess = onDisconnect;
    disc_opts.onFailure = onDisconnectFailure;
    if ((ret_code = MQTTAsync_disconnect(client, &disc_opts)) != MQTTASYNC_SUCCESS)
    {
        return false;
    }
    this->state = CLIENT_FINISHED;
    return true;
}

bool MyMQTTClient::Register_Receive(const QString &topic, QObject *object, MyMQTTClient::Receive_Callback_t callback)
{
    receive_register_t receive_record;
    receive_record.object = object;
    receive_record.callback = callback;

    if(receive_callbacks[topic].contains(receive_record))
    {
        return false;
    }
    receive_callbacks[topic].append(receive_record);
    return true;
}

bool MyMQTTClient::Resign_Receive(const QString &topic, QObject *object)
{
    auto cb_vect = receive_callbacks[topic];
    for(auto i = cb_vect.begin(); i < cb_vect.end();)
    {
        if(i->object == object)
            i = cb_vect.erase(i);
        else
            ++i;
    }
    return true;
}

bool MyMQTTClient::Subscribe(const QString &topic, int QOS)
{
    MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
    opts.onSuccess = on_subscription_success;
    opts.onFailure = on_subscription_fail;
    opts.context = this;
    if ((ret_code = MQTTAsync_subscribe(client, qPrintable(topic), QOS, &opts)) != MQTTASYNC_SUCCESS)
    {
        qDebug() << "client " << topic << " subsrciption failed";
        return false;
    }
    return true;
}

bool MyMQTTClient::unSubscribe(const QString &topic)
{
    MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
//    opts.onSuccess = onSuccess;
//    opts.onFailure = onFailure;
//    opts.context = context;
    if ((ret_code = MQTTAsync_unsubscribe(client, qPrintable(topic), &opts)) != MQTTASYNC_SUCCESS)
    {
        return false;
    }
    return true;
}

bool MyMQTTClient::Publish(const QString& topic, void* payload, int payloadlen, void* context, MQTTAsync_onSuccess* onSuccess, MQTTAsync_onFailure* onFailure,int QOS)
{
    MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
    MQTTAsync_message pubmsg = MQTTAsync_message_initializer;
    opts.onSuccess = onSuccess;
    opts.onFailure = onFailure;
    opts.context = context;
    pubmsg.payload = payload;
    pubmsg.payloadlen = payloadlen;
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    if ((ret_code = MQTTAsync_sendMessage(client, qPrintable(topic), &pubmsg, &opts)) != MQTTASYNC_SUCCESS)
    {
        return false;
    }
    return true;
}

void MyMQTTClient::on_connection_lost(void *ptr_this, char *cause)
{
    qDebug() << "client connection lost";
    MyMQTTClient* my_client = (MyMQTTClient*)ptr_this;
    MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;

    my_client->state = CLIENT_STARTING;
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.onSuccess = on_connect_success;
    conn_opts.onFailure = on_connect_fail;
    conn_opts.context = ptr_this;
    qDebug() << "client reconnecting...";
    if ((my_client->ret_code = MQTTAsync_connect(my_client->client, &conn_opts)) != MQTTASYNC_SUCCESS)
    {
        my_client->state = CLIENT_INIITIALIZED;
    }

//    if ((my_client->ret_code = MQTTAsync_reconnect(my_client->client)) != MQTTASYNC_SUCCESS)
//    {
//        my_client->state = CLIENT_INIITIALIZED;
//    }
}

int MyMQTTClient::on_message_arrived(void *ptr_this, char *topicName, int topicLen, MQTTAsync_message *message)
{
    MyMQTTClient* my_client = (MyMQTTClient*)ptr_this;
    QString topic = topicName;
    auto cb_vect = my_client->receive_callbacks[topic];
    for(auto i = cb_vect.begin(); i != cb_vect.end(); ++i)
    {
        i->callback(i->object,topic,message);
    }
    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topicName);
    return 1;
}

void MyMQTTClient::on_connect_fail(void *ptr_this, MQTTAsync_failureData *response)
{
    MyMQTTClient* my_client = (MyMQTTClient*)ptr_this;
    my_client->state = CLIENT_INIITIALIZED;
    qDebug() << "client fail to connect";
//    MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;

//    my_client->state = CLIENT_STARTING;
//    conn_opts.keepAliveInterval = 20;
//    conn_opts.cleansession = 1;
//    conn_opts.onSuccess = on_connect_success;
//    conn_opts.onFailure = on_connect_fail;
//    conn_opts.context = ptr_this;
//    if ((my_client->ret_code = MQTTAsync_connect(my_client->client, &conn_opts)) != MQTTASYNC_SUCCESS)
//    {
//        my_client->state = CLIENT_INIITIALIZED;
//    }
}

void MyMQTTClient::on_connect_success(void *ptr_this, MQTTAsync_successData *response)
{
    ((MyMQTTClient*)ptr_this)->state = CLIENT_STARTED;
    qDebug() << "client connect successfully";
}

void MyMQTTClient::on_subscription_success(void *ptr_this, MQTTAsync_successData *response)
{
    qDebug() << "client subscribe successfully";
}

void MyMQTTClient::on_subscription_fail(void *ptr_this, MQTTAsync_failureData *response)
{
    qDebug() << "client subscribe failed";
}
