#ifndef THREADELEMENT_H
#define THREADELEMENT_H

#include <QProcess>
#include <QThread>
#include <QDebug>
#include <mqtt/async_client.h>
using namespace std;




class MqttManager: public QThread
{
    Q_OBJECT


public:

    typedef enum{
        Connect         = 0,
        Connected       = 1,
        Disconnect      = 2,
        Disconnected    = 3
    }State;

    MqttManager(QObject *parent);
    string s_ADDRESS;// = "tcp://broker.emqx.io:1883";
    string s_CLIENT_ID;// = "MQTT-Receiver";
    string s_TOPIC;// = "/ynov/bordeaux/";
    uint8_t Qos = 0;


    State getState();
    void setState(State state);
    void toggleState();

    void fromJson(const QJsonObject &json);
    QJsonObject ObjectFromString(const QString &in);
signals:
    void lastMessage_signal(QString s_lastMessage);
    void lastMessageDecoded_signal(QString s_lastDecodedMessage);
    void lastImage_signal(const QString s_filepath);

protected:
    void run(void);

private:
//    int _counter;
    const string s_DECODED_IMAGE_PATH = "decoded_image.png";
    State currentState = Disconnected;

    QString showData(QString inputImageFilename);
    QString binaryToString(QString binary);
};

#endif // THREADELEMENT_H
