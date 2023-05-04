#ifndef THREADELEMENT_H
#define THREADELEMENT_H

#include <QProcess>
#include <QThread>
#include <QDebug>
#define MAX_VALUE 10000
#define MODULO_DATA 10

class ThreadElement: public QThread
{
    Q_OBJECT

public:
    ThreadElement(QObject *parent);
signals:
    void my_signal(int i);

protected:
    void run(void);

private:
    int _counter;
};

#endif // THREADELEMENT_H
