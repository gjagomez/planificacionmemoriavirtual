#ifndef SEMAPHORESCENARIOS_H
#define SEMAPHORESCENARIOS_H

#include <QString>
#include <QVector>

struct ConcurrencyStep
{
    int tick = 0;
    QString actor;
    QString action;
    QString semaphoreSnapshot;
};

class SemaphoreScenario
{
public:
    virtual ~SemaphoreScenario() = default;
    virtual QString name() const = 0;
    virtual QVector<ConcurrencyStep> simulate() const = 0;
};

class ProducerConsumerScenario : public SemaphoreScenario
{
public:
    ProducerConsumerScenario(int producers, int consumers, int bufferSize, int cycles);
    QString name() const override;
    QVector<ConcurrencyStep> simulate() const override;

private:
    int m_producers;
    int m_consumers;
    int m_bufferSize;
    int m_cycles;
};

class ReadersWritersScenario : public SemaphoreScenario
{
public:
    ReadersWritersScenario(int readers, int writers, int cycles);
    QString name() const override;
    QVector<ConcurrencyStep> simulate() const override;

private:
    int m_readers;
    int m_writers;
    int m_cycles;
};

class SleepingBarberScenario : public SemaphoreScenario
{
public:
    SleepingBarberScenario(int chairs, int customers);
    QString name() const override;
    QVector<ConcurrencyStep> simulate() const override;

private:
    int m_chairs;
    int m_customers;
};

#endif // SEMAPHORESCENARIOS_H
