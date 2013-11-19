#ifndef CONSUMER_H
#define CONSUMER_H

#include <QThread>
#include <QCoreApplication>

class Consumer : public QThread
{
    Q_OBJECT
    void run() Q_DECL_OVERRIDE;
};

#endif // CONSUMER_H
