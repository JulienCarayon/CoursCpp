#include "imageManager.h"

ImageManager::ImageManager()
{

}

void ImageManager::encryptData(void)
{
    cout << "Encrypt data ..." << endl;
    cout << "\tdata : " << m_message.toStdString() << endl;
    QImage img(m_inputImageFilename);
    bool saved = false;
    QString binary_message = messageToBinary(removeBackslash());
    int s32_bit_index = 0;
    int s32_width = img.width();
    int s32_height = img.height();
    for (int s32_row = 0; s32_row < s32_height; s32_row++)
    {
        for (int s32_col = 0; s32_col < s32_width; s32_col++)
        {
            QRgb rgb = img.pixel(s32_col, s32_row);
            int s32_red = qRed(rgb);
            int s32_green = qGreen(rgb);
            int s32_blue = qBlue(rgb);

            if (s32_bit_index < binary_message.length())
            {
                s32_red = (s32_red & ~1) | (binary_message[s32_bit_index++].digitValue());
            }
            if (s32_bit_index < binary_message.length())
            {
                s32_green = (s32_green & ~1) | (binary_message[s32_bit_index++].digitValue());
            }
            if (s32_bit_index < binary_message.length())
            {
                s32_blue = (s32_blue & ~1) | (binary_message[s32_bit_index++].digitValue());
            }
            if (s32_row >= 0 && s32_row < s32_height && s32_col >= 0 && s32_col < s32_width)
            {
                img.setPixel(s32_col, s32_row, qRgb(s32_red, s32_green, s32_blue));
            }
            if (s32_bit_index >= binary_message.length())
            {
                saved = img.save(m_outputImageFilename);
                if (!saved)
                {
                    cout << "s32_bit_index -> Error saving image" << endl;
                }
                else
                {
                    cout << "\tEncryption done !" <<endl;
                }
                return;
            }
        }
    }
    saved = img.save(m_outputImageFilename);

    if (!saved)
    {
        cout << "Error saving image" << endl;
    } else {
        cout << "\tEncryption done !" <<endl;
    }
}

QString ImageManager::removeBackslash(void)
{
    return m_message.remove("\\");
}

QString ImageManager::messageToBinary(QString m_message)
{
    QString binary;
    for (int s32_i = 0; s32_i < m_message.length(); s32_i++)
    {
        binary += QString("%1").arg(m_message[s32_i].unicode(), 8, 2, QChar('0'));
    }
    return binary + END_OF_MESSAGE_INDICATOR;
}

QJsonObject ImageManager::convertImagetoJson(void)
{
    QImage image(m_outputImageFilename);
    QJsonObject json;
    QByteArray imageData;
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    json["data"] = QString::fromLatin1(imageData.toBase64().data());
    return json;
}

void ImageManager::deleteImage(void)
{
    cout << "Deleting image " << m_outputImageFilename.toStdString() << " from drone ressources ..." << endl;
    QFile file(m_outputImageFilename);
    if (file.exists())
    {
        if (file.remove())
        {
            cout << "\tDeleted file !";
        }
        else
        {
            cout << "\Error during deleting process !";
        }
    }
    else
    {
        cout << "\The file doesn't exist";
    }
}
