#include <iostream>

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QFile>
#include <QThread>

#include "int64filereader.h"
#include "int64worker.h"
#include "verylonginteger.h"

Int64Worker* createWorker(Int64Worker::Operation operation)
{
    Int64Worker* worker = new Int64Worker(operation);
    QThread* thread = new QThread;
    worker->moveToThread(thread);

    QObject::connect(thread, SIGNAL(started()), worker, SLOT(process()));
    QObject::connect(worker, SIGNAL(finished()), thread, SLOT(quit()));

    QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
    return worker;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCommandLineParser argsParser;
    auto helpOption = argsParser.addHelpOption();
    argsParser.addPositionalArgument("source", "source file with 64-bit signed integer numbers divided space or new line char");
    argsParser.process(a);
    if (argsParser.isSet(helpOption))
        argsParser.showHelp(0);
    else if (argsParser.positionalArguments().isEmpty())
        argsParser.showHelp(-1);
    else
    {
        QFile file(argsParser.positionalArguments()[0]);
        if (!file.open(QFile::ReadOnly))
        {
            std::cout << "Reading file error" << std::endl;
            return -1;
        }

        Int64FileReader reader(file);
        QObject::connect(&reader, &Int64FileReader::completePercentChanged, [](int percent){ std::cout << percent << "% completed" << std::endl;});

        qint64 firstNumber;
        bool firstNumberFilled = false;
        qint64 xorResult;
        VeryLongInteger sumResult;
        QScopedPointer<Int64Worker> xorWorker(createWorker([&xorResult](const qint64& right) { xorResult ^= right; }));
        QScopedPointer<Int64Worker> sumWorker(createWorker([&sumResult](const qint64& right) { sumResult += right; }));

        while (!reader.isFinished())
        {
            bool ok;
            qint64 result = reader.readNextNumber(&ok);
            if (ok)
            {
                if (!firstNumberFilled)
                {
                    firstNumberFilled = true;
                    firstNumber = result;
                    xorResult = result;
                }
                else
                {
                    xorWorker->addNumber(result);
                    sumWorker->addNumber(result);
                }
            }
        }

        if (!firstNumberFilled)
        {
            std::cout << "Reading file error" << std::endl;
            return -1;
        }
        else
        {
            sumWorker->stop();
            xorWorker->stop();

            while (!sumWorker->isFinished())
                QThread::msleep(1);

            VeryLongInteger sumRes(firstNumber);
            sumRes += sumResult;
            VeryLongInteger subResult(firstNumber);
            subResult -= sumResult;
            std::cout << "sum result:" << sumRes.toString().toStdString() << std::endl;
            std::cout << "sub result:" << subResult.toString().toStdString() << std::endl;

            while (!xorWorker->isFinished())
                QThread::msleep(1);

            std::cout << "xor result:" << xorResult << std::endl;
            return 0;
        }
        return a.exec();
    }
    return a.exec();
}
