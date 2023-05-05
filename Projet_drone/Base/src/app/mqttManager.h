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

    QPixmap binaryToPixmap(const QByteArray &binaryData);
    bool binaryToPngFile(const QByteArray &binaryData, const QString &filePath);
signals:
    void lastMessage_signal(QString s_lastMessage);


protected:
    void run(void);

private:
//    int _counter;
    State currentState = Disconnected;

};

#endif // THREADELEMENT_H
