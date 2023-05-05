#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mqttManager.h"

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
    MqttManager *mqttManager;
    string decode_message(const string& image_path);
//    void decode_message(void);

public slots:
    void Connect(void);

private slots:
    void on_lineEditTopic_editingFinished();

private:
    Ui::BaseWindow *ui;
//    void attrInit();
//    void connectSignalsSlots();

    void updateButtonState(MqttManager::State currentState);
};
#endif // MAINWINDOW_H