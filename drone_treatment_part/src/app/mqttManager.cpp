#include "mqttManager.h"

MqttManager::MqttManager() : m_client{s_ADDRESS, s_CLIENT_ID}
{
    if (s_ADDRESS.empty() || s_CLIENT_ID.empty())
    {
        cerr << "Error: s_ADDRESS or s_CLIENT_ID is not initialized" << endl;
    }
}

bool MqttManager::initConnection(void)
{
    try
    {
        cout << "Started connection ..." << endl;
        m_client.set_callback(callback);

        mqtt::connect_options connOpts;
        connOpts.set_keep_alive_interval(u8_INTERVAL);
        connOpts.set_clean_session(true);

        cout << "\tConnecting to broker : '" << s_ADDRESS << "'..." << endl;
        mqtt::token_ptr conntok = m_client.connect(connOpts);
        conntok->wait();

        cout << "\tConnected" << endl;
        return true;
    }
    catch(const mqtt::exception &exc)
    {
        cerr << "Error: " << exc.what() << endl;
        return false;
    }
}

void MqttManager::publishData(QByteArray jsonData)
{
    try
    {
        cout << "Sending message..." << endl;
        mqtt::message_ptr publish_message = mqtt::make_message(s_TOPIC, jsonData, jsonData.size());
        publish_message->set_qos(u8_QOS_MQTT);
        m_client.publish(publish_message)->wait();
        cout << "\tMessage sent ! "<< endl;
    }
    catch(const mqtt::exception &exc)
    {
        cerr << "Error : " << exc.what() << endl;
    }
}

void MqttManager::disconect()
{
    try
    {
        cout << "Disconnecting to broker : " << s_ADDRESS << endl;
        mqtt::token_ptr disctok = m_client.disconnect();
        disctok->wait();
        cout << "\tDisconnected !" << endl;
    }
    catch(const mqtt::exception &exc)
    {
        cerr << "Error : " << exc.what() << endl;
    }
}
