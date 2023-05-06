#include "mainwindow.h"

#include "ui_mainwindow.h"
#include "QDebug"
#include "QFileDialog"
#include <QString>
#include <QImage>
#include <QPainter>
#include <QPicture>
#include <QRegularExpression>
#include <mqttManager.h>


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BaseWindow)
{
    ui->setupUi(this);
    mqttManager = new MqttManager(this);

//    attrInit();
    connectSignalsSlots();     //on connecte les signaux/slots
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mqttManager;
//    MqttManager::quit();
}

void MainWindow::connectSignalsSlots()
{
    QObject::connect(mqttManager, SIGNAL(lastMessage_signal(QString)), this, SLOT(fillRawMessage(QString)));
    QObject::connect(mqttManager, SIGNAL(lastMessageDecoded_signal(QString)), this, SLOT(fillDecodedMessage(QString)));
    QObject::connect(mqttManager, SIGNAL(lastImage_signal(const QString)), this, SLOT(fillImage(const QString)));
}

void MainWindow::Connect()
{
    cout << "Coucou " << std::endl;


    mqttManager->Qos = ui->spinBoxQos->value();
    mqttManager->s_TOPIC = ui->lineEditTopic->text().toStdString();
    mqttManager->s_ADDRESS = ui->lineEditBroker->text().toStdString();
    mqttManager->s_CLIENT_ID = ui->lineEditClientId->text().toStdString();
    qDebug() << (mqttManager->Qos);
    qDebug() << QString::fromStdString(mqttManager->s_TOPIC);
    qDebug() << QString::fromStdString(mqttManager->s_ADDRESS);
    qDebug() << QString::fromStdString(mqttManager->s_CLIENT_ID);
    mqttManager->start();
    mqttManager->toggleState();
    MainWindow::updateButtonState(mqttManager->getState());

//    QString decode_message(QString image_path);

//    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
//                                                    "/home",
//                                                    tr("Images (*.png)"));
//    qDebug() << "Le fichier : " << fileName << " a été choisis";
//    QString decoded_message = decode_message(fileName);

//    qDebug() << "Le message caché est" << decoded_message<<"";

    //                                                             ui->plainTextEditRawMessage->setPlainText(decoded_message);
}


void MainWindow::updateButtonState(MqttManager::State state){
    QString s_InvCurrentState;

    if((state == MqttManager::State::Connect )|( state == MqttManager::State::Connected)){
        s_InvCurrentState="Disconnect";
    }
    else if((state == MqttManager::State::Disconnect) | (state == MqttManager::State::Disconnected)){
        s_InvCurrentState="Connect";
    }
    else{
        s_InvCurrentState="Unknown state";
    }
    ui->pushButton_2->setText(s_InvCurrentState);
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

void MainWindow::fillRawMessage(QString message){
//    qDebug()<< "fillRawMessage : " << message;
    ui->plainTextEditRawMessage->setPlainText(message);


}

void MainWindow::fillImage(const QString s_filepath){
    qDebug()<< " Image received in signal";
    ui->labelImage->setPicture(MainWindow::createQPictureFromPNG(s_filepath));
}

void MainWindow::fillDecodedMessage(QString message){
    qDebug()<< "fillDecodedMessage : " << message;
    ui->plainTextEditDecodedMessage->setPlainText(message);

}

QPicture MainWindow::createQPictureFromPNG(const QString& filePath)
{
    // Charger l'image PNG dans un QImage
    QImage image;
    if (!image.load(filePath))
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




