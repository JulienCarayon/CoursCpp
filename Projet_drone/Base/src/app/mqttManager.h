#ifndef THREADELEMENT_H
#define THREADELEMENT_H

#include <QProcess>
#include <QThread>
#include <QDebug>
#include <mqtt/async_client.h>
#include "imageManager.h"


using namespace std;




class MqttManager: public QThread
{
    Q_OBJECT


public:

    typedef enum{
        CONNECT         = 0,
        CONNECTED       = 1,
        DISCONNECT      = 2,
        DISCONNECTED    = 3
    }State;

    MqttManager(QObject *parent);
    string s_address;// = "tcp://broker.emqx.io:1883";
    string s_clientid;// = "MQTT-Receiver";
    string s_topic;// = "/ynov/bordeaux/";
    uint8_t u8_qos = 0;


    State getState();
    void setState(State state);
    void toggleState();

    void fromJson(const QJsonObject &json);
    QJsonObject ObjectFromString(const QString &in);
signals:
    void lastMessage_signal(QString s_lastmessage);
    void lastMessageDecoded_signal(QString s_lastdecodedmessage);
    void lastImage_signal(const QString s_filepath);


protected:
    void run(void);

private:

    const string ms_DECODED_IMAGE_PATH = "decoded_image.png";
    State m_currentState_t = DISCONNECTED;

    QString showData(QString s_filepath);
    QString binaryToString(QString s_binary);
};

#endif // THREADELEMENT_H
