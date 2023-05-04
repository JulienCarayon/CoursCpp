#include "mqttManager.h"

MqttManager::MqttManager()
{

}




int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QMqttClient mqttClient;

    mqttClient.setHostname("broker.emqx.io");
    mqttClient.setPort(1883);
    mqttClient.setClientId("JuDoJo");

    mqttClient.connectToHost();

    // Attendre que le client MQTT soit connecté au broker
    if (!mqttClient.waitForConnected(5000)) {
        qDebug() << "Erreur de connexion : " << mqttClient.lastError().errorString();
        return 1;
    }

    QByteArray message = "coucou";
    QString topic = "/ynov/bordeaux/CoursCpp";

    mqttClient.publish(topic, message);

    mqttClient.disconnectFromHost();

    return 0;
}
