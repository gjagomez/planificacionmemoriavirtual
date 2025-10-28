/********************************************************************************
** Form generated from reading UI file 'principal.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRINCIPAL_H
#define UI_PRINCIPAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "widgets/scheduletimelinewidget.h"

QT_BEGIN_NAMESPACE

class Ui_principal
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QTabWidget *tabWidget;
    QWidget *schedulingTab;
    QVBoxLayout *schedulingLayout;
    QHBoxLayout *controlBarLayout;
    QLabel *algorithmLabel;
    QComboBox *algorithmCombo;
    QLabel *quantumLabel;
    QSpinBox *quantumSpin;
    QPushButton *addProcessButton;
    QPushButton *removeProcessButton;
    QPushButton *loadSampleButton;
    QPushButton *clearProcessesButton;
    QSpacerItem *controlSpacer;
    QLabel *priorityNoteLabel;
    QFrame *schedulingFrame;
    QHBoxLayout *schedulingMainLayout;
    QFrame *scenarioPanel;
    QVBoxLayout *scenarioLayout;
    QLabel *scenarioTitleLabel;
    QTableWidget *processTable;
    QHBoxLayout *scenarioButtonsLayout;
    QPushButton *loadScenarioButton;
    QPushButton *saveScenarioButton;
    QCheckBox *automaticCheck;
    QPushButton *startScenarioButton;
    QLabel *logTitleLabel;
    QListWidget *logListWidget;
    QFrame *timelinePanel;
    QVBoxLayout *timelineLayout;
    QLabel *timelineHeadingLabel;
    ScheduleTimelineWidget *timelineWidget;
    QFrame *metricsPanel;
    QVBoxLayout *metricsLayout;
    QFrame *waitCard;
    QVBoxLayout *waitCardLayout;
    QLabel *waitingLabel;
    QLabel *waitingValueLabel;
    QFrame *turnaroundCard;
    QVBoxLayout *turnaroundCardLayout;
    QLabel *turnaroundLabel;
    QLabel *turnaroundValueLabel;
    QFrame *responseCard;
    QVBoxLayout *responseCardLayout;
    QLabel *responseLabel;
    QLabel *responseValueLabel;
    QFrame *cpuCard;
    QVBoxLayout *cpuCardLayout;
    QLabel *cpuLabel;
    QLabel *cpuValueLabel;
    QSpacerItem *metricsSpacer;
    QHBoxLayout *exportLayout;
    QSpacerItem *exportSpacer;
    QPushButton *exportCsvButton;
    QPushButton *exportImageButton;
    QWidget *concurrencyTab;
    QVBoxLayout *concurrencyLayout;
    QHBoxLayout *concurrencyHeaderLayout;
    QLabel *scenarioLabel;
    QComboBox *scenarioCombo;
    QPushButton *runScenarioButton;
    QSpacerItem *concurrencyHeaderSpacer;
    QGridLayout *scenarioGrid;
    QLabel *producerLabel;
    QSpinBox *producerSpin;
    QLabel *consumerLabel;
    QSpinBox *consumerSpin;
    QLabel *bufferLabel;
    QSpinBox *bufferSpin;
    QLabel *cycleLabel;
    QSpinBox *cycleSpin;
    QLabel *readerLabel;
    QSpinBox *readerSpin;
    QLabel *writerLabel;
    QSpinBox *writerSpin;
    QLabel *chairsLabel;
    QSpinBox *chairsSpin;
    QLabel *customersLabel;
    QSpinBox *customersSpin;
    QTableWidget *concurrencyTable;
    QLabel *concurrencySummaryLabel;
    QWidget *memoryTab;
    QVBoxLayout *memoryLayout;
    QGridLayout *memoryInputGrid;
    QLabel *referenceLabel;
    QLineEdit *referenceLine;
    QLabel *framesLabel;
    QSpinBox *framesSpin;
    QLabel *tlbLabel;
    QSpinBox *tlbSpin;
    QLabel *policyLabel;
    QComboBox *policyCombo;
    QPushButton *sampleReferenceButton;
    QPushButton *runMemoryButton;
    QTableWidget *memoryTable;
    QLabel *memorySummaryLabel;
    QWidget *dataTab;
    QVBoxLayout *dataLayout;
    QLabel *dataPlaceholderLabel;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *principal)
    {
        if (principal->objectName().isEmpty())
            principal->setObjectName(QString::fromUtf8("principal"));
        principal->resize(1280, 934);
        centralwidget = new QWidget(principal);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        mainLayout = new QVBoxLayout(centralwidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        schedulingTab = new QWidget();
        schedulingTab->setObjectName(QString::fromUtf8("schedulingTab"));
        schedulingLayout = new QVBoxLayout(schedulingTab);
        schedulingLayout->setObjectName(QString::fromUtf8("schedulingLayout"));
        controlBarLayout = new QHBoxLayout();
        controlBarLayout->setObjectName(QString::fromUtf8("controlBarLayout"));
        algorithmLabel = new QLabel(schedulingTab);
        algorithmLabel->setObjectName(QString::fromUtf8("algorithmLabel"));

        controlBarLayout->addWidget(algorithmLabel);

        algorithmCombo = new QComboBox(schedulingTab);
        algorithmCombo->setObjectName(QString::fromUtf8("algorithmCombo"));

        controlBarLayout->addWidget(algorithmCombo);

        quantumLabel = new QLabel(schedulingTab);
        quantumLabel->setObjectName(QString::fromUtf8("quantumLabel"));

        controlBarLayout->addWidget(quantumLabel);

        quantumSpin = new QSpinBox(schedulingTab);
        quantumSpin->setObjectName(QString::fromUtf8("quantumSpin"));
        quantumSpin->setMinimum(1);
        quantumSpin->setMaximum(1000);
        quantumSpin->setValue(2);

        controlBarLayout->addWidget(quantumSpin);

        addProcessButton = new QPushButton(schedulingTab);
        addProcessButton->setObjectName(QString::fromUtf8("addProcessButton"));

        controlBarLayout->addWidget(addProcessButton);

        removeProcessButton = new QPushButton(schedulingTab);
        removeProcessButton->setObjectName(QString::fromUtf8("removeProcessButton"));

        controlBarLayout->addWidget(removeProcessButton);

        loadSampleButton = new QPushButton(schedulingTab);
        loadSampleButton->setObjectName(QString::fromUtf8("loadSampleButton"));

        controlBarLayout->addWidget(loadSampleButton);

        clearProcessesButton = new QPushButton(schedulingTab);
        clearProcessesButton->setObjectName(QString::fromUtf8("clearProcessesButton"));

        controlBarLayout->addWidget(clearProcessesButton);

        controlSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        controlBarLayout->addItem(controlSpacer);

        priorityNoteLabel = new QLabel(schedulingTab);
        priorityNoteLabel->setObjectName(QString::fromUtf8("priorityNoteLabel"));

        controlBarLayout->addWidget(priorityNoteLabel);


        schedulingLayout->addLayout(controlBarLayout);

        schedulingFrame = new QFrame(schedulingTab);
        schedulingFrame->setObjectName(QString::fromUtf8("schedulingFrame"));
        schedulingFrame->setFrameShape(QFrame::StyledPanel);
        schedulingFrame->setFrameShadow(QFrame::Raised);
        schedulingMainLayout = new QHBoxLayout(schedulingFrame);
        schedulingMainLayout->setObjectName(QString::fromUtf8("schedulingMainLayout"));
        scenarioPanel = new QFrame(schedulingFrame);
        scenarioPanel->setObjectName(QString::fromUtf8("scenarioPanel"));
        scenarioPanel->setFrameShape(QFrame::NoFrame);
        scenarioLayout = new QVBoxLayout(scenarioPanel);
        scenarioLayout->setObjectName(QString::fromUtf8("scenarioLayout"));
        scenarioTitleLabel = new QLabel(scenarioPanel);
        scenarioTitleLabel->setObjectName(QString::fromUtf8("scenarioTitleLabel"));
        scenarioTitleLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        scenarioLayout->addWidget(scenarioTitleLabel);

        processTable = new QTableWidget(scenarioPanel);
        if (processTable->columnCount() < 4)
            processTable->setColumnCount(4);
        processTable->setObjectName(QString::fromUtf8("processTable"));
        processTable->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        processTable->setAlternatingRowColors(true);
        processTable->setSelectionMode(QAbstractItemView::SingleSelection);
        processTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        processTable->setColumnCount(4);

        scenarioLayout->addWidget(processTable);

        scenarioButtonsLayout = new QHBoxLayout();
        scenarioButtonsLayout->setObjectName(QString::fromUtf8("scenarioButtonsLayout"));
        loadScenarioButton = new QPushButton(scenarioPanel);
        loadScenarioButton->setObjectName(QString::fromUtf8("loadScenarioButton"));

        scenarioButtonsLayout->addWidget(loadScenarioButton);

        saveScenarioButton = new QPushButton(scenarioPanel);
        saveScenarioButton->setObjectName(QString::fromUtf8("saveScenarioButton"));

        scenarioButtonsLayout->addWidget(saveScenarioButton);


        scenarioLayout->addLayout(scenarioButtonsLayout);

        automaticCheck = new QCheckBox(scenarioPanel);
        automaticCheck->setObjectName(QString::fromUtf8("automaticCheck"));

        scenarioLayout->addWidget(automaticCheck);

        startScenarioButton = new QPushButton(scenarioPanel);
        startScenarioButton->setObjectName(QString::fromUtf8("startScenarioButton"));

        scenarioLayout->addWidget(startScenarioButton);

        logTitleLabel = new QLabel(scenarioPanel);
        logTitleLabel->setObjectName(QString::fromUtf8("logTitleLabel"));

        scenarioLayout->addWidget(logTitleLabel);

        logListWidget = new QListWidget(scenarioPanel);
        logListWidget->setObjectName(QString::fromUtf8("logListWidget"));

        scenarioLayout->addWidget(logListWidget);


        schedulingMainLayout->addWidget(scenarioPanel);

        timelinePanel = new QFrame(schedulingFrame);
        timelinePanel->setObjectName(QString::fromUtf8("timelinePanel"));
        timelinePanel->setFrameShape(QFrame::NoFrame);
        timelineLayout = new QVBoxLayout(timelinePanel);
        timelineLayout->setObjectName(QString::fromUtf8("timelineLayout"));
        timelineHeadingLabel = new QLabel(timelinePanel);
        timelineHeadingLabel->setObjectName(QString::fromUtf8("timelineHeadingLabel"));
        timelineHeadingLabel->setAlignment(Qt::AlignCenter);

        timelineLayout->addWidget(timelineHeadingLabel);

        timelineWidget = new ScheduleTimelineWidget(timelinePanel);
        timelineWidget->setObjectName(QString::fromUtf8("timelineWidget"));

        timelineLayout->addWidget(timelineWidget);


        schedulingMainLayout->addWidget(timelinePanel);

        metricsPanel = new QFrame(schedulingFrame);
        metricsPanel->setObjectName(QString::fromUtf8("metricsPanel"));
        metricsPanel->setFrameShape(QFrame::NoFrame);
        metricsLayout = new QVBoxLayout(metricsPanel);
        metricsLayout->setObjectName(QString::fromUtf8("metricsLayout"));
        waitCard = new QFrame(metricsPanel);
        waitCard->setObjectName(QString::fromUtf8("waitCard"));
        waitCard->setFrameShape(QFrame::StyledPanel);
        waitCard->setFrameShadow(QFrame::Raised);
        waitCardLayout = new QVBoxLayout(waitCard);
        waitCardLayout->setObjectName(QString::fromUtf8("waitCardLayout"));
        waitingLabel = new QLabel(waitCard);
        waitingLabel->setObjectName(QString::fromUtf8("waitingLabel"));
        waitingLabel->setAlignment(Qt::AlignCenter);

        waitCardLayout->addWidget(waitingLabel);

        waitingValueLabel = new QLabel(waitCard);
        waitingValueLabel->setObjectName(QString::fromUtf8("waitingValueLabel"));
        waitingValueLabel->setAlignment(Qt::AlignCenter);
        waitingValueLabel->setMargin(4);

        waitCardLayout->addWidget(waitingValueLabel);


        metricsLayout->addWidget(waitCard);

        turnaroundCard = new QFrame(metricsPanel);
        turnaroundCard->setObjectName(QString::fromUtf8("turnaroundCard"));
        turnaroundCard->setFrameShape(QFrame::StyledPanel);
        turnaroundCard->setFrameShadow(QFrame::Raised);
        turnaroundCardLayout = new QVBoxLayout(turnaroundCard);
        turnaroundCardLayout->setObjectName(QString::fromUtf8("turnaroundCardLayout"));
        turnaroundLabel = new QLabel(turnaroundCard);
        turnaroundLabel->setObjectName(QString::fromUtf8("turnaroundLabel"));
        turnaroundLabel->setAlignment(Qt::AlignCenter);

        turnaroundCardLayout->addWidget(turnaroundLabel);

        turnaroundValueLabel = new QLabel(turnaroundCard);
        turnaroundValueLabel->setObjectName(QString::fromUtf8("turnaroundValueLabel"));
        turnaroundValueLabel->setAlignment(Qt::AlignCenter);

        turnaroundCardLayout->addWidget(turnaroundValueLabel);


        metricsLayout->addWidget(turnaroundCard);

        responseCard = new QFrame(metricsPanel);
        responseCard->setObjectName(QString::fromUtf8("responseCard"));
        responseCard->setFrameShape(QFrame::StyledPanel);
        responseCard->setFrameShadow(QFrame::Raised);
        responseCardLayout = new QVBoxLayout(responseCard);
        responseCardLayout->setObjectName(QString::fromUtf8("responseCardLayout"));
        responseLabel = new QLabel(responseCard);
        responseLabel->setObjectName(QString::fromUtf8("responseLabel"));
        responseLabel->setAlignment(Qt::AlignCenter);

        responseCardLayout->addWidget(responseLabel);

        responseValueLabel = new QLabel(responseCard);
        responseValueLabel->setObjectName(QString::fromUtf8("responseValueLabel"));
        responseValueLabel->setAlignment(Qt::AlignCenter);

        responseCardLayout->addWidget(responseValueLabel);


        metricsLayout->addWidget(responseCard);

        cpuCard = new QFrame(metricsPanel);
        cpuCard->setObjectName(QString::fromUtf8("cpuCard"));
        cpuCard->setFrameShape(QFrame::StyledPanel);
        cpuCard->setFrameShadow(QFrame::Raised);
        cpuCardLayout = new QVBoxLayout(cpuCard);
        cpuCardLayout->setObjectName(QString::fromUtf8("cpuCardLayout"));
        cpuLabel = new QLabel(cpuCard);
        cpuLabel->setObjectName(QString::fromUtf8("cpuLabel"));
        cpuLabel->setAlignment(Qt::AlignCenter);

        cpuCardLayout->addWidget(cpuLabel);

        cpuValueLabel = new QLabel(cpuCard);
        cpuValueLabel->setObjectName(QString::fromUtf8("cpuValueLabel"));
        cpuValueLabel->setAlignment(Qt::AlignCenter);

        cpuCardLayout->addWidget(cpuValueLabel);


        metricsLayout->addWidget(cpuCard);

        metricsSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        metricsLayout->addItem(metricsSpacer);


        schedulingMainLayout->addWidget(metricsPanel);


        schedulingLayout->addWidget(schedulingFrame);

        exportLayout = new QHBoxLayout();
        exportLayout->setObjectName(QString::fromUtf8("exportLayout"));
        exportSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        exportLayout->addItem(exportSpacer);

        exportCsvButton = new QPushButton(schedulingTab);
        exportCsvButton->setObjectName(QString::fromUtf8("exportCsvButton"));

        exportLayout->addWidget(exportCsvButton);

        exportImageButton = new QPushButton(schedulingTab);
        exportImageButton->setObjectName(QString::fromUtf8("exportImageButton"));

        exportLayout->addWidget(exportImageButton);


        schedulingLayout->addLayout(exportLayout);

        tabWidget->addTab(schedulingTab, QString());
        tabWidget->setTabText(tabWidget->indexOf(schedulingTab), QString::fromUtf8("Planificacion CPU"));
        concurrencyTab = new QWidget();
        concurrencyTab->setObjectName(QString::fromUtf8("concurrencyTab"));
        concurrencyLayout = new QVBoxLayout(concurrencyTab);
        concurrencyLayout->setObjectName(QString::fromUtf8("concurrencyLayout"));
        concurrencyHeaderLayout = new QHBoxLayout();
        concurrencyHeaderLayout->setObjectName(QString::fromUtf8("concurrencyHeaderLayout"));
        scenarioLabel = new QLabel(concurrencyTab);
        scenarioLabel->setObjectName(QString::fromUtf8("scenarioLabel"));

        concurrencyHeaderLayout->addWidget(scenarioLabel);

        scenarioCombo = new QComboBox(concurrencyTab);
        scenarioCombo->setObjectName(QString::fromUtf8("scenarioCombo"));

        concurrencyHeaderLayout->addWidget(scenarioCombo);

        runScenarioButton = new QPushButton(concurrencyTab);
        runScenarioButton->setObjectName(QString::fromUtf8("runScenarioButton"));

        concurrencyHeaderLayout->addWidget(runScenarioButton);

        concurrencyHeaderSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        concurrencyHeaderLayout->addItem(concurrencyHeaderSpacer);


        concurrencyLayout->addLayout(concurrencyHeaderLayout);

        scenarioGrid = new QGridLayout();
        scenarioGrid->setObjectName(QString::fromUtf8("scenarioGrid"));
        producerLabel = new QLabel(concurrencyTab);
        producerLabel->setObjectName(QString::fromUtf8("producerLabel"));

        scenarioGrid->addWidget(producerLabel, 0, 0, 1, 1);

        producerSpin = new QSpinBox(concurrencyTab);
        producerSpin->setObjectName(QString::fromUtf8("producerSpin"));
        producerSpin->setMinimum(1);
        producerSpin->setValue(2);

        scenarioGrid->addWidget(producerSpin, 0, 1, 1, 1);

        consumerLabel = new QLabel(concurrencyTab);
        consumerLabel->setObjectName(QString::fromUtf8("consumerLabel"));

        scenarioGrid->addWidget(consumerLabel, 0, 2, 1, 1);

        consumerSpin = new QSpinBox(concurrencyTab);
        consumerSpin->setObjectName(QString::fromUtf8("consumerSpin"));
        consumerSpin->setMinimum(1);
        consumerSpin->setValue(2);

        scenarioGrid->addWidget(consumerSpin, 0, 3, 1, 1);

        bufferLabel = new QLabel(concurrencyTab);
        bufferLabel->setObjectName(QString::fromUtf8("bufferLabel"));

        scenarioGrid->addWidget(bufferLabel, 1, 0, 1, 1);

        bufferSpin = new QSpinBox(concurrencyTab);
        bufferSpin->setObjectName(QString::fromUtf8("bufferSpin"));
        bufferSpin->setMinimum(1);
        bufferSpin->setMaximum(64);
        bufferSpin->setValue(5);

        scenarioGrid->addWidget(bufferSpin, 1, 1, 1, 1);

        cycleLabel = new QLabel(concurrencyTab);
        cycleLabel->setObjectName(QString::fromUtf8("cycleLabel"));

        scenarioGrid->addWidget(cycleLabel, 1, 2, 1, 1);

        cycleSpin = new QSpinBox(concurrencyTab);
        cycleSpin->setObjectName(QString::fromUtf8("cycleSpin"));
        cycleSpin->setMinimum(1);
        cycleSpin->setMaximum(20);
        cycleSpin->setValue(3);

        scenarioGrid->addWidget(cycleSpin, 1, 3, 1, 1);

        readerLabel = new QLabel(concurrencyTab);
        readerLabel->setObjectName(QString::fromUtf8("readerLabel"));

        scenarioGrid->addWidget(readerLabel, 2, 0, 1, 1);

        readerSpin = new QSpinBox(concurrencyTab);
        readerSpin->setObjectName(QString::fromUtf8("readerSpin"));
        readerSpin->setMinimum(1);
        readerSpin->setValue(3);

        scenarioGrid->addWidget(readerSpin, 2, 1, 1, 1);

        writerLabel = new QLabel(concurrencyTab);
        writerLabel->setObjectName(QString::fromUtf8("writerLabel"));

        scenarioGrid->addWidget(writerLabel, 2, 2, 1, 1);

        writerSpin = new QSpinBox(concurrencyTab);
        writerSpin->setObjectName(QString::fromUtf8("writerSpin"));
        writerSpin->setMinimum(1);
        writerSpin->setValue(2);

        scenarioGrid->addWidget(writerSpin, 2, 3, 1, 1);

        chairsLabel = new QLabel(concurrencyTab);
        chairsLabel->setObjectName(QString::fromUtf8("chairsLabel"));

        scenarioGrid->addWidget(chairsLabel, 3, 0, 1, 1);

        chairsSpin = new QSpinBox(concurrencyTab);
        chairsSpin->setObjectName(QString::fromUtf8("chairsSpin"));
        chairsSpin->setMinimum(0);
        chairsSpin->setMaximum(10);
        chairsSpin->setValue(3);

        scenarioGrid->addWidget(chairsSpin, 3, 1, 1, 1);

        customersLabel = new QLabel(concurrencyTab);
        customersLabel->setObjectName(QString::fromUtf8("customersLabel"));

        scenarioGrid->addWidget(customersLabel, 3, 2, 1, 1);

        customersSpin = new QSpinBox(concurrencyTab);
        customersSpin->setObjectName(QString::fromUtf8("customersSpin"));
        customersSpin->setMinimum(1);
        customersSpin->setMaximum(40);
        customersSpin->setValue(10);

        scenarioGrid->addWidget(customersSpin, 3, 3, 1, 1);


        concurrencyLayout->addLayout(scenarioGrid);

        concurrencyTable = new QTableWidget(concurrencyTab);
        if (concurrencyTable->columnCount() < 4)
            concurrencyTable->setColumnCount(4);
        concurrencyTable->setObjectName(QString::fromUtf8("concurrencyTable"));
        concurrencyTable->setAlternatingRowColors(true);
        concurrencyTable->setSelectionMode(QAbstractItemView::NoSelection);
        concurrencyTable->setColumnCount(4);

        concurrencyLayout->addWidget(concurrencyTable);

        concurrencySummaryLabel = new QLabel(concurrencyTab);
        concurrencySummaryLabel->setObjectName(QString::fromUtf8("concurrencySummaryLabel"));

        concurrencyLayout->addWidget(concurrencySummaryLabel);

        tabWidget->addTab(concurrencyTab, QString());
        memoryTab = new QWidget();
        memoryTab->setObjectName(QString::fromUtf8("memoryTab"));
        QFont font;
        font.setPointSize(12);
        memoryTab->setFont(font);
        memoryLayout = new QVBoxLayout(memoryTab);
        memoryLayout->setObjectName(QString::fromUtf8("memoryLayout"));
        memoryInputGrid = new QGridLayout();
        memoryInputGrid->setObjectName(QString::fromUtf8("memoryInputGrid"));
        referenceLabel = new QLabel(memoryTab);
        referenceLabel->setObjectName(QString::fromUtf8("referenceLabel"));

        memoryInputGrid->addWidget(referenceLabel, 0, 0, 1, 1);

        referenceLine = new QLineEdit(memoryTab);
        referenceLine->setObjectName(QString::fromUtf8("referenceLine"));

        memoryInputGrid->addWidget(referenceLine, 0, 1, 1, 3);

        framesLabel = new QLabel(memoryTab);
        framesLabel->setObjectName(QString::fromUtf8("framesLabel"));

        memoryInputGrid->addWidget(framesLabel, 1, 0, 1, 1);

        framesSpin = new QSpinBox(memoryTab);
        framesSpin->setObjectName(QString::fromUtf8("framesSpin"));
        framesSpin->setMinimum(1);
        framesSpin->setMaximum(12);
        framesSpin->setValue(3);

        memoryInputGrid->addWidget(framesSpin, 1, 1, 1, 1);

        tlbLabel = new QLabel(memoryTab);
        tlbLabel->setObjectName(QString::fromUtf8("tlbLabel"));

        memoryInputGrid->addWidget(tlbLabel, 1, 2, 1, 1);

        tlbSpin = new QSpinBox(memoryTab);
        tlbSpin->setObjectName(QString::fromUtf8("tlbSpin"));
        tlbSpin->setMinimum(0);
        tlbSpin->setMaximum(12);
        tlbSpin->setValue(2);

        memoryInputGrid->addWidget(tlbSpin, 1, 3, 1, 1);

        policyLabel = new QLabel(memoryTab);
        policyLabel->setObjectName(QString::fromUtf8("policyLabel"));

        memoryInputGrid->addWidget(policyLabel, 2, 0, 1, 1);

        policyCombo = new QComboBox(memoryTab);
        policyCombo->setObjectName(QString::fromUtf8("policyCombo"));

        memoryInputGrid->addWidget(policyCombo, 2, 1, 1, 1);

        sampleReferenceButton = new QPushButton(memoryTab);
        sampleReferenceButton->setObjectName(QString::fromUtf8("sampleReferenceButton"));

        memoryInputGrid->addWidget(sampleReferenceButton, 2, 2, 1, 1);

        runMemoryButton = new QPushButton(memoryTab);
        runMemoryButton->setObjectName(QString::fromUtf8("runMemoryButton"));

        memoryInputGrid->addWidget(runMemoryButton, 2, 3, 1, 1);


        memoryLayout->addLayout(memoryInputGrid);

        memoryTable = new QTableWidget(memoryTab);
        if (memoryTable->columnCount() < 6)
            memoryTable->setColumnCount(6);
        memoryTable->setObjectName(QString::fromUtf8("memoryTable"));
        memoryTable->setAlternatingRowColors(true);
        memoryTable->setSelectionMode(QAbstractItemView::NoSelection);
        memoryTable->setColumnCount(6);

        memoryLayout->addWidget(memoryTable);

        memorySummaryLabel = new QLabel(memoryTab);
        memorySummaryLabel->setObjectName(QString::fromUtf8("memorySummaryLabel"));

        memoryLayout->addWidget(memorySummaryLabel);

        tabWidget->addTab(memoryTab, QString());
        dataTab = new QWidget();
        dataTab->setObjectName(QString::fromUtf8("dataTab"));
        dataLayout = new QVBoxLayout(dataTab);
        dataLayout->setObjectName(QString::fromUtf8("dataLayout"));
        dataPlaceholderLabel = new QLabel(dataTab);
        dataPlaceholderLabel->setObjectName(QString::fromUtf8("dataPlaceholderLabel"));
        dataPlaceholderLabel->setAlignment(Qt::AlignCenter);

        dataLayout->addWidget(dataPlaceholderLabel);

        tabWidget->addTab(dataTab, QString());

        mainLayout->addWidget(tabWidget);

        principal->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(principal);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        principal->setStatusBar(statusbar);

        retranslateUi(principal);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(principal);
    } // setupUi

    void retranslateUi(QMainWindow *principal)
    {
        principal->setWindowTitle(QCoreApplication::translate("principal", "Simulador de Algoritmos de Planificacion, Semaforos e Interfaz OE con Laboratorios de Memoria Virtual en Linux", nullptr));
        algorithmLabel->setText(QCoreApplication::translate("principal", "Algoritmo:", nullptr));
        quantumLabel->setText(QCoreApplication::translate("principal", "Quantum:", nullptr));
        addProcessButton->setText(QCoreApplication::translate("principal", "Agregar proceso", nullptr));
        removeProcessButton->setText(QCoreApplication::translate("principal", "Eliminar seleccion", nullptr));
        loadSampleButton->setText(QCoreApplication::translate("principal", "Escenario ejemplo", nullptr));
        clearProcessesButton->setText(QCoreApplication::translate("principal", "Limpiar", nullptr));
        priorityNoteLabel->setText(QCoreApplication::translate("principal", "Prioridad baja = mayor prioridad", nullptr));
        scenarioTitleLabel->setText(QCoreApplication::translate("principal", "Escenario", nullptr));
        loadScenarioButton->setText(QCoreApplication::translate("principal", "Cargar...", nullptr));
        saveScenarioButton->setText(QCoreApplication::translate("principal", "Guardar", nullptr));
        automaticCheck->setText(QCoreApplication::translate("principal", "Automatico", nullptr));
        startScenarioButton->setText(QCoreApplication::translate("principal", "Iniciar", nullptr));
        logTitleLabel->setText(QCoreApplication::translate("principal", "Registro", nullptr));
        timelineHeadingLabel->setText(QCoreApplication::translate("principal", "Linea de tiempo", nullptr));
        waitingLabel->setText(QCoreApplication::translate("principal", "Tiempo de espera", nullptr));
        waitingValueLabel->setText(QCoreApplication::translate("principal", "--", nullptr));
        turnaroundLabel->setText(QCoreApplication::translate("principal", "Tiempo de retorno", nullptr));
        turnaroundValueLabel->setText(QCoreApplication::translate("principal", "--", nullptr));
        responseLabel->setText(QCoreApplication::translate("principal", "Tiempo de respuesta", nullptr));
        responseValueLabel->setText(QCoreApplication::translate("principal", "--", nullptr));
        cpuLabel->setText(QCoreApplication::translate("principal", "Uso de CPU", nullptr));
        cpuValueLabel->setText(QCoreApplication::translate("principal", "--", nullptr));
        exportCsvButton->setText(QCoreApplication::translate("principal", "Exportar a CSV", nullptr));
        exportImageButton->setText(QCoreApplication::translate("principal", "Exportar a imagen", nullptr));
        scenarioLabel->setText(QCoreApplication::translate("principal", "Escenario:", nullptr));
        runScenarioButton->setText(QCoreApplication::translate("principal", "Simular", nullptr));
        producerLabel->setText(QCoreApplication::translate("principal", "Productores:", nullptr));
        consumerLabel->setText(QCoreApplication::translate("principal", "Consumidores:", nullptr));
        bufferLabel->setText(QCoreApplication::translate("principal", "Tamano buffer:", nullptr));
        cycleLabel->setText(QCoreApplication::translate("principal", "Ciclos:", nullptr));
        readerLabel->setText(QCoreApplication::translate("principal", "Lectores:", nullptr));
        writerLabel->setText(QCoreApplication::translate("principal", "Escritores:", nullptr));
        chairsLabel->setText(QCoreApplication::translate("principal", "Sillas:", nullptr));
        customersLabel->setText(QCoreApplication::translate("principal", "Clientes:", nullptr));
        concurrencySummaryLabel->setText(QCoreApplication::translate("principal", "Pasos generados: 0", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(concurrencyTab), QCoreApplication::translate("principal", "Concurrencia", nullptr));
        referenceLabel->setText(QCoreApplication::translate("principal", "Referencias (espacio o coma):", nullptr));
        framesLabel->setText(QCoreApplication::translate("principal", "Marcos:", nullptr));
        tlbLabel->setText(QCoreApplication::translate("principal", "Entradas TLB:", nullptr));
        policyLabel->setText(QCoreApplication::translate("principal", "Politica:", nullptr));
        sampleReferenceButton->setText(QCoreApplication::translate("principal", "Cargar ejemplo", nullptr));
        runMemoryButton->setText(QCoreApplication::translate("principal", "Simular", nullptr));
        memorySummaryLabel->setText(QCoreApplication::translate("principal", "Fallos de pagina: 0 | TLB hits: 0 (0%)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(memoryTab), QCoreApplication::translate("principal", "Memoria Virtual", nullptr));
        dataPlaceholderLabel->setText(QCoreApplication::translate("principal", "Anade aqui materiales adicionales o documentacion del laboratorio.", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(dataTab), QCoreApplication::translate("principal", "Datos/Escenarios", nullptr));
    } // retranslateUi

};

namespace Ui {
    class principal: public Ui_principal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRINCIPAL_H
