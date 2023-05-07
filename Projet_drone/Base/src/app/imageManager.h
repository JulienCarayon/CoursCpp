#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H
#include <QByteArray>
#include <QImage>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QPixmap>
#include <QBuffer>
#include <QDir>
#include <QString>

#include <QPainter>
#include <QPicture>

class ImageManager
{
public:
    ImageManager();
    QJsonObject ObjectFromString(const QString &s_STRING);
    void fromJson(const QJsonObject &JSON);
    QString showData(QString s_filepath);
    QPicture createQPictureFromPNG(const QString &s_FILEPATH);
    QString decode_message(QString s_filepath);
private:
    QString binaryToString(QString s_binary);
};

#endif // IMAGEMANAGER_H
