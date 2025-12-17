/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_ip;
    QLineEdit *ipLineEdit;
    QLabel *label_port;
    QSpinBox *portSpinBox;
    QLabel *label_size;
    QSpinBox *sizeSpinBox;
    QLabel *label_maxSize;
    QSpinBox *maxSizeSpinBox;
    QLabel *label_interval;
    QSpinBox *intervalSpinBox;
    QLabel *label_pattern;
    QLineEdit *patternLineEdit;
    QCheckBox *incSizeCheckBox;
    QCheckBox *incContentCheckBox;
    QHBoxLayout *buttonLayout;
    QPushButton *startButton;
    QPushButton *stopButton;
    QTextEdit *logTextEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(520, 480);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_ip = new QLabel(groupBox);
        label_ip->setObjectName(QString::fromUtf8("label_ip"));

        gridLayout->addWidget(label_ip, 0, 0, 1, 1);

        ipLineEdit = new QLineEdit(groupBox);
        ipLineEdit->setObjectName(QString::fromUtf8("ipLineEdit"));

        gridLayout->addWidget(ipLineEdit, 0, 1, 1, 1);

        label_port = new QLabel(groupBox);
        label_port->setObjectName(QString::fromUtf8("label_port"));

        gridLayout->addWidget(label_port, 1, 0, 1, 1);

        portSpinBox = new QSpinBox(groupBox);
        portSpinBox->setObjectName(QString::fromUtf8("portSpinBox"));
        portSpinBox->setMaximum(65535);

        gridLayout->addWidget(portSpinBox, 1, 1, 1, 1);

        label_size = new QLabel(groupBox);
        label_size->setObjectName(QString::fromUtf8("label_size"));

        gridLayout->addWidget(label_size, 2, 0, 1, 1);

        sizeSpinBox = new QSpinBox(groupBox);
        sizeSpinBox->setObjectName(QString::fromUtf8("sizeSpinBox"));
        sizeSpinBox->setMaximum(65507);

        gridLayout->addWidget(sizeSpinBox, 2, 1, 1, 1);

        label_maxSize = new QLabel(groupBox);
        label_maxSize->setObjectName(QString::fromUtf8("label_maxSize"));

        gridLayout->addWidget(label_maxSize, 3, 0, 1, 1);

        maxSizeSpinBox = new QSpinBox(groupBox);
        maxSizeSpinBox->setObjectName(QString::fromUtf8("maxSizeSpinBox"));
        maxSizeSpinBox->setMaximum(65507);

        gridLayout->addWidget(maxSizeSpinBox, 3, 1, 1, 1);

        label_interval = new QLabel(groupBox);
        label_interval->setObjectName(QString::fromUtf8("label_interval"));

        gridLayout->addWidget(label_interval, 4, 0, 1, 1);

        intervalSpinBox = new QSpinBox(groupBox);
        intervalSpinBox->setObjectName(QString::fromUtf8("intervalSpinBox"));
        intervalSpinBox->setMaximum(60000);

        gridLayout->addWidget(intervalSpinBox, 4, 1, 1, 1);

        label_pattern = new QLabel(groupBox);
        label_pattern->setObjectName(QString::fromUtf8("label_pattern"));

        gridLayout->addWidget(label_pattern, 5, 0, 1, 1);

        patternLineEdit = new QLineEdit(groupBox);
        patternLineEdit->setObjectName(QString::fromUtf8("patternLineEdit"));

        gridLayout->addWidget(patternLineEdit, 5, 1, 1, 1);

        incSizeCheckBox = new QCheckBox(groupBox);
        incSizeCheckBox->setObjectName(QString::fromUtf8("incSizeCheckBox"));

        gridLayout->addWidget(incSizeCheckBox, 6, 0, 1, 1);

        incContentCheckBox = new QCheckBox(groupBox);
        incContentCheckBox->setObjectName(QString::fromUtf8("incContentCheckBox"));

        gridLayout->addWidget(incContentCheckBox, 7, 0, 1, 1);


        verticalLayout->addWidget(groupBox);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));
        startButton = new QPushButton(centralwidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        buttonLayout->addWidget(startButton);

        stopButton = new QPushButton(centralwidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));

        buttonLayout->addWidget(stopButton);


        verticalLayout->addLayout(buttonLayout);

        logTextEdit = new QTextEdit(centralwidget);
        logTextEdit->setObjectName(QString::fromUtf8("logTextEdit"));
        logTextEdit->setReadOnly(true);

        verticalLayout->addWidget(logTextEdit);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "UDP Sender", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Sender Settings", nullptr));
        label_ip->setText(QCoreApplication::translate("MainWindow", "Destination IP:", nullptr));
        label_port->setText(QCoreApplication::translate("MainWindow", "Port:", nullptr));
        label_size->setText(QCoreApplication::translate("MainWindow", "Initial Size:", nullptr));
        label_maxSize->setText(QCoreApplication::translate("MainWindow", "Max Size:", nullptr));
        label_interval->setText(QCoreApplication::translate("MainWindow", "Interval (ms):", nullptr));
        label_pattern->setText(QCoreApplication::translate("MainWindow", "Pattern (hex):", nullptr));
        incSizeCheckBox->setText(QCoreApplication::translate("MainWindow", "Increase Size", nullptr));
        incContentCheckBox->setText(QCoreApplication::translate("MainWindow", "Increment Content", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        stopButton->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
