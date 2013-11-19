#ifndef PRODUCER_H
#define PRODUCER_H

#include <QThread>
#include <QCoreApplication>

class Producer : public QThread
{
    Q_OBJECT
    void run() Q_DECL_OVERRIDE;
};

#endif // PRODUCER_H
