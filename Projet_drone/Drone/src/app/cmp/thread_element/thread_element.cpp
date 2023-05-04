#include "thread_element.h"

ThreadElement::ThreadElement(QObject *parent): QThread(parent)
{
    _counter = 0;
}

void ThreadElement::run()
{
    while(_counter < MAX_VALUE)
    {
        _counter++;
        if (_counter % MODULO_DATA == 0)
        {
            emit my_signal(_counter);
        }
        msleep(200);
    }
}

