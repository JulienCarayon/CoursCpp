#include "mqttManager.h"


#include <QByteArray>
#include <QPixmap>
#include <QBuffer>
#include <QDir>


using namespace std;

string lastMessage = "";

class Callback : public virtual mqtt::callback {
public:
    void message_arrived(mqtt::const_message_ptr msg) override {

        std::cout << "Message received on topic " << msg->get_topic() << std::endl;
        lastMessage = msg->to_string();
//        cout << "Message content <START>" << msg->to_string() <<"<END>"<< std::endl;

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
    MqttManager::s_ADDRESS = "tcp://broker.emqx.io:1883" ;
    MqttManager::s_CLIENT_ID = "MQTT-Receiver" ;
    MqttManager::s_TOPIC= "/ynov/bordeaux/" ;

}

MqttManager::State MqttManager::getState()
{
    return currentState;
}

void MqttManager::toggleState()
{

    if(getState()==Connected){
        MqttManager::setState(Disconnect);
    }
    else{
        MqttManager::setState(Connect);
    }
}


void MqttManager::setState(State state)
{
    currentState = state;
}

void MqttManager::run()
{
    std::cout << "MqttManager started"<< std::endl;
    mqtt::async_client client_t(MqttManager::s_ADDRESS, MqttManager::s_CLIENT_ID);
    string previousMessage = lastMessage;
    try
    {
        while(1){
            if(MqttManager::getState()==Connect){
                mqtt::connect_options conn_opts;
                conn_opts.set_clean_session(true);

                Callback callback_t;
                client_t.set_callback(callback_t);

                client_t.connect(conn_opts)->wait();

                mqtt::topic mqtt_topic(client_t, MqttManager::s_TOPIC, MqttManager::Qos);
                mqtt_topic.subscribe()->wait();
                MqttManager::setState(Connected);
            }
            if (MqttManager::getState() == Disconnect){
                client_t.disconnect()->wait();
                MqttManager::setState(Disconnected);
                MqttManager::quit();
                break;
            }

            if(lastMessage != previousMessage){
                 cout << "<NEW Message incoming START>" << lastMessage <<"<NEW Message incoming END>"<< std::endl;
//                MqttManager::binaryToPngFile(QByteArray::fromStdString(lastMessage),QDir::currentPath().remove("/bin/release"));
                 emit MqttManager::lastMessage_signal(QString::fromStdString(lastMessage));
            }
            previousMessage = lastMessage;
//            std::cout << "\nMqttManager State:  "<< MqttManager::getState() << std::endl;
        }
    }
    catch (const mqtt::exception& exc_ref) {
        client_t.disconnect()->wait();
        std::cerr << "MQTT error: " << exc_ref.what() << std::endl;
    }

}



QPixmap MqttManager::binaryToPixmap(const QByteArray& binaryData)
{
    QPixmap pixmap;
    pixmap.loadFromData(binaryData, "PNG");
    return pixmap;
}

bool MqttManager::binaryToPngFile(const QByteArray& binaryData, const QString& filePath)
{
    QPixmap pixmap;
    if (!pixmap.loadFromData(binaryData, "PNG"))
    {
        qWarning() << "Failed to load image from binary data.";
        return false;
    }

    if (!pixmap.save(filePath, "PNG"))
    {
        qWarning() << "Failed to save PNG file.";
        return false;
    }

    return true;
}
