#include "mainwindow.h"

#include "ui_mainwindow.h"
#include "QDebug"
#include "QFileDialog"
#include <QString>
#include <QImage>
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
//    connectSignalsSlots();     //on connecte les signaux/slots
}

MainWindow::~MainWindow()
{
    delete ui;
//    MqttManager::quit();
}

//void MainWindow::connectSignalsSlots()
//{
//    connect(threadElement, &ThreadElement::my_signal, this, &MainWindow::spinBox);
//}

void MainWindow::Connect()
{
    cout << "Coucou " << std::endl;



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

    if(state == MqttManager::State::Connect | state == MqttManager::State::Connected){
        s_InvCurrentState="Disconnect";
    }
    else if(state == MqttManager::State::Disconnect | state == MqttManager::State::Disconnected){
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

//void MainWindow::on_lineEditTopic_editingFinished()
//{
//}

//void MainWindow::on_lineEditBroker_editingFinished()
//{
//}

//void MainWindow::on_lineEditCliendId_editingFinished()
//{
//}
