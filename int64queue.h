#ifndef INT64QUEUE_H
#define INT64QUEUE_H

#include <QMutex>
#include <QList>

class Int64Queue
{
public:
    bool isEmpty() const;

    void push(qint64 value);
    qint64 pop();

private:
    struct ScopedLock
    {
        ScopedLock(QMutex& mutex)
            : _mutex(mutex)
        {
            _mutex.lock();
        }

        ~ScopedLock()
        {
            _mutex.unlock();
        }

    private:
        QMutex& _mutex;
    };

private:
    QList<qint64> _list;
    mutable QMutex _mutex;
};

#endif // INT64QUEUE_H
