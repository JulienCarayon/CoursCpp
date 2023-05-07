#ifndef MQTTMANAGER_H
#define MQTTMANAGER_H

#include <mqtt/async_client.h>
#include <iostream>
#include <string>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>

using namespace std;

const string s_ADDRESS{"tcp://broker.emqx.io:1883"};
const string s_CLIENT_ID{"MQTT-Receiver"};
const string s_TOPIC{"/ynov/bordeaux/CoursCpp"};
const uint8_t u8_INTERVAL{20};
const uint8_t u8_QOS_MQTT{2};

class Callback : public virtual mqtt::callback
{
public:
    virtual void connection_lost(const string &cause)
    {
        cout << "Connection lost !" << endl;
        if (!cause.empty())
            std::cout << "\tcause: " << cause << std::endl;
    }
};

class MqttManager
{
private:
    mqtt::async_client m_client;

public:
    MqttManager();
    bool initConnection(void);
    void publishData(QByteArray jsonData);
    void disconect();
    Callback callback;
};

#endif // MQTTMANAGER_H
