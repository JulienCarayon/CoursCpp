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
