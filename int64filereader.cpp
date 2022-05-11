#include "int64filereader.h"

Int64FileReader::Int64FileReader(QFile& sourceFile, QObject *parent)
    : QObject(parent)
    , _percent(0)
    , _file(sourceFile)
{

}

qint64 Int64FileReader::readNextNumber(bool* ok)
{
    QString number;
    while (!_file.atEnd())
    {
        QByteArray nextChar = _file.read(1);
        if (nextChar.isEmpty())
            break;
        if (nextChar[0] == ' ')
            break;
        if (nextChar[0] == '\n')
            break;
        number.append(nextChar);
    }

    setPercent(_file.pos() * 100 / _file.size());
    if (number.isEmpty())
    {
        *ok = false;
        return 0;
    }
    return number.toLongLong(ok);
}

bool Int64FileReader::isFinished() const
{
    return _file.atEnd();
}

void Int64FileReader::setPercent(int percent)
{
    if (_percent == percent)
        return;

    _percent = percent;
    emit completePercentChanged(percent);
}

