#include <QCoreApplication>
#include <QApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>

#include "mqttManager.h"
#include "imageManager.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cout << "\t\tSTARTING PROCESS ...\n" << endl;

    ImageManager imageManager;
    imageManager.encryptData();

    QJsonObject json_data;
    json_data = imageManager.convertImagetoJson();
    QJsonDocument doc(json_data);
    QByteArray json_data_byte_array = doc.toJson();

    // MQTT class
    MqttManager mqtt_manager;
    if (!mqtt_manager.initConnection()) {
        cerr << "Error: failed to initiate MQTT connection" << endl;
        return 1;
    }
    mqtt_manager.publishData(json_data_byte_array);
    mqtt_manager.disconect();

    cout << "\n\t\t  PROCESS DONE ..." << endl;
    return a.exec();
}
