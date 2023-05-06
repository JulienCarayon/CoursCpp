#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <iostream>
#include <QString>
#include <QJsonObject>
#include <QImage>
#include <QBuffer>
#include <QDir>

#define END_OF_MESSAGE_INDICATOR "1111111111111110"

using namespace std;

class ImageManager
{
public:
    ImageManager();
    void encryptData(void);
    QString removeBackslash(void);
    QString messageToBinary(QString message);
    QJsonObject convertImagetoJson(void);

private:
    QString m_inputImageFilename =  QDir::currentPath().remove("/bin/release") +"/src/app/resources/images/DroneIMG37337.png";
    QString m_outputImageFilename = "DroneIMG37337.png";
    QString m_message = "37°42'41.9\"S 144°59'33.0\"E";
};

#endif // IMAGEMANAGER_H
