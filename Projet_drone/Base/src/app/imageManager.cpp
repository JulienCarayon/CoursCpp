#include "imageManager.h"

ImageManager::ImageManager()
{

}

QJsonObject ImageManager::ObjectFromString(const QString &s_STRING)
{
    QJsonObject obj;

    QJsonDocument doc = QJsonDocument::fromJson(s_STRING.toUtf8());

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


void ImageManager::fromJson(const QJsonObject& JSON)
{
    QByteArray imagedatadecoded = QByteArray::fromBase64(JSON["data"].toString().toUtf8());
    QImage imagedecoded;
    imagedecoded.loadFromData(imagedatadecoded, "PNG");

    // Sauvegarde de l'image décodée dans un nouveau fichier PNG
    const QString s_NEWFILENAME = "decoded_image.png";
    imagedecoded.save(s_NEWFILENAME, "PNG");
}

QString ImageManager::showData(QString s_filepath)
{
    QImage img(s_filepath);
    QString s_binarymessage;
    for (int row = 0; row < img.height(); row++) {
        for (int col = 0; col < img.width(); col++) {
            QRgb rgb = img.pixel(col, row);
            s_binarymessage += QString::number(qRed(rgb) & 1);
            if (s_binarymessage.right(16) == "1111111111111110") {
                return ImageManager::binaryToString(s_binarymessage.left(s_binarymessage.length() - 16));
            }
            s_binarymessage += QString::number(qGreen(rgb) & 1);
            if (s_binarymessage.right(16) == "1111111111111110") {
                return ImageManager::binaryToString(s_binarymessage.left(s_binarymessage.length() - 16));
            }
            s_binarymessage += QString::number(qBlue(rgb) & 1);
            if (s_binarymessage.right(16) == "1111111111111110") {
                return ImageManager::binaryToString(s_binarymessage.left(s_binarymessage.length() - 16));
            }
        }
    }
    return binaryToString(s_binarymessage);
}

QString ImageManager::binaryToString(QString s_binary)
{
    QString s_message;
    for (int i = 0; i < s_binary.length(); i += 8) {
        s_message += QChar(s_binary.mid(i, 8).toInt(nullptr, 2));
    }
    return s_message;
}

QPicture ImageManager::createQPictureFromPNG(const QString& s_FILEPATH)
{
    // Charger l'image PNG dans un QImage
    QImage image;
    if (!image.load(s_FILEPATH))
    {
        // Gérer les erreurs de chargement de l'image
        return QPicture(); // Retourner une QPicture vide
    }

    // Créer une QPicture et dessiner l'image sur celle-ci
    QPicture picture;
    QPainter painter(&picture);
    painter.drawImage(QPoint(0, 0), image);
    painter.end();

    return picture;
}
