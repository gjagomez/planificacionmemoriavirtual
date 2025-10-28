#include "principal.h"
#include "ui_principal.h"

#include <algorithm>

#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include <QHeaderView>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QPixmap>
#include <QRegularExpression>
#include <QtCore/qscopedvaluerollback.h>
#include <QStatusBar>
#include <QStringList>
#include <QTableWidgetItem>
#include <QTextStream>

principal::principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::principal)
{
    ui->setupUi(this);
    statusBar()->hide();

    applyModernStyle();
    setupSchedulingTab();
    setupConcurrencyTab();
    setupMemoryTab();
}

principal::~principal()
{
    delete ui;
}

void principal::setupSchedulingTab()
{
    ui->processTable->setHorizontalHeaderLabels({QStringLiteral("Proceso"), QStringLiteral("Llegada"), QStringLiteral("Duracion"), QStringLiteral("Prioridad")});
    ui->processTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->processTable->verticalHeader()->setVisible(false);

    ui->algorithmCombo->addItem(QStringLiteral("First Come First Served (FCFS)"), QStringLiteral("fcfs"));
    ui->algorithmCombo->addItem(QStringLiteral("Shortest Job First (SJF)"), QStringLiteral("sjf"));
    ui->algorithmCombo->addItem(QStringLiteral("Shortest Remaining Time First (SRTF)"), QStringLiteral("srtf"));
    ui->algorithmCombo->addItem(QStringLiteral("Round Robin"), QStringLiteral("rr"));
    ui->algorithmCombo->addItem(QStringLiteral("Prioridades"), QStringLiteral("priority"));
    ui->algorithmCombo->setCurrentIndex(0);

    connect(ui->addProcessButton, &QPushButton::clicked, this, &principal::addProcessRow);
    connect(ui->removeProcessButton, &QPushButton::clicked, this, &principal::removeSelectedProcess);
    connect(ui->loadSampleButton, &QPushButton::clicked, this, &principal::loadProcessSample);
    connect(ui->clearProcessesButton, &QPushButton::clicked, this, &principal::clearProcesses);
    connect(ui->startScenarioButton, &QPushButton::clicked, this, &principal::runSchedulingSimulation);
    connect(ui->algorithmCombo, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &principal::algorithmChanged);
    connect(ui->loadScenarioButton, &QPushButton::clicked, this, &principal::loadScenarioFromFile);
    connect(ui->saveScenarioButton, &QPushButton::clicked, this, &principal::saveScenarioToFile);
    connect(ui->exportCsvButton, &QPushButton::clicked, this, &principal::exportSchedulingCsv);
    connect(ui->exportImageButton, &QPushButton::clicked, this, &principal::exportSchedulingImage);

    loadProcessSample();
    updateQuantumVisibility();
}

void principal::setupConcurrencyTab()
{
    ui->scenarioCombo->addItem(QStringLiteral("Productor - Consumidor"), static_cast<int>(ConcurrencyScenarioId::ProducerConsumer));
    ui->scenarioCombo->addItem(QStringLiteral("Lectores - Escritores"), static_cast<int>(ConcurrencyScenarioId::ReadersWriters));
    ui->scenarioCombo->addItem(QStringLiteral("Barbero dormilon"), static_cast<int>(ConcurrencyScenarioId::SleepingBarber));
    ui->scenarioCombo->setCurrentIndex(0);

    ui->concurrencyTable->setHorizontalHeaderLabels({QStringLiteral("Paso"), QStringLiteral("Actor"), QStringLiteral("Accion"), QStringLiteral("Semaforos")});
    ui->concurrencyTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->concurrencyTable->verticalHeader()->setVisible(false);

    connect(ui->scenarioCombo, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &principal::concurrencyScenarioChanged);
    connect(ui->runScenarioButton, &QPushButton::clicked, this, &principal::runConcurrencySimulation);

    updateScenarioControls();
}

void principal::setupMemoryTab()
{
    ui->policyCombo->addItem(QStringLiteral("FIFO"), static_cast<int>(ReplacementPolicy::Fifo));
    ui->policyCombo->addItem(QStringLiteral("LRU"), static_cast<int>(ReplacementPolicy::Lru));
    ui->policyCombo->addItem(QStringLiteral("OPT"), static_cast<int>(ReplacementPolicy::Optimal));
    ui->policyCombo->setCurrentIndex(0);

    ui->memoryTable->setHorizontalHeaderLabels({QStringLiteral("Paso"), QStringLiteral("Pagina"), QStringLiteral("Marco"), QStringLiteral("TLB"), QStringLiteral("Fallo"), QStringLiteral("Estado")});
    ui->memoryTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->memoryTable->horizontalHeader()->setStretchLastSection(true);
    ui->memoryTable->verticalHeader()->setVisible(false);

    connect(ui->runMemoryButton, &QPushButton::clicked, this, &principal::runMemorySimulation);
    connect(ui->sampleReferenceButton, &QPushButton::clicked, this, &principal::loadReferenceSample);

    ui->referenceLine->setPlaceholderText(QStringLiteral("7 0 1 2 0 3 0 4 2 3 0 3 2"));
    loadReferenceSample();
}

void principal::applyModernStyle()
{
    const QString style = QStringLiteral(
        "QMainWindow { background-color: #ffffff; color: #2d3748; }"
        "QTabWidget::pane { border: 0px; }"
        "QTabBar::tab { background: #f8fafc; color: #64748b; padding: 10px 24px; border-radius: 12px 12px 0 0; margin: 0 6px; font-weight: 500; }"
        "QTabBar::tab:selected { background: #ffffff; color: #1e293b; font-weight: 400; border-bottom: 3px solid #0d9488; }"
        "QLabel { color: #334155; font-size: 14px; font-weight: 500; }"
        "QPushButton { background-color: #0d9488; color: white; padding: 10px 20px; border-radius: 12px; font-weight: 600; border: none; }"
        "QPushButton:hover { background-color: #0f766e; }"
        "QPushButton:pressed { background-color: #115e59; }"
        "QPushButton:disabled { background-color: #e2e8f0; color: #94a3b8; }"
        "QTableWidget { background-color: #ffffff; alternate-background-color: #fafbfc; gridline-color: #e5e7eb; color: #1e293b; selection-background-color: #d1fae5; selection-color: #0f766e; }"
        "QHeaderView::section { background-color: #f8fafc; color: #475569; padding: 8px; border: none; font-weight: 600; }"
        "QLineEdit, QSpinBox, QComboBox { background-color: #f8fafc; border: 2px solid #e5e7eb; border-radius: 10px; padding: 8px; color: #1e293b; font-weight: 500; }"
        "QLineEdit:focus, QSpinBox:focus, QComboBox:focus { border: 2px solid #0d9488; background-color: #ffffff; }"
        "QCheckBox { color: #334155; font-weight: 500; }"
        "QFrame#waitCard { background-color: #fce7f3; border: none; border-radius: 20px; padding: 18px; }"
        "QFrame#turnaroundCard { background-color: #dbeafe; border: none; border-radius: 20px; padding: 18px; }"
        "QFrame#responseCard { background-color: #fed7aa; border: none; border-radius: 20px; padding: 18px; }"
        "QFrame#cpuCard { background-color: #fef9c3; border: none; border-radius: 20px; padding: 18px; }"
        "QFrame#schedulingFrame { background-color: #f8fafc; border: 2px solid #e5e7eb; border-radius: 20px; padding: 20px; }"
        "ScheduleTimelineWidget { background-color: #ffffff; border: 2px solid #e5e7eb; border-radius: 16px; }"
        "QListWidget { background-color: #f8fafc; border: 2px solid #e5e7eb; border-radius: 12px; color: #334155; }"
        );
    setStyleSheet(style);
}

void principal::addProcessRow()
{
    const int row = ui->processTable->rowCount();
    ui->processTable->insertRow(row);

    auto makeNumericItem = [](int value) {
        auto *item = new QTableWidgetItem(QString::number(value));
        item->setData(Qt::EditRole, value);
        item->setTextAlignment(Qt::AlignCenter);
        return item;
    };

    auto *idItem = new QTableWidgetItem(QStringLiteral("P%1").arg(row + 1));
    idItem->setTextAlignment(Qt::AlignCenter);

    ui->processTable->setItem(row, 0, idItem);
    ui->processTable->setItem(row, 1, makeNumericItem(row));
    ui->processTable->setItem(row, 2, makeNumericItem(5));
    ui->processTable->setItem(row, 3, makeNumericItem(1));

    if (ui->automaticCheck->isChecked() && !m_blockAutoRun) {
        runSchedulingSimulation();
    }
}

void principal::removeSelectedProcess()
{
    const int row = ui->processTable->currentRow();
    if (row >= 0) {
        ui->processTable->removeRow(row);
        if (ui->automaticCheck->isChecked() && !m_blockAutoRun) {
            runSchedulingSimulation();
        }
    }
}

void principal::loadProcessSample()
{
    QScopedValueRollback<bool> guard(m_blockAutoRun, true);
    ui->processTable->setRowCount(0);
    const QVector<Process> sample = {
        {QStringLiteral("P1"), 0, 6, 1},
        {QStringLiteral("P2"), 2, 3, 2},
        {QStringLiteral("P3"), 4, 5, 3},
        {QStringLiteral("P4"), 6, 2, 2}
    };

    for (const Process &proc : sample) {
        addProcessRow();
        const int row = ui->processTable->rowCount() - 1;
        ui->processTable->item(row, 0)->setText(proc.pid);
        ui->processTable->item(row, 1)->setData(Qt::EditRole, proc.arrivalTime);
        ui->processTable->item(row, 1)->setText(QString::number(proc.arrivalTime));
        ui->processTable->item(row, 2)->setData(Qt::EditRole, proc.burstTime);
        ui->processTable->item(row, 2)->setText(QString::number(proc.burstTime));
        ui->processTable->item(row, 3)->setData(Qt::EditRole, proc.priority);
        ui->processTable->item(row, 3)->setText(QString::number(proc.priority));
    }


    if (ui->automaticCheck->isChecked() && !m_blockAutoRun) {
        runSchedulingSimulation();
    }
}

void principal::clearProcesses()
{
    ui->processTable->setRowCount(0);
    ui->timelineWidget->setTimeline({});
    ui->logListWidget->clear();
    ui->waitingValueLabel->setText(QStringLiteral("--"));
    ui->turnaroundValueLabel->setText(QStringLiteral("--"));
    ui->responseValueLabel->setText(QStringLiteral("--"));
    ui->cpuValueLabel->setText(QStringLiteral("--"));
    m_hasSchedulingResult = false;
    m_lastSchedulingResult = SchedulingResult{};
}

void principal::runSchedulingSimulation()
{
    const QVector<Process> processes = collectProcesses();
    if (processes.isEmpty()) {
        QMessageBox::information(this, tr("Planificacion"), tr("Agrega al menos un proceso valido."));
        return;
    }

    const QString algorithmId = currentAlgorithmId();
    auto algorithm = createAlgorithm(algorithmId);
    if (!algorithm) {
        QMessageBox::warning(this, tr("Algoritmo"), tr("No se pudo crear el algoritmo seleccionado."));
        return;
    }

    const int quantum = ui->quantumSpin->value();
    const SchedulingResult result = algorithm->schedule(processes, quantum);
    populateSchedulingResult(result, processes);
}

QVector<Process> principal::collectProcesses() const
{
    QVector<Process> processes;
    for (int row = 0; row < ui->processTable->rowCount(); ++row) {
        const auto *idItem = ui->processTable->item(row, 0);
        const auto *arrivalItem = ui->processTable->item(row, 1);
        const auto *burstItem = ui->processTable->item(row, 2);
        const auto *priorityItem = ui->processTable->item(row, 3);

        const QString pid = idItem ? idItem->text().trimmed() : QString();
        if (pid.isEmpty()) {
            continue;
        }

        bool okArrival = false;
        bool okBurst = false;
        bool okPriority = false;
        const int arrival = arrivalItem ? arrivalItem->text().toInt(&okArrival) : 0;
        int burst = burstItem ? burstItem->text().toInt(&okBurst) : 0;
        const int priority = priorityItem ? priorityItem->text().toInt(&okPriority) : 0;

        if (!okBurst || burst <= 0) {
            burst = 1;
        }

        Process process{pid, okArrival ? arrival : 0, burst, okPriority ? priority : 0};
        processes.push_back(process);
    }

    std::sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        if (a.arrivalTime == b.arrivalTime) {
            return a.pid < b.pid;
        }
        return a.arrivalTime < b.arrivalTime;
    });

    return processes;
}

std::unique_ptr<SchedulingAlgorithm> principal::createAlgorithm(const QString &id) const
{
    if (id == QLatin1String("fcfs")) {
        return std::make_unique<FcfsAlgorithm>();
    }
    if (id == QLatin1String("sjf")) {
        return std::make_unique<SjfAlgorithm>();
    }
    if (id == QLatin1String("srtf")) {
        return std::make_unique<SrtfAlgorithm>();
    }
    if (id == QLatin1String("rr")) {
        return std::make_unique<RoundRobinAlgorithm>();
    }
    if (id == QLatin1String("priority")) {
        return std::make_unique<PriorityAlgorithm>();
    }
    return nullptr;
}

QString principal::currentAlgorithmId() const
{
    return ui->algorithmCombo->currentData().toString();
}

void principal::updateQuantumVisibility()
{
    const QString id = currentAlgorithmId();
    const bool showQuantum = id == QLatin1String("rr");
    ui->quantumLabel->setVisible(showQuantum);
    ui->quantumSpin->setVisible(showQuantum);
    ui->priorityNoteLabel->setVisible(id == QLatin1String("priority"));
}

void principal::algorithmChanged(int)
{
    updateQuantumVisibility();
    if (ui->automaticCheck->isChecked() && !m_blockAutoRun) {
        runSchedulingSimulation();
    }
}

void principal::populateSchedulingResult(const SchedulingResult &result, const QVector<Process> &processes)
{
    m_lastSchedulingResult = result;
    m_hasSchedulingResult = true;

    ui->timelineWidget->setTimeline(result.timeline);
    updateMetricCards(result, processes);

    ui->logListWidget->clear();
    appendLogMessage(QStringLiteral("Escenario iniciado"));
    for (const ScheduleEvent &eventItem : result.timeline) {
        if (eventItem.pid.compare(QStringLiteral("IDLE"), Qt::CaseInsensitive) == 0) {
            appendLogMessage(QStringLiteral("CPU inactiva (%1 - %2)").arg(eventItem.startTime).arg(eventItem.endTime));
        } else {
            appendLogMessage(QStringLiteral("%1 ejecutando (%2 - %3)")
                                 .arg(eventItem.pid)
                                 .arg(eventItem.startTime)
                                 .arg(eventItem.endTime));
        }
    }
    for (const ProcessReport &report : result.reports) {
        appendLogMessage(QStringLiteral("%1 -> espera %2, retorno %3, respuesta %4")
                             .arg(report.pid)
                             .arg(report.waitingTime)
                             .arg(report.turnaroundTime)
                             .arg(report.responseTime));
    }
    appendLogMessage(QStringLiteral("Escenario finalizado"));

    if (ui->automaticCheck->isChecked()) {
        appendLogMessage(QStringLiteral("Modo automatico activo"));
    }
}

void principal::updateMetricCards(const SchedulingResult &result, const QVector<Process> &processes)
{
    ui->waitingValueLabel->setText(QString::number(result.averageWaiting, 'f', 2));
    ui->turnaroundValueLabel->setText(QString::number(result.averageTurnaround, 'f', 2));
    ui->responseValueLabel->setText(QString::number(result.averageResponse, 'f', 2));

    int lastFinish = 0;
    int busy = 0;
    for (const ScheduleEvent &eventItem : result.timeline) {
        const int duration = eventItem.endTime - eventItem.startTime;
        lastFinish = std::max(lastFinish, eventItem.endTime);
        if (eventItem.pid.compare(QStringLiteral("IDLE"), Qt::CaseInsensitive) != 0) {
            busy += duration;
        }
    }
    const double cpuUsage = (lastFinish > 0) ? (static_cast<double>(busy) / lastFinish) * 100.0 : 0.0;
    ui->cpuValueLabel->setText(QStringLiteral("%1%%").arg(cpuUsage, 0, 'f', 2));

    Q_UNUSED(processes);
}

void principal::appendLogMessage(const QString &message) const
{
    auto *item = new QListWidgetItem(QDateTime::currentDateTime().toString(QStringLiteral("hh:mm:ss")) + QStringLiteral(" | ") + message);
    ui->logListWidget->addItem(item);
    ui->logListWidget->scrollToBottom();
}

void principal::loadScenarioFromFile()
{
    QScopedValueRollback<bool> guard(m_blockAutoRun, true);
    const QString fileName = QFileDialog::getOpenFileName(this, tr("Cargar escenario"), QString(), tr("Archivos CSV (*.csv);;Todos los archivos (*.*)"));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Cargar escenario"), tr("No se pudo abrir el archivo."));
        return;
    }

    QVector<Process> loaded;
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        const QString line = stream.readLine().trimmed();
        if (line.isEmpty()) {
            continue;
        }
        const QStringList parts = line.split(QRegularExpression(",|;|\t"), Qt::KeepEmptyParts);
        if (parts.size() < 3) {
            continue;
        }
        Process proc;
        proc.pid = parts[0].trimmed();
        if (proc.pid.compare(QStringLiteral("Proceso"), Qt::CaseInsensitive) == 0) {
            continue;
        }
        proc.arrivalTime = parts.value(1).trimmed().toInt();
        proc.burstTime = parts.value(2).trimmed().toInt();
        proc.priority = parts.value(3).trimmed().toInt();
        if (!proc.pid.isEmpty()) {
            if (proc.burstTime <= 0) {
                proc.burstTime = 1;
            }
            loaded.push_back(proc);
        }
    }

    if (loaded.isEmpty()) {
        QMessageBox::information(this, tr("Cargar escenario"), tr("El archivo no contiene procesos validos."));
        return;
    }

    ui->processTable->setRowCount(0);
    for (const Process &proc : loaded) {
        addProcessRow();
        const int row = ui->processTable->rowCount() - 1;
        ui->processTable->item(row, 0)->setText(proc.pid);
        ui->processTable->item(row, 1)->setData(Qt::EditRole, proc.arrivalTime);
        ui->processTable->item(row, 1)->setText(QString::number(proc.arrivalTime));
        ui->processTable->item(row, 2)->setData(Qt::EditRole, proc.burstTime);
        ui->processTable->item(row, 2)->setText(QString::number(proc.burstTime));
        ui->processTable->item(row, 3)->setData(Qt::EditRole, proc.priority);
        ui->processTable->item(row, 3)->setText(QString::number(proc.priority));
    }


    if (ui->automaticCheck->isChecked() && !m_blockAutoRun) {
        runSchedulingSimulation();
    }
}

void principal::saveScenarioToFile()
{
    const QVector<Process> processes = collectProcesses();
    if (processes.isEmpty()) {
        QMessageBox::information(this, tr("Guardar escenario"), tr("No hay procesos para guardar."));
        return;
    }

    const QString fileName = QFileDialog::getSaveFileName(this, tr("Guardar escenario"), QString(), tr("Archivos CSV (*.csv);;Todos los archivos (*.*)"));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Guardar escenario"), tr("No se pudo escribir el archivo."));
        return;
    }

    QTextStream stream(&file);
    stream << "Proceso,Llegada,Duracion,Prioridad\n";
    for (const Process &proc : processes) {
        stream << proc.pid << ',' << proc.arrivalTime << ',' << proc.burstTime << ',' << proc.priority << "\n";
    }
}

void principal::exportSchedulingCsv()
{
    if (!m_hasSchedulingResult) {
        QMessageBox::information(this, tr("Exportar"), tr("Ejecuta primero una simulacion."));
        return;
    }

    const QString fileName = QFileDialog::getSaveFileName(this, tr("Exportar resultados"), QString(), tr("Archivos CSV (*.csv);;Todos los archivos (*.*)"));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Exportar"), tr("No se pudo escribir el archivo."));
        return;
    }

    QTextStream stream(&file);
    stream << "Proceso,Inicio,Fin,Espera,Retorno,Respuesta\n";
    for (const ProcessReport &report : m_lastSchedulingResult.reports) {
        stream << report.pid << ','
               << report.firstStart << ','
               << report.finishTime << ','
               << report.waitingTime << ','
               << report.turnaroundTime << ','
               << report.responseTime << "\n";
    }
    stream << "Promedio Espera," << QString::number(m_lastSchedulingResult.averageWaiting, 'f', 2) << "\n";
    stream << "Promedio Retorno," << QString::number(m_lastSchedulingResult.averageTurnaround, 'f', 2) << "\n";
    stream << "Promedio Respuesta," << QString::number(m_lastSchedulingResult.averageResponse, 'f', 2) << "\n";
    stream << "\nLinea de tiempo (PID,Inicio,Fin)\n";
    for (const ScheduleEvent &eventItem : m_lastSchedulingResult.timeline) {
        stream << eventItem.pid << ',' << eventItem.startTime << ',' << eventItem.endTime << "\n";
    }
}

void principal::exportSchedulingImage()
{
    if (!m_hasSchedulingResult) {
        QMessageBox::information(this, tr("Exportar"), tr("Ejecuta primero una simulacion."));
        return;
    }

    const QString fileName = QFileDialog::getSaveFileName(this, tr("Exportar imagen"), QString(), tr("Imagen PNG (*.png);;Todos los archivos (*.*)"));
    if (fileName.isEmpty()) {
        return;
    }

    QPixmap pixmap(ui->timelineWidget->size());
    ui->timelineWidget->render(&pixmap);
    if (!pixmap.save(fileName)) {
        QMessageBox::warning(this, tr("Exportar imagen"), tr("No se pudo guardar la imagen."));
    }
}

void principal::runConcurrencySimulation()
{
    std::unique_ptr<SemaphoreScenario> scenario;
    switch (currentScenarioId()) {
    case ConcurrencyScenarioId::ProducerConsumer:
        scenario = std::make_unique<ProducerConsumerScenario>(ui->producerSpin->value(), ui->consumerSpin->value(), ui->bufferSpin->value(), ui->cycleSpin->value());
        break;
    case ConcurrencyScenarioId::ReadersWriters:
        scenario = std::make_unique<ReadersWritersScenario>(ui->readerSpin->value(), ui->writerSpin->value(), ui->cycleSpin->value());
        break;
    case ConcurrencyScenarioId::SleepingBarber:
        scenario = std::make_unique<SleepingBarberScenario>(ui->chairsSpin->value(), ui->customersSpin->value());
        break;
    }

    const QVector<ConcurrencyStep> steps = scenario->simulate();
    populateConcurrencyResult(steps);
}

ConcurrencyScenarioId principal::currentScenarioId() const
{
    return static_cast<ConcurrencyScenarioId>(ui->scenarioCombo->currentData().toInt());
}

void principal::updateScenarioControls()
{
    const ConcurrencyScenarioId scenario = currentScenarioId();
    const bool showProducerConsumer = scenario == ConcurrencyScenarioId::ProducerConsumer;
    const bool showReadersWriters = scenario == ConcurrencyScenarioId::ReadersWriters;
    const bool showBarber = scenario == ConcurrencyScenarioId::SleepingBarber;

    ui->producerLabel->setVisible(showProducerConsumer);
    ui->producerSpin->setVisible(showProducerConsumer);
    ui->consumerLabel->setVisible(showProducerConsumer);
    ui->consumerSpin->setVisible(showProducerConsumer);
    ui->bufferLabel->setVisible(showProducerConsumer);
    ui->bufferSpin->setVisible(showProducerConsumer);
    ui->cycleLabel->setVisible(showProducerConsumer || showReadersWriters);
    ui->cycleSpin->setVisible(showProducerConsumer || showReadersWriters);

    ui->readerLabel->setVisible(showReadersWriters);
    ui->readerSpin->setVisible(showReadersWriters);
    ui->writerLabel->setVisible(showReadersWriters);
    ui->writerSpin->setVisible(showReadersWriters);

    ui->chairsLabel->setVisible(showBarber);
    ui->chairsSpin->setVisible(showBarber);
    ui->customersLabel->setVisible(showBarber);
    ui->customersSpin->setVisible(showBarber);
}

void principal::populateConcurrencyResult(const QVector<ConcurrencyStep> &steps)
{
    ui->concurrencyTable->setRowCount(steps.size());
    for (int row = 0; row < steps.size(); ++row) {
        const ConcurrencyStep &step = steps[row];
        const QVector<QString> values = {
            QString::number(step.tick),
            step.actor,
            step.action,
            step.semaphoreSnapshot
        };
        for (int col = 0; col < values.size(); ++col) {
            auto *item = new QTableWidgetItem(values[col]);
            if (col == 0) {
                item->setTextAlignment(Qt::AlignCenter);
            }
            ui->concurrencyTable->setItem(row, col, item);
        }
    }
    ui->concurrencySummaryLabel->setText(QStringLiteral("Pasos generados: %1").arg(steps.size()));
}

void principal::concurrencyScenarioChanged(int)
{
    updateScenarioControls();
}

void principal::runMemorySimulation()
{
    const QVector<int> references = parseReferenceString(ui->referenceLine->text());
    if (references.isEmpty()) {
        QMessageBox::information(this, tr("Memoria virtual"), tr("Introduce una secuencia de paginas valida."));
        return;
    }

    VirtualMemorySimulator simulator(ui->framesSpin->value(), ui->tlbSpin->value(), selectedPolicy());
    simulator.setReferenceString(references);
    const VirtualMemoryReport report = simulator.runSimulation();
    populateMemoryResult(report);
}

void principal::loadReferenceSample()
{
    ui->referenceLine->setText(QStringLiteral("7 0 1 2 0 3 0 4 2 3 0 3 2"));
}

QVector<int> principal::parseReferenceString(const QString &text) const
{
    QVector<int> values;
    const QRegularExpression splitter(QStringLiteral("[^0-9]+"));
    const QStringList tokens = text.split(splitter, Qt::SkipEmptyParts);
    for (const QString &token : tokens) {
        bool ok = false;
        const int value = token.toInt(&ok);
        if (ok) {
            values.push_back(value);
        }
    }
    return values;
}

ReplacementPolicy principal::selectedPolicy() const
{
    return static_cast<ReplacementPolicy>(ui->policyCombo->currentData().toInt());
}

void principal::populateMemoryResult(const VirtualMemoryReport &report)
{
    ui->memoryTable->setRowCount(report.accesses.size());
    for (int row = 0; row < report.accesses.size(); ++row) {
        const MemoryAccess &access = report.accesses[row];

        QStringList frameTextParts;
        for (int frameValue : access.frameSnapshot) {
            frameTextParts << (frameValue >= 0 ? QString::number(frameValue) : QStringLiteral("-"));
        }
        const QString frameText = QStringLiteral("Frames [%1]").arg(frameTextParts.join(QStringLiteral(", ")));

        QStringList tlbParts;
        for (int i = 0; i < access.tlbSnapshot.size(); ++i) {
            const int page = access.tlbSnapshot[i];
            if (page >= 0) {
                const int frame = (i < access.tlbFrameSnapshot.size()) ? access.tlbFrameSnapshot[i] : -1;
                tlbParts << QStringLiteral("%1->%2").arg(page).arg(frame >= 0 ? QString::number(frame) : QStringLiteral("-"));
            }
        }
        const QString tlbText = tlbParts.isEmpty() ? QStringLiteral("TLB []") : QStringLiteral("TLB [%1]").arg(tlbParts.join(QStringLiteral(", ")));

        const QVector<QString> values = {
            QString::number(access.step),
            QString::number(access.pageNumber),
            access.frameIndex >= 0 ? QString::number(access.frameIndex) : QStringLiteral("-"),
            access.tlbHit ? QStringLiteral("Hit") : QStringLiteral("Miss"),
            access.pageFault ? QStringLiteral("Si") : QStringLiteral("No"),
            QStringLiteral("%1 | %2 | %3").arg(access.explanation, frameText, tlbText)
        };

        for (int col = 0; col < values.size(); ++col) {
            auto *item = new QTableWidgetItem(values[col]);
            if (col <= 2) {
                item->setTextAlignment(Qt::AlignCenter);
            }
            ui->memoryTable->setItem(row, col, item);
        }
    }

    const double hitRatePercent = report.hitRate * 100.0;
    ui->memorySummaryLabel->setText(QStringLiteral("Fallos de pagina: %1 | TLB hits: %2 (%3%)")
                                        .arg(report.pageFaults)
                                        .arg(report.tlbHits)
                                        .arg(hitRatePercent, 0, 'f', 2));
}


































