#include <QCoreApplication>
#include <QApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <iostream>
#include <cstdlib>

#include "mqttManager.h"
#include "imageManager.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "\t\tSTARTING PROCESS ...\n" << endl;
    QCoreApplication a(argc, argv);
    ImageManager imageManager;
    MqttManager mqtt_manager;
    QJsonObject json_data;

    imageManager.encryptData();
    json_data = imageManager.convertImagetoJson();
    QJsonDocument doc(json_data);
    QByteArray json_data_byte_array = doc.toJson();

    if (!mqtt_manager.initConnection())
    {
        cerr << "Error: failed to initiate MQTT connection" << endl;
        return 1;
    }
    mqtt_manager.publishData(json_data_byte_array);
    mqtt_manager.disconect();
    imageManager.deleteImage();

    cout << "\n\t\t  PROCESS DONE ...\n\n" << endl;

    exit(0);
    return a.exec();
}
