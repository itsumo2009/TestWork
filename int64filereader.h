#ifndef INT64FILEREADER_H
#define INT64FILEREADER_H

#include <QObject>
#include <QFile>

class Int64FileReader : public QObject
{
    Q_OBJECT
public:
    explicit Int64FileReader(QFile& sourceFile, QObject *parent = nullptr);

    qint64 readNextNumber(bool *ok);
    bool isFinished() const;

signals:
    void completePercentChanged(int percent);

private:
    void setPercent(int percent);
private:
    int _percent;
    QFile& _file;
};


#endif // INT64FILEREADER_H
