#include "verylonginteger.h"

namespace {

    const qint64 module = Q_INT64_C(1000000000000000000);
}

VeryLongInteger::VeryLongInteger()
    : _negative(false)
{

}

VeryLongInteger::VeryLongInteger(const QVector<qint64> &digits)
    : _negative(false)
{
    if (!digits.empty())
    {
        _negative = digits[0] < 0;
        for (size_t i = digits.size() - 1; i > 0; --i)
        {
            _digits.push_back(digits[i]);
            Q_ASSERT(digits[i] >= 0);
            Q_ASSERT(digits[i] < module);
        }
        _digits.push_back(std::abs(digits[0]));
    }
}

VeryLongInteger::VeryLongInteger(const qint64 &initialValue)
{
    _digits.push_back(std::abs(initialValue));
    _negative = initialValue < 0;
    if (_digits[0] >= module)
    {
        _digits.push_back(_digits[0] / module);
        _digits[0] %= module;
    }
}

VeryLongInteger::VeryLongInteger(const QString &stringValue)
{
    _negative = stringValue.startsWith('-');
    for (int i = _negative? 1 : 0; i < stringValue.length(); i++)
    {
        int value = stringValue.mid(i, 1).toUInt();

        for (int j=_digits.size() - 1; j>=0; --j)
        {
            if (_digits[j] > module / 10)
            {
                if (j+1 < _digits.size())
                    _digits[j+1] += _digits[j] / (module / 10);
                else
                    _digits.push_back(_digits[j] / (module / 10));

                _digits[j] %= module / 10;
            }

            _digits[j] *= 10;
        }
        if (_digits.empty())
            _digits.push_back(value);
        else
            _digits[0] += value;
    }
}

bool VeryLongInteger::operator <(const VeryLongInteger &right) const
{
    if (_negative != right._negative)
        return _negative;

    for (int  i = std::max(_digits.size(), right._digits.size()) - 1; i >= 0; --i)
        if (digit(i) == right.digit(i))
            continue;
        else
            return digit(i) < right.digit(i);
    return false;
}

bool VeryLongInteger::operator >(const VeryLongInteger &right) const
{
    return right < *this;
}

bool VeryLongInteger::operator ==(const VeryLongInteger &right) const
{
    if (_negative != right._negative)
        return false;

    for (int  i = std::max(_digits.size(), right._digits.size()) - 1; i >= 0; --i)
        if (digit(i) == right.digit(i))
            continue;
        else
            return false;

    return true;
}

bool VeryLongInteger::operator !=(const VeryLongInteger &right) const
{
    return !(*this == right);
}

VeryLongInteger &VeryLongInteger::operator +=(const VeryLongInteger &right)
{
    int acc = 0;

    if (_negative == right._negative)
    {
        for (int i =0; i <= qMax(_digits.size(), right._digits.size()); ++i)
        {
            if (digit(i) >= module - right.digit(i) - acc)
            {
                setDigit(i, digit(i) - module + right.digit(i) + acc);
                acc = 1;
            }
            else
            {
                setDigit(i, digit(i) + right.digit(i) + acc);
                acc = 0;
            }
        }
    }
    else
    {
        switch (compareModule(right)) {
            case 0:
                _negative = false;
                _digits.clear();
            break;
            case 1:
                for (int i =0; i < qMax(_digits.size(), right._digits.size()); ++i)
                {
                    if (digit(i) < right.digit(i) + acc)
                    {
                        setDigit(i, digit(i) - right.digit(i) - acc + module);
                        acc = 1;
                    }
                    else
                    {
                        setDigit(i, digit(i) - right.digit(i) - acc);
                        acc = 0;
                    }
                }
            break;
            case -1:
                _negative = !_negative;
                for (int i =0; i < qMax(_digits.size(), right._digits.size()); ++i)
                {
                    if (right.digit(i) < digit(i) + acc)
                    {
                        setDigit(i, right.digit(i) - digit(i) - acc + module);
                        acc = 1;
                    }
                    else
                    {
                        setDigit(i,  right.digit(i) - digit(i) - acc);
                        acc = 0;
                    }
                }
            break;
        }
    }
    return *this;
}

VeryLongInteger &VeryLongInteger::operator -=(const VeryLongInteger &right)
{
    int acc = 0;

    if (_negative == !right._negative)
    {
        for (int i =0; i <= qMax(_digits.size(), right._digits.size()); ++i)
        {
            if (digit(i) >= module - right.digit(i) - acc)
            {
                setDigit(i, digit(i) - module + right.digit(i) + acc);
                acc = 1;
            }
            else
            {
                setDigit(i, digit(i) + right.digit(i) + acc);
                acc = 0;
            }
        }
    }
    else
    {
        switch (compareModule(right)) {
            case 0:
                _negative = false;
                _digits.clear();
            break;
            case 1:
                for (int i =0; i < qMax(_digits.size(), right._digits.size()); ++i)
                {
                    if (digit(i) < right.digit(i) + acc)
                    {
                        setDigit(i, digit(i) - right.digit(i) - acc + module);
                        acc = 1;
                    }
                    else
                    {
                        setDigit(i, digit(i) - right.digit(i) - acc);
                        acc = 0;
                    }
                }
            break;
            case -1:
                for (int i =0; i < qMax(_digits.size(), right._digits.size()); ++i)
                {
                    if (right.digit(i) < digit(i) + acc)
                    {
                        setDigit(i, right.digit(i) - digit(i) - acc + module);
                        acc = 1;
                    }
                    else
                    {
                        setDigit(i,  right.digit(i) - digit(i) - acc);
                        acc = 0;
                    }
                }
            break;
        }
    }
    return *this;
}

QString VeryLongInteger::toString() const
{
    QString result;
    if (_negative)
        result += '-';
    for (int i=_digits.size() - 1; i>=0; --i)
    {
        if (i == _digits.size() - 1)
            result += QString::number(_digits[i]);
        else
        {
            result += QString("%1").arg(_digits[i], 18, 10, QChar('0'));
        }
    }

    return result;
}

bool VeryLongInteger::isNegative() const
{
    return _negative;
}

qint64 VeryLongInteger::digit(int position) const
{
    if (position < _digits.size())
        return _digits[position];
    else
        return 0;
}

void VeryLongInteger::setDigit(int position, qint64 value)
{
    if (position == _digits.size())
    {
        if (value != 0)
            _digits.push_back(value);
        return;
    }
    _digits[position] = value;
}

int VeryLongInteger::compareModule(const VeryLongInteger &right)
{
    for (int i=qMax(_digits.size(), right._digits.size()) - 1; i>=0; --i)
    {
        if (digit(i) == right.digit(i))
            continue;
        else
            return digit(i) < right.digit(i) ? - 1 : 1;
    }

    return 0;
}
