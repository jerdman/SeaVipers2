/********************************************************************************
** Form generated from reading UI file 'seavipers2.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEAVIPERS2_H
#define UI_SEAVIPERS2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SeaVipers2Class
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QPushButton *initializeButton;
    QCheckBox *learningCheckBox;
    QGroupBox *groupBox_2;
    QLCDNumber *lcdNumber;
    QGroupBox *groupBox_3;
    QPushButton *ptuResetButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SeaVipers2Class)
    {
        if (SeaVipers2Class->objectName().isEmpty())
            SeaVipers2Class->setObjectName(QStringLiteral("SeaVipers2Class"));
        SeaVipers2Class->resize(800, 700);
        centralWidget = new QWidget(SeaVipers2Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 500, 351, 71));
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        initializeButton = new QPushButton(groupBox);
        initializeButton->setObjectName(QStringLiteral("initializeButton"));
        initializeButton->setGeometry(QRect(10, 15, 75, 23));
        learningCheckBox = new QCheckBox(groupBox);
        learningCheckBox->setObjectName(QStringLiteral("learningCheckBox"));
        learningCheckBox->setGeometry(QRect(100, 20, 70, 17));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(380, 500, 281, 71));
        lcdNumber = new QLCDNumber(groupBox_2);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(10, 20, 64, 23));
        lcdNumber->setAutoFillBackground(false);
        lcdNumber->setFrameShape(QFrame::Box);
        lcdNumber->setLineWidth(1);
        lcdNumber->setMidLineWidth(0);
        lcdNumber->setSmallDecimalPoint(true);
        lcdNumber->setDigitCount(6);
        lcdNumber->setSegmentStyle(QLCDNumber::Flat);
        lcdNumber->setProperty("value", QVariant(187.97));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 580, 351, 51));
        ptuResetButton = new QPushButton(groupBox_3);
        ptuResetButton->setObjectName(QStringLiteral("ptuResetButton"));
        ptuResetButton->setGeometry(QRect(10, 20, 75, 23));
        SeaVipers2Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SeaVipers2Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        SeaVipers2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SeaVipers2Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SeaVipers2Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SeaVipers2Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SeaVipers2Class->setStatusBar(statusBar);

        retranslateUi(SeaVipers2Class);

        QMetaObject::connectSlotsByName(SeaVipers2Class);
    } // setupUi

    void retranslateUi(QMainWindow *SeaVipers2Class)
    {
        SeaVipers2Class->setWindowTitle(QApplication::translate("SeaVipers2Class", "SeaVipers2", 0));
        groupBox->setTitle(QApplication::translate("SeaVipers2Class", "Tracker", 0));
        initializeButton->setText(QApplication::translate("SeaVipers2Class", "Initialize", 0));
        learningCheckBox->setText(QApplication::translate("SeaVipers2Class", "Learning", 0));
        groupBox_2->setTitle(QApplication::translate("SeaVipers2Class", "Rangefinder", 0));
        groupBox_3->setTitle(QApplication::translate("SeaVipers2Class", "PTU", 0));
        ptuResetButton->setText(QApplication::translate("SeaVipers2Class", "Reset", 0));
    } // retranslateUi

};

namespace Ui {
    class SeaVipers2Class: public Ui_SeaVipers2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEAVIPERS2_H
