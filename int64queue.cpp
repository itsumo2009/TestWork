#include "int64queue.h"

bool Int64Queue::isEmpty() const
{
    ScopedLock lock(_mutex);
    return _list.isEmpty();
}

void Int64Queue::push(qint64 value)
{
    ScopedLock lock(_mutex);
    _list.push_back(value);
}

qint64 Int64Queue::pop()
{
    Q_ASSERT(!isEmpty());
    ScopedLock lock(_mutex);
    qint64 result = _list.first();
    _list.pop_front();
    return result;
}
