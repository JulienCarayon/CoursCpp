#include <iostream>
#include <mqtt/async_client.h>

const std::string s_ADDRESS { "tcp://broker.emqx.io:1883" };
const std::string s_CLIENT_ID { "MQTT-Receiver" };
const std::string s_TOPIC { "/ynov/bordeaux/" };

class Callback : public virtual mqtt::callback
{
public:
    virtual void connection_lost(const std::string& cause_ref) {
        std::cout << "Connection lost" << std::endl;
    }

    virtual void delivery_complete(mqtt::delivery_token_ptr token) {}

    virtual void message_arrived(const std::string& topic_ref, mqtt::message_ptr msg) {}
};

int main()
{
    try {
        mqtt::async_client client(s_ADDRESS, s_CLIENT_ID);
        Callback Callback;
        client.set_callback(Callback);

        mqtt::connect_options connOpts;
        connOpts.set_keep_alive_interval(20);
        connOpts.set_clean_session(true);

        std::cout << "Connecting to broker: '" << s_ADDRESS << "'..." << std::endl;
        mqtt::token_ptr conntok = client.connect(connOpts);
        conntok->wait();

        std::cout << "Connected" << std::endl;

        std::cout << "Sending message..." << std::endl;
        mqtt::message_ptr pubmsg = mqtt::make_message(s_TOPIC, "coucou c'est l'homme le plus intelligent qui envoie un message\nPS : Merci ChatGPT");
        pubmsg->set_qos(0);
        client.publish(pubmsg)->wait();

        std::cout << "Message sent" << std::endl;

        std::cout << "Disconnecting..." << std::endl;
        mqtt::token_ptr disctok = client.disconnect();
        disctok->wait();

        std::cout << "Disconnected" << std::endl;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        return 1;
    }

    return 0;
}
