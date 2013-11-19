#include <QCoreApplication>
#include <QWaitCondition>
#include <QMutex>
#include <QTime>
#include <stdio.h>
#include "Producer.h"
#include "Consumer.h"

using namespace std;

const int DataSize = 100000;
const int BufferSize = 8192;
char buffer[BufferSize];

QWaitCondition bufferNotEmpty;
QWaitCondition bufferNotFull;
QMutex mutex;
int numUsedBytes = 0;

void Producer::run()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    for (int i = 0; i < DataSize; ++i) {
        mutex.lock();
        if (numUsedBytes == BufferSize)
            bufferNotFull.wait(&mutex);
        mutex.unlock();

        buffer[i % BufferSize] = "ACGT"[(int)qrand() % 4];

        mutex.lock();
        ++numUsedBytes;
        bufferNotEmpty.wakeAll();
        mutex.unlock();
    }
}

void Consumer::run()
{
    for (int i = 0; i < DataSize; ++i) {
        mutex.lock();
        if (numUsedBytes == 0)
            bufferNotEmpty.wait(&mutex);
        mutex.unlock();

        fprintf(stderr, "%c", buffer[i % BufferSize]);

        mutex.lock();
        --numUsedBytes;
        bufferNotFull.wakeAll();
        mutex.unlock();
    }
    fprintf(stderr, "\n");
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Producer producer;
    Consumer consumer;
    producer.start();
    consumer.start();
    producer.wait();
    consumer.wait();

    return a.exec();
}
