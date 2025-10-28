#include "scheduler.h"

#include <algorithm>
#include <limits>
#include <queue>

namespace {

static const QString kIdlePid = QStringLiteral("IDLE");

void appendEvent(QVector<ScheduleEvent> &timeline, const QString &pid, int start, int end)
{
    if (start == end) {
        return;
    }
    if (!timeline.isEmpty()) {
        ScheduleEvent &last = timeline.last();
        if (last.pid == pid && last.endTime == start) {
            last.endTime = end;
            return;
        }
    }
    timeline.push_back({pid, start, end});
}

QVector<ProcessReport> buildReports(const QVector<Process> &processes,
                                    const QVector<ScheduleEvent> &timeline)
{
    QVector<ProcessReport> reports;
    reports.reserve(processes.size());
    for (const Process &proc : processes) {
        ProcessReport report;
        report.pid = proc.pid;
        int totalActive = 0;
        for (const ScheduleEvent &event : timeline) {
            if (event.pid != proc.pid) {
                continue;
            }
            totalActive += event.endTime - event.startTime;
            if (report.firstStart == -1 || event.startTime < report.firstStart) {
                report.firstStart = event.startTime;
            }
            report.finishTime = std::max(report.finishTime, event.endTime);
        }
        if (report.firstStart == -1) {
            report.firstStart = proc.arrivalTime;
            report.finishTime = proc.arrivalTime;
        }
        report.turnaroundTime = report.finishTime - proc.arrivalTime;
        report.waitingTime = report.turnaroundTime - proc.burstTime;
        if (report.waitingTime < 0) {
            report.waitingTime = 0;
        }
        report.responseTime = report.firstStart - proc.arrivalTime;
        if (report.responseTime < 0) {
            report.responseTime = 0;
        }
        reports.push_back(report);
    }
    return reports;
}

SchedulingResult finalizeResult(const QVector<Process> &processes,
                                QVector<ScheduleEvent> timeline)
{
    std::sort(timeline.begin(), timeline.end(), [](const ScheduleEvent &a, const ScheduleEvent &b) {
        return a.startTime < b.startTime;
    });
    QVector<ProcessReport> reports = buildReports(processes, timeline);
    SchedulingResult result;
    result.timeline = std::move(timeline);
    result.reports = reports;
    double totalWaiting = 0.0;
    double totalTurnaround = 0.0;
    double totalResponse = 0.0;
    for (const ProcessReport &report : result.reports) {
        totalWaiting += report.waitingTime;
        totalTurnaround += report.turnaroundTime;
        totalResponse += report.responseTime;
    }
    const int count = result.reports.isEmpty() ? 1 : result.reports.size();
    result.averageWaiting = totalWaiting / count;
    result.averageTurnaround = totalTurnaround / count;
    result.averageResponse = totalResponse / count;
    return result;
}

} // namespace

QString FcfsAlgorithm::name() const
{
    return QStringLiteral("FCFS");
}

SchedulingResult FcfsAlgorithm::schedule(const QVector<Process> &processes, int) const
{
    QVector<Process> sorted = processes;
    std::sort(sorted.begin(), sorted.end(), [](const Process &lhs, const Process &rhs) {
        if (lhs.arrivalTime == rhs.arrivalTime) {
            return lhs.pid < rhs.pid;
        }
        return lhs.arrivalTime < rhs.arrivalTime;
    });

    QVector<ScheduleEvent> timeline;
    timeline.reserve(sorted.size());
    int currentTime = 0;
    for (const Process &proc : sorted) {
        if (currentTime < proc.arrivalTime) {
            appendEvent(timeline, kIdlePid, currentTime, proc.arrivalTime);
            currentTime = proc.arrivalTime;
        }
        const int start = currentTime;
        const int end = start + proc.burstTime;
        appendEvent(timeline, proc.pid, start, end);
        currentTime = end;
    }
    return finalizeResult(processes, timeline);
}

QString SjfAlgorithm::name() const
{
    return QStringLiteral("SJF");
}

SchedulingResult SjfAlgorithm::schedule(const QVector<Process> &processes, int) const
{
    QVector<Process> remaining = processes;
    std::sort(remaining.begin(), remaining.end(), [](const Process &lhs, const Process &rhs) {
        return lhs.arrivalTime < rhs.arrivalTime;
    });

    QVector<ScheduleEvent> timeline;
    int currentTime = 0;

    while (!remaining.isEmpty()) {
        QVector<int> readyIndexes;
        for (int i = 0; i < remaining.size(); ++i) {
            if (remaining[i].arrivalTime <= currentTime) {
                readyIndexes.push_back(i);
            } else {
                break;
            }
        }

        if (readyIndexes.isEmpty()) {
            const int nextArrival = remaining.first().arrivalTime;
            appendEvent(timeline, kIdlePid, currentTime, nextArrival);
            currentTime = nextArrival;
            continue;
        }

        int bestIdx = readyIndexes.first();
        for (int idx : readyIndexes) {
            if (remaining[idx].burstTime < remaining[bestIdx].burstTime ||
                (remaining[idx].burstTime == remaining[bestIdx].burstTime && remaining[idx].pid < remaining[bestIdx].pid)) {
                bestIdx = idx;
            }
        }

        Process proc = remaining.takeAt(bestIdx);
        const int start = currentTime;
        const int end = start + proc.burstTime;
        appendEvent(timeline, proc.pid, start, end);
        currentTime = end;
    }

    return finalizeResult(processes, timeline);
}

QString SrtfAlgorithm::name() const
{
    return QStringLiteral("SRTF");
}

SchedulingResult SrtfAlgorithm::schedule(const QVector<Process> &processes, int) const
{
    struct RuntimeProc {
        Process proc;
        int remaining;
        bool completed = false;
    };

    QVector<RuntimeProc> runtime;
    runtime.reserve(processes.size());
    for (const Process &proc : processes) {
        runtime.push_back({proc, proc.burstTime, false});
    }

    int currentTime = 0;
    int finished = 0;
    QVector<ScheduleEvent> timeline;

    auto hasArrived = [&](const RuntimeProc &rp) { return rp.proc.arrivalTime <= currentTime && !rp.completed; };
    auto nextArrival = [&]() {
        int next = std::numeric_limits<int>::max();
        for (const RuntimeProc &rp : runtime) {
            if (!rp.completed && rp.proc.arrivalTime > currentTime) {
                next = std::min(next, rp.proc.arrivalTime);
            }
        }
        return next;
    };

    while (finished < runtime.size()) {
        int bestIdx = -1;
        for (int i = 0; i < runtime.size(); ++i) {
            if (!hasArrived(runtime[i])) {
                continue;
            }
            if (bestIdx == -1 || runtime[i].remaining < runtime[bestIdx].remaining ||
                (runtime[i].remaining == runtime[bestIdx].remaining && runtime[i].proc.pid < runtime[bestIdx].proc.pid)) {
                bestIdx = i;
            }
        }

        if (bestIdx == -1) {
            const int arrival = nextArrival();
            if (arrival == std::numeric_limits<int>::max()) {
                break;
            }
            appendEvent(timeline, kIdlePid, currentTime, arrival);
            currentTime = arrival;
            continue;
        }

        RuntimeProc &selected = runtime[bestIdx];
        const int arrivalNext = nextArrival();
        const int runUntil = arrivalNext == std::numeric_limits<int>::max()
                                 ? currentTime + selected.remaining
                                 : std::min(currentTime + selected.remaining, arrivalNext);
        const int actualEnd = std::max(currentTime + 1, runUntil);
        appendEvent(timeline, selected.proc.pid, currentTime, actualEnd);
        selected.remaining -= actualEnd - currentTime;
        currentTime = actualEnd;
        if (selected.remaining == 0) {
            selected.completed = true;
            ++finished;
        }
    }

    return finalizeResult(processes, timeline);
}

QString RoundRobinAlgorithm::name() const
{
    return QStringLiteral("Round Robin");
}

SchedulingResult RoundRobinAlgorithm::schedule(const QVector<Process> &processes, int quantum) const
{
    if (quantum <= 0) {
        quantum = 1;
    }

    struct RuntimeProc {
        Process proc;
        int remaining;
    };

    QVector<RuntimeProc> runtime;
    runtime.reserve(processes.size());
    for (const Process &proc : processes) {
        runtime.push_back({proc, proc.burstTime});
    }

    QVector<ScheduleEvent> timeline;
    std::queue<int> readyQueue;
    int currentTime = 0;
    int completed = 0;

    auto enqueueArrivals = [&](int time) {
        for (int i = 0; i < runtime.size(); ++i) {
            if (runtime[i].proc.arrivalTime == time && runtime[i].remaining > 0) {
                readyQueue.push(i);
            }
        }
    };

    int nextArrival = std::numeric_limits<int>::max();
    for (const RuntimeProc &rt : runtime) {
        nextArrival = std::min(nextArrival, rt.proc.arrivalTime);
    }

    if (nextArrival > 0 && nextArrival != std::numeric_limits<int>::max()) {
        appendEvent(timeline, kIdlePid, 0, nextArrival);
        currentTime = nextArrival;
    }

    enqueueArrivals(currentTime);

    while (completed < runtime.size()) {
        if (readyQueue.empty()) {
            int soonest = std::numeric_limits<int>::max();
            for (const RuntimeProc &rt : runtime) {
                if (rt.remaining > 0 && rt.proc.arrivalTime > currentTime) {
                    soonest = std::min(soonest, rt.proc.arrivalTime);
                }
            }
            if (soonest == std::numeric_limits<int>::max()) {
                break;
            }
            appendEvent(timeline, kIdlePid, currentTime, soonest);
            currentTime = soonest;
            enqueueArrivals(currentTime);
            continue;
        }

        const int idx = readyQueue.front();
        readyQueue.pop();
        RuntimeProc &rt = runtime[idx];

        const int slice = std::min(quantum, rt.remaining);
        const int start = currentTime;
        const int end = start + slice;
        appendEvent(timeline, rt.proc.pid, start, end);
        rt.remaining -= slice;
        currentTime = end;

        for (int time = start + 1; time <= currentTime; ++time) {
            enqueueArrivals(time);
        }

        if (rt.remaining > 0) {
            readyQueue.push(idx);
        } else {
            ++completed;
        }
    }

    return finalizeResult(processes, timeline);
}

QString PriorityAlgorithm::name() const
{
    return QStringLiteral("Prioridades");
}

SchedulingResult PriorityAlgorithm::schedule(const QVector<Process> &processes, int) const
{
    QVector<Process> remaining = processes;
    std::sort(remaining.begin(), remaining.end(), [](const Process &lhs, const Process &rhs) {
        return lhs.arrivalTime < rhs.arrivalTime;
    });

    QVector<ScheduleEvent> timeline;
    int currentTime = 0;

    while (!remaining.isEmpty()) {
        QVector<int> readyIndexes;
        for (int i = 0; i < remaining.size(); ++i) {
            if (remaining[i].arrivalTime <= currentTime) {
                readyIndexes.push_back(i);
            } else {
                break;
            }
        }

        if (readyIndexes.isEmpty()) {
            const int nextArrival = remaining.first().arrivalTime;
            appendEvent(timeline, kIdlePid, currentTime, nextArrival);
            currentTime = nextArrival;
            continue;
        }

        int bestIdx = readyIndexes.first();
        for (int idx : readyIndexes) {
            if (remaining[idx].priority < remaining[bestIdx].priority ||
                (remaining[idx].priority == remaining[bestIdx].priority && remaining[idx].pid < remaining[bestIdx].pid)) {
                bestIdx = idx;
            }
        }

        Process proc = remaining.takeAt(bestIdx);
        const int start = currentTime;
        const int end = start + proc.burstTime;
        appendEvent(timeline, proc.pid, start, end);
        currentTime = end;
    }

    return finalizeResult(processes, timeline);
}
