#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "QDebug"
#include "QFileDialog"
//#include <QString>
//#include <QImage>
//#include <QPainter>
//#include <QPicture>
#include <QRegularExpression>
#include <mqttManager.h>
#include <imageManager.h>

QT_BEGIN_NAMESPACE
namespace Ui { class BaseWindow; }
QT_END_NAMESPACE
using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void connectButton(void);
    void fillRawMessage(QString s_message);
    void fillDecodedMessage(QString s_message);
    void fillImage(QString s_filepath);

private:
    string ms_decodemessage(const string& s_imagepath);
    MqttManager *mqttManager;
    Ui::BaseWindow *ui;
    void connectSignalsSlots();
    void updateButtonState(MqttManager::State currentstate_t);
    QPicture createQPictureFromPNG(const QString &s_FILEPATH);
};
#endif // MAINWINDOW_H
