#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QFileDialog"
#include <QString>
#include <QImage>
#include <QRegularExpression>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::browseFile()
{
    QString decode_message(QString image_path);

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Images (*.png)"));
    qDebug() << "Le fichier : " << fileName << " a été choisis";
    QString decoded_message = decode_message(fileName);

    qDebug() << "Le message caché est" << decoded_message<<"";

    ui->plainTextEdit->setPlainText(decoded_message);
}



QString decode_message(QString image_path) {
    // Ouvre l'image
    QImage image(image_path);

    // Vérifie si l'image est valide
    if (image.isNull()) {
        qCritical() << "Erreur : Impossible d'ouvrir l'image " << image_path;
        return "";
    }

    // Convertit le message en une chaîne binaire
    QString message = "";
    QString bits = "";
    QString message_prefix = "";
    int message_length = 0;
    int actual_char = 0;
    int counter8bit = 0;

    // Cachage du message dans les pixels de l'image
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QRgb pixel = image.pixel(x, y);
            int r = qRed(pixel) & 1;
            bits += QString::number(r);
            ++counter8bit;

            if (counter8bit == 8) {
                bool ok = false;
                int bit = bits.toInt(&ok, 2);
                if (!ok) {
                    qCritical() << "Erreur : Impossible de convertir les bits en entier.";
                    return "";
                }
                char c = static_cast<char>(bit);
                message += c;
                bits = "";
                counter8bit = 0;
                ++actual_char;
            }

            // Vérifie si le message est trop long pour être caché dans l'image
            if (actual_char > image.width() * image.height()) {
                qCritical() << "Erreur : Le message est trop long pour être caché dans l'image.";
                return "";
            }

            QRegularExpression re("\\[(\\d*)\\]");
            QRegularExpressionMatch match = re.match(message);
            if (match.hasMatch()) {
                message_prefix = match.captured(0);
                message_length = match.captured(1).toInt();
                if (actual_char >= message_length + message_prefix.length()) {
                    break;
                }
            }
        }
        if (actual_char >= message_length + message_prefix.length()) {
            break;
        }
    }

    // Récupère le message caché dans l'image
    message = message.replace(message_prefix, "").left(message_length);
    return message;
}




//string decode_message(const string& image_path) {
//    qDebug() << "Function called";
//    //void decode_message(void) {
//    // Ouvre l'image en tant que fichier binaire
//    ifstream image_file(image_path, ios::binary);
//    if (!image_file.is_open()) {
//        cerr << "Impossible d'ouvrir le fichier d'image." << endl;
//        return "";
//    }
//    qDebug() << "After loading file";
//    // Lit l'en-tête de l'image pour obtenir sa taille
//    char header[54];
//    image_file.read(header, 54);
//    int image_size = *(int*)&header[34];
//    // Alloue un tampon pour stocker les données de l'image
//    char* image_data = new char[image_size];
//    // Lit les données de l'image dans le tampon
//    image_file.read(image_data, image_size);
//    // Extrait le message caché dans l'image
//    qDebug() << "After reading file";
//    string message;
//    for (long i = 0; i < image_size; i += 3) {
//        bitset<8> b(image_data[i]);
//        bitset<8> g(image_data[i+1]);
//        bitset<8> r(image_data[i+2]);
//        message += (char)r[0] + '0';
//        message += (char)g[0] + '0';
//        message += (char)b[0] + '0';
//    }
//    // Libère le tampon de données de l'image
//    delete[] image_data;
//    // Retourne le message caché dans l'image
////    return message;
//    qDebug() << "Le message est"<<QString::fromStdString(message);
//    return image_path;
//}
