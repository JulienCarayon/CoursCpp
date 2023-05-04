#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*---------------------------------------------------------------------------*/
/* Includes                                                                  */
/*---------------------------------------------------------------------------*/
#include <QMainWindow>
#include <QApplication>
#include <QObject>
#include <QString>

#include <QtMqtt/QtMqtt>
#include <QtMqtt/QMqttClient>

#include <QImage>

#include <QDebug>
#include "QDebug"
#include "QFileDialog"
#include <QString>

#include <QRegularExpression>

/*---------------------------------------------------------------------------*/
/* Defines                                                                   */
/*---------------------------------------------------------------------------*/

namespace Ui {
class MainWindow;
}

/*---------------------------------------------------------------------------*/
/* Class                                                                     */
/*---------------------------------------------------------------------------*/
/**
 *      todo mettre un descriptif de la class
 *
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*-----------------------------------------------------------------------*/
    /* Constructors & Destructor                                             */
    /*-----------------------------------------------------------------------*/
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    /*-----------------------------------------------------------------------*/
    /* Public Types                                                          */
    /*-----------------------------------------------------------------------*/

    /*-----------------------------------------------------------------------*/
    /* Public Methods                                                        */
    /*-----------------------------------------------------------------------*/
    QString decode_message(const QString& image_path);
//    void decode_message(void);

    /*-----------------------------------------------------------------------*/
    /* Signals                                                               */
    /*-----------------------------------------------------------------------*/

public slots:
    /*-----------------------------------------------------------------------*/
    /* Public Slots                                                          */
    /*-----------------------------------------------------------------------*/
    void browseFile(void);

private:
    Ui::MainWindow *ui;

    /*---------------------------------------------------------------*/
    /* Private Members                                               */
    /*---------------------------------------------------------------*/
//    QString message;
//    QString bits;
//    QString message_prefix;

    /*-----------------------------------------------------------------------*/
    /* Private Methods                                                       */
    /*-----------------------------------------------------------------------*/
    void attrInit();
    void connectSignalsSlots();

};
#endif // MAINWINDOW_H
