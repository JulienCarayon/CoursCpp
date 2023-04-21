#include <iostream>
#include <mqtt/async_client.h>

class Callback : public virtual mqtt::callback {
public:
    void message_arrived(mqtt::const_message_ptr msg) override {
        std::cout << "Message received on topic " << msg->get_topic() << std::endl;
        std::cout << "Message content: " << msg->to_string() << std::endl;
    }

    virtual void connection_lost(const std::string& cause_ref) override {
        std::cout << "\nConnection lost" << std::endl;
        if (!cause_ref.empty())
            std::cout << "\tcause: " << cause_ref << std::endl;
    }
};

int main() {
    const std::string s_ADDRESS = "tcp://broker.emqx.io:1883";
    const std::string s_CLIENT_ID = "MQTT-Receiver";
    const std::string s_TOPIC = "/ynov/bordeaux/";
    mqtt::async_client client_t(s_ADDRESS, s_CLIENT_ID);
    try {
        mqtt::connect_options conn_opts;
        conn_opts.set_clean_session(true);

        Callback callback_t;
        client_t.set_callback(callback_t);

        client_t.connect(conn_opts)->wait();

        mqtt::topic mqtt_topic(client_t, s_TOPIC, 0);
        mqtt_topic.subscribe()->wait();

        while (true) {
            // Wait for messages
        }
    }
    catch (const mqtt::exception& exc_ref) {
        client_t.disconnect()->wait();
        std::cerr << "MQTT error: " << exc_ref.what() << std::endl;
        return 1;
    }
    
    return 0;
}