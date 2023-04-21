#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
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

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
