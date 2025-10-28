#include "semaphorescenarios.h"

#include <algorithm>
#include <QStringList>

namespace {

QString makeSemaphoreState(const QStringList &pairs)
{
    return pairs.join(QStringLiteral(" | "));
}

} // namespace

ProducerConsumerScenario::ProducerConsumerScenario(int producers, int consumers, int bufferSize, int cycles)
    : m_producers(std::max(1, producers))
    , m_consumers(std::max(1, consumers))
    , m_bufferSize(std::max(1, bufferSize))
    , m_cycles(std::max(1, cycles))
{
}

QString ProducerConsumerScenario::name() const
{
    return QStringLiteral("Productor-Consumidor");
}

QVector<ConcurrencyStep> ProducerConsumerScenario::simulate() const
{
    QVector<ConcurrencyStep> steps;
    steps.reserve(m_cycles * (m_producers + m_consumers));

    int tick = 0;
    int empty = m_bufferSize;
    int full = 0;
    int mutex = 1;

    auto snapshot = [&]() {
        return makeSemaphoreState({QStringLiteral("empty=%1").arg(empty),
                                   QStringLiteral("full=%1").arg(full),
                                   QStringLiteral("mutex=%1").arg(mutex)});
    };

    for (int cycle = 0; cycle < m_cycles; ++cycle) {
        for (int p = 0; p < m_producers; ++p) {
            ConcurrencyStep step;
            step.tick = tick++;
            step.actor = QStringLiteral("Productor %1").arg(p + 1);
            if (empty == 0) {
                step.action = QStringLiteral("wait(empty) -> bloqueado (buffer lleno)");
            } else {
                --empty; // wait(empty)
                --mutex; // wait(mutex)
                step.action = QStringLiteral("wait(empty); wait(mutex); produce; signal(mutex); signal(full)");
                ++mutex;
                ++full;
            }
            step.semaphoreSnapshot = snapshot();
            steps.push_back(step);
        }

        for (int c = 0; c < m_consumers; ++c) {
            ConcurrencyStep step;
            step.tick = tick++;
            step.actor = QStringLiteral("Consumidor %1").arg(c + 1);
            if (full == 0) {
                step.action = QStringLiteral("wait(full) -> bloqueado (sin productos)");
            } else {
                --full; // wait(full)
                --mutex; // wait(mutex)
                step.action = QStringLiteral("wait(full); wait(mutex); consume; signal(mutex); signal(empty)");
                ++mutex;
                ++empty;
            }
            step.semaphoreSnapshot = snapshot();
            steps.push_back(step);
        }
    }

    return steps;
}

ReadersWritersScenario::ReadersWritersScenario(int readers, int writers, int cycles)
    : m_readers(std::max(1, readers))
    , m_writers(std::max(1, writers))
    , m_cycles(std::max(1, cycles))
{
}

QString ReadersWritersScenario::name() const
{
    return QStringLiteral("Lectores-Escritores");
}

QVector<ConcurrencyStep> ReadersWritersScenario::simulate() const
{
    QVector<ConcurrencyStep> steps;
    steps.reserve(m_cycles * (m_readers + m_writers) * 2);

    int tick = 0;
    int readCount = 0;
    bool writerActive = false;

    for (int cycle = 0; cycle < m_cycles; ++cycle) {
        for (int r = 0; r < m_readers; ++r) {
            ConcurrencyStep enter;
            enter.tick = tick++;
            enter.actor = QStringLiteral("Lector %1").arg(r + 1);
            QStringList states;
            if (readCount == 0 && !writerActive) {
                states << QStringLiteral("rw_mutex=LIBRE");
            } else if (writerActive) {
                enter.action = QStringLiteral("wait(rw_mutex) -> espera (escritor activo)");
                states << QStringLiteral("rw_mutex=ESCRITOR");
                enter.semaphoreSnapshot = makeSemaphoreState(states);
                steps.push_back(enter);
                continue;
            }
            ++readCount;
            enter.action = QStringLiteral("wait(mutex); readcount=%1; si primero -> wait(rw_mutex)").arg(readCount);
            states << QStringLiteral("readcount=%1").arg(readCount);
            states << QStringLiteral("rw_mutex=LECTORES");
            enter.semaphoreSnapshot = makeSemaphoreState(states);
            steps.push_back(enter);

            ConcurrencyStep exit;
            exit.tick = tick++;
            exit.actor = enter.actor;
            --readCount;
            exit.action = QStringLiteral("signal(mutex); readcount=%1; si cero -> signal(rw_mutex)").arg(readCount);
            QStringList exitStates;
            exitStates << QStringLiteral("readcount=%1").arg(readCount);
            exitStates << QStringLiteral("rw_mutex=%1").arg(readCount == 0 ? QStringLiteral("LIBRE") : QStringLiteral("LECTORES"));
            exit.semaphoreSnapshot = makeSemaphoreState(exitStates);
            steps.push_back(exit);
        }

        for (int w = 0; w < m_writers; ++w) {
            ConcurrencyStep enter;
            enter.tick = tick++;
            enter.actor = QStringLiteral("Escritor %1").arg(w + 1);
            if (readCount > 0 || writerActive) {
                enter.action = QStringLiteral("wait(rw_mutex) -> espera (lectores/escritor)");
                enter.semaphoreSnapshot = makeSemaphoreState({QStringLiteral("rw_mutex=OCUPADO"),
                                                              QStringLiteral("readcount=%1").arg(readCount)});
                steps.push_back(enter);
                continue;
            }
            writerActive = true;
            enter.action = QStringLiteral("wait(rw_mutex); escribe");
            enter.semaphoreSnapshot = makeSemaphoreState({QStringLiteral("rw_mutex=ESCRITOR"),
                                                          QStringLiteral("readcount=%1").arg(readCount)});
            steps.push_back(enter);

            ConcurrencyStep exit;
            exit.tick = tick++;
            exit.actor = enter.actor;
            exit.action = QStringLiteral("signal(rw_mutex); escritura completada");
            writerActive = false;
            exit.semaphoreSnapshot = makeSemaphoreState({QStringLiteral("rw_mutex=LIBRE"),
                                                         QStringLiteral("readcount=%1").arg(readCount)});
            steps.push_back(exit);
        }
    }

    return steps;
}

SleepingBarberScenario::SleepingBarberScenario(int chairs, int customers)
    : m_chairs(std::max(0, chairs))
    , m_customers(std::max(1, customers))
{
}

QString SleepingBarberScenario::name() const
{
    return QStringLiteral("Barbero Dormilon");
}

QVector<ConcurrencyStep> SleepingBarberScenario::simulate() const
{
    QVector<ConcurrencyStep> steps;
    steps.reserve(m_customers * 3);

    int tick = 0;
    int waiting = 0;
    bool barberBusy = false;

    for (int c = 0; c < m_customers; ++c) {
        const QString customer = QStringLiteral("Cliente %1").arg(c + 1);

        ConcurrencyStep arrival;
        arrival.tick = tick++;
        arrival.actor = customer;
        arrival.semaphoreSnapshot = makeSemaphoreState({QStringLiteral("waiting=%1").arg(waiting),
                                                        QStringLiteral("sillas=%1").arg(m_chairs),
                                                        QStringLiteral("barbero=%1").arg(barberBusy ? QStringLiteral("OCUPADO") : QStringLiteral("DORMIDO"))});

        if (!barberBusy) {
            barberBusy = true;
            arrival.action = QStringLiteral("signal(customer); despierta al barbero; ocupa la silla");
            arrival.semaphoreSnapshot = makeSemaphoreState({QStringLiteral("waiting=%1").arg(waiting),
                                                            QStringLiteral("sillas=%1").arg(m_chairs),
                                                            QStringLiteral("barbero=ACTIVO")});
            steps.push_back(arrival);

            ConcurrencyStep haircut;
            haircut.tick = tick++;
            haircut.actor = QStringLiteral("Barbero");
            haircut.action = QStringLiteral("wait(customer); wait(mutex); atiende a %1; signal(mutex)").arg(customer);
            haircut.semaphoreSnapshot = makeSemaphoreState({QStringLiteral("waiting=%1").arg(waiting),
                                                            QStringLiteral("barbero=TRABAJANDO")});
            steps.push_back(haircut);

            ConcurrencyStep done;
            done.tick = tick++;
            done.actor = QStringLiteral("Barbero");
            barberBusy = false;
            done.action = QStringLiteral("signal(barber); termina; vuelve a dormir");
            done.semaphoreSnapshot = makeSemaphoreState({QStringLiteral("waiting=%1").arg(waiting),
                                                         QStringLiteral("barbero=DORMIDO")});
            steps.push_back(done);
        } else if (waiting < m_chairs) {
            ++waiting;
            arrival.action = QStringLiteral("espera; se sienta (%1/%2)").arg(waiting).arg(m_chairs);
            arrival.semaphoreSnapshot = makeSemaphoreState({QStringLiteral("waiting=%1").arg(waiting),
                                                            QStringLiteral("sillas=%1").arg(m_chairs),
                                                            QStringLiteral("barbero=OCUPADO")});
            steps.push_back(arrival);

            ConcurrencyStep attend;
            attend.tick = tick++;
            attend.actor = QStringLiteral("Barbero");
            --waiting;
            attend.action = QStringLiteral("signal(customer); wait(mutex); atiende a %1").arg(customer);
            attend.semaphoreSnapshot = makeSemaphoreState({QStringLiteral("waiting=%1").arg(waiting),
                                                            QStringLiteral("barbero=TRABAJANDO")});
            steps.push_back(attend);

            ConcurrencyStep finish;
            finish.tick = tick++;
            finish.actor = QStringLiteral("Barbero");
            barberBusy = waiting > 0;
            finish.action = QStringLiteral("signal(barber); libera al siguiente");
            finish.semaphoreSnapshot = makeSemaphoreState({QStringLiteral("waiting=%1").arg(waiting),
                                                            QStringLiteral("barbero=%1").arg(barberBusy ? QStringLiteral("OCUPADO") : QStringLiteral("DORMIDO"))});
            steps.push_back(finish);
        } else {
            arrival.action = QStringLiteral("no hay sillas; se va");
            arrival.semaphoreSnapshot = makeSemaphoreState({QStringLiteral("waiting=%1").arg(waiting),
                                                            QStringLiteral("sillas=%1").arg(m_chairs),
                                                            QStringLiteral("barbero=OCUPADO")});
            steps.push_back(arrival);
        }
    }

    return steps;
}
