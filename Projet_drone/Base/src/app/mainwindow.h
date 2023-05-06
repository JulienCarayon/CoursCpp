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

    void fillRawMessage(QString message);
    void fillDecodedMessage(QString message);
    void fillImage(QString s_filepath);
private slots:


private:
    Ui::BaseWindow *ui;
//    void attrInit();
    void connectSignalsSlots();

    void updateButtonState(MqttManager::State currentState);
    void on_lineEditTopic_editingFinished(void);
    void on_lineEditBroker_editingFinished(void);
    void on_lineEditCliendId_editingFinished(void);

    QPicture createQPictureFromPNG(const QString &filePath);
};
#endif // MAINWINDOW_H
