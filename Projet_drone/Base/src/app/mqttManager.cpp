#include "mqttManager.h"


#include <QByteArray>
#include <QPixmap>
#include <QBuffer>
#include <QDir>

#include <QImage>
#include <QJsonObject>
#include <QJsonDocument>  //pas utile ?
#include <QByteArray>

string s_lastmessage = "";

using namespace std;

class Callback : public virtual mqtt::callback {
public:
    void message_arrived(mqtt::const_message_ptr msg) override {

        std::cout << "Message received on topic " << msg->get_topic() << std::endl;
        s_lastmessage = msg->to_string();
    }

    virtual void connection_lost(const std::string& cause_ref) override {
        std::cout << "\nConnection lost" << std::endl;
        if (!cause_ref.empty())
            std::cout << "\tcause: " << cause_ref << std::endl;
    }

};




MqttManager::MqttManager(QObject *parent): QThread(parent)
{
    qDebug()<< "MqttManager::Constructor";
    MqttManager::s_address = "tcp://broker.emqx.io:1883" ;
    MqttManager::s_clientid = "MQTT-Receiver" ;
    MqttManager::s_topic= "/ynov/bordeaux/" ;

}

MqttManager::State MqttManager::getState()
{
    return m_currentState_t;
}

void MqttManager::toggleState()
{

    if(getState()==CONNECTED){
        MqttManager::setState(DISCONNECTED);
    }
    else{
        MqttManager::setState(CONNECT);
    }
}


void MqttManager::setState(State state)
{
    m_currentState_t = state;
}

void MqttManager::run()
{
    ImageManager imageManager;
    std::cout << "MqttManager started"<< std::endl;
    mqtt::async_client client_t(MqttManager::s_address, MqttManager::s_clientid);
    string s_previousmessage = s_lastmessage;
    try
    {
        while(1){
            if(MqttManager::getState()==CONNECT){
                mqtt::connect_options conn_opts;
                conn_opts.set_clean_session(true);

                Callback callback_t;
                client_t.set_callback(callback_t);

                client_t.connect(conn_opts)->wait();

                mqtt::topic mqtt_topic(client_t, MqttManager::s_topic, MqttManager::u8_qos);
                mqtt_topic.subscribe()->wait();
                MqttManager::setState(CONNECTED);
            }
            if (MqttManager::getState() == DISCONNECT){
                client_t.disconnect()->wait();
                MqttManager::setState(DISCONNECTED);
                MqttManager::quit();
                break;
            }

            if(s_lastmessage != s_previousmessage){
                cout << "<NEW Message incoming START>" << s_lastmessage <<"<NEW Message incoming END>"<< std::endl;
//                MqttManager::binaryToPngFile(QByteArray::fromStdString(lastMessage),QDir::currentPath().remove("/bin/release"));
                emit MqttManager::lastMessage_signal(QString::fromStdString(s_lastmessage));
                const QJsonObject Array = imageManager.ObjectFromString(QString::fromStdString(s_lastmessage));
                imageManager.fromJson(Array);
                emit MqttManager::lastMessageDecoded_signal(imageManager.showData(QString::fromStdString(ms_DECODED_IMAGE_PATH)));
                emit MqttManager::lastImage_signal(QString::fromStdString(ms_DECODED_IMAGE_PATH));
                s_previousmessage = s_lastmessage;
            }

        }
    }
    catch (const mqtt::exception& exc_ref) {
        client_t.disconnect()->wait();
        std::cerr << "MQTT error: " << exc_ref.what() << std::endl;
    }

}

