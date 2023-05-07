#include "mainwindow.h"

#include "ui_mainwindow.h"


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BaseWindow)
{
    ui->setupUi(this);
    mqttManager = new MqttManager(this);
    ui->pushButton_2->setStyleSheet("background-color: green;");
    connectSignalsSlots();     //on connecte les signaux/slots
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mqttManager;
}

void MainWindow::connectSignalsSlots()
{
    QObject::connect(mqttManager, SIGNAL(lastMessage_signal(QString)), this, SLOT(fillRawMessage(QString)));
    QObject::connect(mqttManager, SIGNAL(lastMessageDecoded_signal(QString)), this, SLOT(fillDecodedMessage(QString)));
    QObject::connect(mqttManager, SIGNAL(lastImage_signal(const QString)), this, SLOT(fillImage(const QString)));
}

void MainWindow::connectButton()
{
    mqttManager->u8_qos = ui->spinBoxQos->value();
    mqttManager->s_topic = ui->lineEditTopic->text().toStdString();
    mqttManager->s_address = ui->lineEditBroker->text().toStdString();
    mqttManager->s_clientid = ui->lineEditClientId->text().toStdString();
    qDebug() << (mqttManager->u8_qos);
    qDebug() << QString::fromStdString(mqttManager->s_topic);
    qDebug() << QString::fromStdString(mqttManager->s_address);
    qDebug() << QString::fromStdString(mqttManager->s_clientid);
    mqttManager->start();
    mqttManager->toggleState();
    MainWindow::updateButtonState(mqttManager->getState());
}


void MainWindow::updateButtonState(MqttManager::State currentstate_t){
    QString s_InvCurrentState;

    if((currentstate_t == MqttManager::State::CONNECT )|( currentstate_t == MqttManager::State::CONNECTED)){
        s_InvCurrentState="Disconnect";
        ui->pushButton_2->setStyleSheet("background-color: red;");
    }
    else if((currentstate_t == MqttManager::State::DISCONNECT) | (currentstate_t == MqttManager::State::DISCONNECTED)){
        s_InvCurrentState="Connect";
        ui->pushButton_2->setStyleSheet("background-color: green;");
    }
    else{
        s_InvCurrentState="Unknown state";
    }
    ui->pushButton_2->setText(s_InvCurrentState);
}



void MainWindow::fillRawMessage(QString s_message){
    ui->plainTextEditRawMessage->setPlainText(s_message);
}

void MainWindow::fillImage(const QString s_filepath){
    ImageManager imagemanager;
    qDebug()<< " Image received in signal";
    ui->labelImage->setPicture(imagemanager.createQPictureFromPNG(s_filepath));
}

void MainWindow::fillDecodedMessage(QString s_message){
//    qDebug()<< "fillDecodedMessage : " << message;
    ui->plainTextEditDecodedMessage->setPlainText(s_message);

}





