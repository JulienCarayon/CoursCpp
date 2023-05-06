#include "mqttManager.h"


#include <QByteArray>
#include <QPixmap>
#include <QBuffer>
#include <QDir>

#include <QImage>
#include <QJsonObject>
#include <QJsonDocument>  //pas utile ?
#include <QByteArray>


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
                 const QJsonObject Array = MqttManager::ObjectFromString(QString::fromStdString(lastMessage));
                 MqttManager::fromJson(Array);
                 emit MqttManager::lastMessageDecoded_signal(MqttManager::showData(QString::fromStdString(s_DECODED_IMAGE_PATH)));
                 MqttManager::fromJson(Array);
                 emit MqttManager::lastImage_signal(QString::fromStdString(s_DECODED_IMAGE_PATH));
            }
            previousMessage = lastMessage;
        }
    }
    catch (const mqtt::exception& exc_ref) {
        client_t.disconnect()->wait();
        std::cerr << "MQTT error: " << exc_ref.what() << std::endl;
    }

}

QJsonObject MqttManager::ObjectFromString(const QString& in)
{
    QJsonObject obj;

    QJsonDocument doc = QJsonDocument::fromJson(in.toUtf8());

    // check validity of the document
    if(!doc.isNull())
    {
        if(doc.isObject())
        {
            obj = doc.object();
        }
        else
        {
            qDebug() << "Document is not an object";
        }
    }
    else
    {
        qDebug() << "Invalid JSON...\n" ;
    }

    return obj;
}


void MqttManager::fromJson(const QJsonObject& json)
{
    QByteArray imageDataDecoded = QByteArray::fromBase64(json["data"].toString().toUtf8());
    QImage imageDecoded;
    imageDecoded.loadFromData(imageDataDecoded, "PNG");

    // Sauvegarde de l'image décodée dans un nouveau fichier PNG
    QString newFilename = "decoded_image.png";
    imageDecoded.save(newFilename, "PNG");
}

QString MqttManager::showData(QString inputImageFilename)
{
    QImage img(inputImageFilename);
    QString binary_message;
    for (int row = 0; row < img.height(); row++) {
        for (int col = 0; col < img.width(); col++) {
            QRgb rgb = img.pixel(col, row);
            binary_message += QString::number(qRed(rgb) & 1);
            if (binary_message.right(16) == "1111111111111110") {
                 return binaryToString(binary_message.left(binary_message.length() - 16));
            }
            binary_message += QString::number(qGreen(rgb) & 1);
            if (binary_message.right(16) == "1111111111111110") {
                 return binaryToString(binary_message.left(binary_message.length() - 16));
            }
            binary_message += QString::number(qBlue(rgb) & 1);
            if (binary_message.right(16) == "1111111111111110") {
                 return binaryToString(binary_message.left(binary_message.length() - 16));
            }
        }
    }
    return binaryToString(binary_message);
}

QString MqttManager::binaryToString(QString binary)
{
    QString message;
    for (int i = 0; i < binary.length(); i += 8) {
        message += QChar(binary.mid(i, 8).toInt(nullptr, 2));
    }
    return message;
}
