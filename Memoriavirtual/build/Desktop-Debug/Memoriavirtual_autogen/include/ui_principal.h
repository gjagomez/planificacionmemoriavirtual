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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_principal
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *principal)
    {
        if (principal->objectName().isEmpty())
            principal->setObjectName(QString::fromUtf8("principal"));
        principal->resize(800, 600);
        centralwidget = new QWidget(principal);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        principal->setCentralWidget(centralwidget);
        menubar = new QMenuBar(principal);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        principal->setMenuBar(menubar);
        statusbar = new QStatusBar(principal);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        principal->setStatusBar(statusbar);

        retranslateUi(principal);

        QMetaObject::connectSlotsByName(principal);
    } // setupUi

    void retranslateUi(QMainWindow *principal)
    {
        principal->setWindowTitle(QCoreApplication::translate("principal", "principal", nullptr));
    } // retranslateUi

};

namespace Ui {
    class principal: public Ui_principal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRINCIPAL_H
