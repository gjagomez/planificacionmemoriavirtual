#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QVector>
#include <memory>

#include "simulations/concurrency/semaphorescenarios.h"
#include "simulations/memory/virtualmemory.h"
#include "simulations/scheduling/scheduler.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class principal;
}
QT_END_NAMESPACE

enum class ConcurrencyScenarioId {
    ProducerConsumer,
    ReadersWriters,
    SleepingBarber
};

class principal : public QMainWindow
{
    Q_OBJECT

public:
    explicit principal(QWidget *parent = nullptr);
    ~principal() override;

private slots:
    void addProcessRow();
    void removeSelectedProcess();
    void loadProcessSample();
    void clearProcesses();
    void runSchedulingSimulation();
    void algorithmChanged(int index);
    void loadScenarioFromFile();
    void saveScenarioToFile();
    void exportSchedulingCsv();
    void exportSchedulingImage();

    void runConcurrencySimulation();
    void concurrencyScenarioChanged(int index);

    void runMemorySimulation();
    void loadReferenceSample();

private:
    void setupSchedulingTab();
    void setupConcurrencyTab();
    void setupMemoryTab();
    void applyModernStyle();

    QVector<Process> collectProcesses() const;
    std::unique_ptr<SchedulingAlgorithm> createAlgorithm(const QString &id) const;
    QString currentAlgorithmId() const;
    void updateQuantumVisibility();
    void populateSchedulingResult(const SchedulingResult &result, const QVector<Process> &processes);
    void updateMetricCards(const SchedulingResult &result, const QVector<Process> &processes);
    void appendLogMessage(const QString &message) const;

    ConcurrencyScenarioId currentScenarioId() const;
    void updateScenarioControls();
    void populateConcurrencyResult(const QVector<ConcurrencyStep> &steps);

    QVector<int> parseReferenceString(const QString &text) const;
    ReplacementPolicy selectedPolicy() const;
    void populateMemoryResult(const VirtualMemoryReport &report);

    Ui::principal *ui;
    SchedulingResult m_lastSchedulingResult;
    bool m_hasSchedulingResult = false;
    bool m_blockAutoRun = false;
};

#endif // PRINCIPAL_H
