#include <iostream>
#include <mqtt/async_client.h>

class callback : public virtual mqtt::callback {
public:
    void message_arrived(mqtt::const_message_ptr msg) override {
        std::cout << "Message received on topic " << msg->get_topic() << std::endl;
        std::cout << "Message content: " << msg->to_string() << std::endl;
    }
};

int main() {
    std::string address = "tcp://broker.emqx.io:1883";
    std::string client_id = "MQTT-Receiver";
    std::string topic = "/ynov/bordeaux/";

    mqtt::async_client client(address, client_id);

    mqtt::connect_options conn_opts;
    conn_opts.set_clean_session(true);

    callback cb;
    client.set_callback(cb);

    client.connect(conn_opts)->wait();

    mqtt::topic mqtt_topic(client, topic, 0);
    mqtt_topic.subscribe()->wait();

    while (true) {
        // Wait for messages
    }

    client.disconnect()->wait();
    return 0;
}