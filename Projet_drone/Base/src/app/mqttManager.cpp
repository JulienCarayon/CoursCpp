#include "mqttManager.h"
using namespace std;

class Callback : public virtual mqtt::callback {
public:
    void message_arrived(mqtt::const_message_ptr msg) override {

        std::cout << "Message received on topic " << msg->get_topic() << std::endl;
        cout << "Message content: " << msg->to_string() << std::endl;
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

    try
    {
        while(1){
            if(MqttManager::getState()==Connect){
                mqtt::connect_options conn_opts;
                conn_opts.set_clean_session(true);

                Callback callback_t;
                client_t.set_callback(callback_t);

                client_t.connect(conn_opts)->wait();

                mqtt::topic mqtt_topic(client_t, MqttManager::s_TOPIC, 0);
                mqtt_topic.subscribe()->wait();
                MqttManager::setState(Connected);
            }
            if (MqttManager::getState() == Disconnect){
                client_t.disconnect()->wait();
                MqttManager::setState(Disconnected);
                MqttManager::quit();
                break;
            }
//            std::cout << "\nMqttManager State:  "<< MqttManager::getState() << std::endl;
        }
    }
    catch (const mqtt::exception& exc_ref) {
        client_t.disconnect()->wait();
        std::cerr << "MQTT error: " << exc_ref.what() << std::endl;
    }

}

