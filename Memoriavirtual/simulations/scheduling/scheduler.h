#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <QString>
#include <QVector>

struct Process
{
    QString pid;
    int arrivalTime = 0;
    int burstTime = 0;
    int priority = 0;
};

struct ScheduleEvent
{
    QString pid;
    int startTime = 0;
    int endTime = 0;
};

struct ProcessReport
{
    QString pid;
    int firstStart = -1;
    int finishTime = 0;
    int waitingTime = 0;
    int turnaroundTime = 0;
    int responseTime = 0;
};

struct SchedulingResult
{
    QVector<ScheduleEvent> timeline;
    QVector<ProcessReport> reports;
    double averageWaiting = 0.0;
    double averageTurnaround = 0.0;
    double averageResponse = 0.0;
};

class SchedulingAlgorithm
{
public:
    virtual ~SchedulingAlgorithm() = default;
    virtual QString name() const = 0;
    virtual SchedulingResult schedule(const QVector<Process> &processes, int quantum = 1) const = 0;
};

class FcfsAlgorithm : public SchedulingAlgorithm
{
public:
    QString name() const override;
    SchedulingResult schedule(const QVector<Process> &processes, int quantum = 1) const override;
};

class SjfAlgorithm : public SchedulingAlgorithm
{
public:
    QString name() const override;
    SchedulingResult schedule(const QVector<Process> &processes, int quantum = 1) const override;
};

class SrtfAlgorithm : public SchedulingAlgorithm
{
public:
    QString name() const override;
    SchedulingResult schedule(const QVector<Process> &processes, int quantum = 1) const override;
};

class RoundRobinAlgorithm : public SchedulingAlgorithm
{
public:
    QString name() const override;
    SchedulingResult schedule(const QVector<Process> &processes, int quantum = 1) const override;
};

class PriorityAlgorithm : public SchedulingAlgorithm
{
public:
    QString name() const override;
    SchedulingResult schedule(const QVector<Process> &processes, int quantum = 1) const override;
};

#endif // SCHEDULER_H
