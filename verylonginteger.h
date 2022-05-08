#ifndef VERYLONGINTEGER_H
#define VERYLONGINTEGER_H

#include <QVector>

class VeryLongInteger
{
public:
    VeryLongInteger();
    VeryLongInteger(const QVector<qint64>& digits);
    VeryLongInteger(const qint64& initialValue);
    VeryLongInteger(const QString& stringValue);
public:
    bool operator <(const VeryLongInteger& right) const;
    bool operator >(const VeryLongInteger& right) const;
    bool operator ==(const VeryLongInteger& right) const;
    bool operator !=(const VeryLongInteger& right) const;

    VeryLongInteger& operator +=(const VeryLongInteger& right);
    VeryLongInteger& operator -=(const VeryLongInteger& right);

    QString toString() const;

    bool isNegative() const;
private:
    qint64 digit(int position) const;
    void setDigit(int position, qint64 value);

    int compareModule(const VeryLongInteger& right);

private:
    QVector<qint64> _digits;
    bool _negative;
};

#endif // VERYLONGINTEGER_H
