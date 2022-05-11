#include "int64worker.h"

#include <QThread>

Int64Worker::Int64Worker(Operation op, QObject *parent)
    : QObject(parent)
    , _stopRequested(false)
    , _finished(false)
    , _operation(op)
{

}

void Int64Worker::addNumber(qint64 number)
{
    _numbers.push(number);
}

bool Int64Worker::isFinished() const
{
    return _finished;
}

void Int64Worker::process()
{
    while (!_stopRequested)
    {
        while (_numbers.isEmpty() && !_stopRequested)
            QThread::msleep(1);

        while (!_numbers.isEmpty())
            _operation(_numbers.pop());
    }
    _finished = true;
    emit finished();
}

void Int64Worker::stop()
{
    _stopRequested = true;
}
