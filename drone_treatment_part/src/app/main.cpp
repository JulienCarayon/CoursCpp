#include <QCoreApplication>
#include <QApplication>
#include <QImage>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <cstring>
#include <QDir>
#include <mqtt/async_client.h>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QBuffer>
#include <QByteArray>
#include <QPixmap>
#include <QBuffer>
using namespace std;

void hideData(QString inputImageFilename, QString outputImageFilename, QString message);
QString showData(QString inputImageFilename);
QString binaryToString(QString binary);
QString remove_backslash(QString message);
void testImageConversion(const QString& filename);

QJsonObject toJson(const QString& filename);
QImage fromJson(const QJsonObject& json);

const string s_ADDRESS{"tcp://broker.emqx.io:1883"};
const string s_CLIENT_ID{"MQTT-Receiver"};
const string s_TOPIC{"/ynov/bordeaux/CoursCpp"};
const string s_MESSAGE{"coucou les loulous"};
const uint8_t u8_INTERVAL{20};
const uint8_t u8_QOS_MQTT{0};

class Callback : public virtual mqtt::callback
{
public:
    virtual void connection_lost(const string &cause)
    {
        cout << "Connection lost" << endl;
    }

    virtual void delivery_complete(mqtt::delivery_token_ptr token) {}

    virtual void message_arrived(const string &topic, mqtt::message_ptr msg) {}
};


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cout << "Strating process ..." << endl;

    QString inputImageFilename = QDir::currentPath().remove("/bin/release") + "src/app/resouces/images/DroneIMG37337.png";
    QString outputImageFilename = "DroneIMG37337.png";
    QString message = "37°42'41.9\"S 144°59'33.0\"E";

    hideData(inputImageFilename, outputImageFilename, message);

    QImage img(outputImageFilename);
    QString hiddenMessage = showData(outputImageFilename);
    cout << "Hidden Message : " << hiddenMessage.toUtf8().toStdString() << endl;

    QJsonObject json_data;
    json_data = toJson(outputImageFilename);
    cout <<" JSON : " << json_data["data"].toString().toStdString() << endl;
    fromJson(json_data);

  // MQTT sent binary data
    try
    {
        mqtt::async_client client(s_ADDRESS, s_CLIENT_ID);
        Callback callback;
        client.set_callback(callback);

        mqtt::connect_options connOpts;
        connOpts.set_keep_alive_interval(u8_INTERVAL);
        connOpts.set_clean_session(true);

        cout << "Connecting to broker: '" << s_ADDRESS << "'..." << endl;
        mqtt::token_ptr conntok = client.connect(connOpts);
        conntok->wait();

        cout << "Connected" << endl;

        cout << "Sending message..." << endl;

        //std::string jsonString = json_data.toJson().toStdString();    //not work
        cout <<" JSON 2 : " << json_data["data"].toString().toStdString() << endl;
        QJsonDocument doc(json_data);
        QByteArray jsonData = doc.toJson();
        //mqtt::message_ptr pubmsg = mqtt::make_message(s_TOPIC, imageData.toStdString(),0,false);  //with binary file
        mqtt::message_ptr pubmsg = mqtt::make_message(s_TOPIC, jsonData, jsonData.size());
        pubmsg->set_qos(u8_QOS_MQTT);
        client.publish(pubmsg)->wait();

        cout << "Message sent : " + s_MESSAGE << endl;

        cout << "Disconnecting..." << endl;
        mqtt::token_ptr disctok = client.disconnect();
        disctok->wait();

        cout << "Disconnected" << endl;
    }
    catch (const mqtt::exception &exc)
    {
        cerr << "Error: " << exc.what() << endl;
        return 1;
    }

    return a.exec();
}

QString remove_backslash(QString message) {
    message.remove("\\");
    cout << "Message : " <<message.toUtf8().toStdString() << endl;
    return message;
}

QString messageToBinary(QString message)
{
    QString binary;
    for (int i = 0; i < message.length(); i++) {
        binary += QString("%1").arg(message[i].unicode(), 8, 2, QChar('0'));
    }
    return binary + "1111111111111110";
}

void hideData(QString inputImageFilename, QString outputImageFilename, QString message)
{
    QImage img(inputImageFilename);
    QString binary_message = messageToBinary(remove_backslash(message));
    int bit_index = 0;
    int width = img.width();
    int height = img.height();
    for (int row = 0; row < img.height(); row++) {
        for (int col = 0; col < img.width(); col++) {
            QRgb rgb = img.pixel(col, row);
            int red = qRed(rgb);
            int test = qGray(rgb);
            int green = qGreen(rgb);
            int blue = qBlue(rgb);
            if (bit_index < binary_message.length()) {
                red = (red & ~1) | (binary_message[bit_index++].digitValue());
            }
            if (bit_index < binary_message.length()) {
                green = (green & ~1) | (binary_message[bit_index++].digitValue());
            }
            if (bit_index < binary_message.length()) {
                blue = (blue & ~1) | (binary_message[bit_index++].digitValue());
            }
            if (row >= 0 && row < height && col >= 0 && col < width) {
                img.setPixel(col, row, qRgb(red, green, blue));
            }
            if (bit_index >= binary_message.length()) {
                img.save(outputImageFilename);
                return;
            }
        }
    }
    img.save(outputImageFilename);
}

QString binaryToString(QString binary)
{
    QString message;
    for (int i = 0; i < binary.length(); i += 8) {
        message += QChar(binary.mid(i, 8).toInt(nullptr, 2));
    }
    return message;
}

QString showData(QString inputImageFilename)
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

QJsonObject toJson(const QString& filename)
{
    // Chargement de l'image PNG
    QImage image(filename);
    QJsonObject json;
    json["width"] = image.width();
    json["height"] = image.height();
    QByteArray imageData;
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    json["data"] = QString::fromLatin1(imageData.toBase64().data());
    return json;
}

QImage fromJson(const QJsonObject& json)
{
    QByteArray imageDataDecoded = QByteArray::fromBase64(json["data"].toString().toUtf8());
    QImage imageDecoded;
    imageDecoded.loadFromData(imageDataDecoded, "PNG");

    // Sauvegarde de l'image décodée dans un nouveau fichier PNG
    QString newFilename = "decoded_image.png";
    imageDecoded.save(newFilename, "PNG");
    return imageDecoded;
}
