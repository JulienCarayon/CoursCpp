#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    string decode_message(const string& image_path);
//    void decode_message(void);

public slots:
    void browseFile(void);

private slots:
    void on_lineEditTopic_editingFinished();

private:
    Ui::BaseWindow *ui;

};
#endif // MAINWINDOW_H
