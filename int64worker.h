#ifndef INT64WORKER_H
#define INT64WORKER_H

#include <QObject>

#include "int64queue.h"

#include <functional>

class Int64Worker : public QObject
{
    Q_OBJECT
public:
    typedef std::function<void(const qint64)> Operation;
public:
    explicit Int64Worker(Operation op, QObject *parent = nullptr);
    void addNumber(qint64 number);

    bool isFinished() const;
signals:
    void finished();

public slots:
    void process();
    void stop();

private:
    Int64Queue _numbers;
    bool _stopRequested;
    bool _finished;
    Operation _operation;
};


#endif // INT64WORKER_H
