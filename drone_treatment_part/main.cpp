#include <QCoreApplication>
#include <QApplication>
#include <QImage>
#include <QDebug>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QBuffer>

#include "mqttmanager.h"

using namespace std;

void hideData(QString inputImageFilename, QString outputImageFilename, QString message);
QString remove_backslash(QString message);
QString messageToBinary(QString message);
QJsonObject toJson(const QString& filename);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cout << "Strating process ..." << endl;

    QString inputImageFilename = QDir::currentPath().remove("/bin/release") + "src/app/resouces/images/DroneIMG37337.png";
    QString outputImageFilename = "DroneIMG37337.png";
    QString message = "37°42'41.9\"S 144°59'33.0\"E";

    hideData(inputImageFilename, outputImageFilename, message);

    QJsonObject json_data;
    json_data = toJson(outputImageFilename);
    QJsonDocument doc(json_data);
    QByteArray jsonData = doc.toJson();

    MqttManager mqtt_manager;
    if (!mqtt_manager.initConnection()) {
        cerr << "Error: failed to initiate MQTT connection" << endl;
        return 1;
    }
    mqtt_manager.publishData(jsonData);
    mqtt_manager.disconect();

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

QJsonObject toJson(const QString& filename)
{
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
