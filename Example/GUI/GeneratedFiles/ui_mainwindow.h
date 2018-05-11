/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButtonCompute;
    QLabel *label_7;
    QLabel *labelClusteringRateMax;
    QComboBox *comboBoxData;
    QLabel *labelProject;
    QTabWidget *tabWidget;
    QWidget *tab;
    QCustomPlot *customPlot;
    QWidget *tab_2;
    QLabel *Image;
    QComboBox *comboBoxSet;
    QSpinBox *spinBoxImageId;
    QLabel *labelImage;
    QLabel *label_1;
    QLabel *label_2;
    QPushButton *pushButtonAddLayer;
    QComboBox *comboBoxLayer;
    QFrame *line;
    QComboBox *comboBoxActivationfunction;
    QSpinBox *spinBoxNeurons;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEditInformation;
    QLabel *label_5;
    QPushButton *pushButtonConsole;
    QPushButton *pushButtonRemoveLayer;
    QLabel *labelLoading;
    QFrame *line_2;
    QLabel *label_6;
    QTimeEdit *timeEdit;
    QLineEdit *lineEditCount;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLabel *label;
    QLineEdit *lineEditIteration;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(850, 500);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMinimumSize(QSize(0, 0));
        pushButtonCompute = new QPushButton(centralWidget);
        pushButtonCompute->setObjectName(QStringLiteral("pushButtonCompute"));
        pushButtonCompute->setGeometry(QRect(710, 460, 80, 22));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 270, 51, 21));
        labelClusteringRateMax = new QLabel(centralWidget);
        labelClusteringRateMax->setObjectName(QStringLiteral("labelClusteringRateMax"));
        labelClusteringRateMax->setGeometry(QRect(10, 340, 111, 21));
        comboBoxData = new QComboBox(centralWidget);
        comboBoxData->addItem(QString());
        comboBoxData->addItem(QString());
        comboBoxData->addItem(QString());
        comboBoxData->setObjectName(QStringLiteral("comboBoxData"));
        comboBoxData->setGeometry(QRect(60, 10, 111, 22));
        labelProject = new QLabel(centralWidget);
        labelProject->setObjectName(QStringLiteral("labelProject"));
        labelProject->setGeometry(QRect(10, 10, 60, 21));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(180, 1, 661, 441));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        customPlot = new QCustomPlot(tab);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        customPlot->setGeometry(QRect(10, 14, 641, 391));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        Image = new QLabel(tab_2);
        Image->setObjectName(QStringLiteral("Image"));
        Image->setGeometry(QRect(20, 10, 300, 300));
        comboBoxSet = new QComboBox(tab_2);
        comboBoxSet->setObjectName(QStringLiteral("comboBoxSet"));
        comboBoxSet->setGeometry(QRect(10, 380, 81, 22));
        spinBoxImageId = new QSpinBox(tab_2);
        spinBoxImageId->setObjectName(QStringLiteral("spinBoxImageId"));
        spinBoxImageId->setGeometry(QRect(10, 350, 81, 22));
        spinBoxImageId->setMaximum(9999);
        labelImage = new QLabel(tab_2);
        labelImage->setObjectName(QStringLiteral("labelImage"));
        labelImage->setGeometry(QRect(10, 330, 81, 16));
        tabWidget->addTab(tab_2, QString());
        label_1 = new QLabel(centralWidget);
        label_1->setObjectName(QStringLiteral("label_1"));
        label_1->setGeometry(QRect(10, 310, 91, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 70, 41, 21));
        pushButtonAddLayer = new QPushButton(centralWidget);
        pushButtonAddLayer->setObjectName(QStringLiteral("pushButtonAddLayer"));
        pushButtonAddLayer->setGeometry(QRect(125, 70, 22, 22));
        QIcon icon;
        icon.addFile(QStringLiteral("Extra Files/add-circle-20.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonAddLayer->setIcon(icon);
        comboBoxLayer = new QComboBox(centralWidget);
        comboBoxLayer->setObjectName(QStringLiteral("comboBoxLayer"));
        comboBoxLayer->setGeometry(QRect(60, 70, 61, 22));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(0, 29, 181, 41));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        comboBoxActivationfunction = new QComboBox(centralWidget);
        comboBoxActivationfunction->addItem(QString());
        comboBoxActivationfunction->addItem(QString());
        comboBoxActivationfunction->addItem(QString());
        comboBoxActivationfunction->addItem(QString());
        comboBoxActivationfunction->setObjectName(QStringLiteral("comboBoxActivationfunction"));
        comboBoxActivationfunction->setGeometry(QRect(60, 150, 111, 22));
        spinBoxNeurons = new QSpinBox(centralWidget);
        spinBoxNeurons->setObjectName(QStringLiteral("spinBoxNeurons"));
        spinBoxNeurons->setGeometry(QRect(60, 110, 51, 22));
        spinBoxNeurons->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinBoxNeurons->setMaximum(20000);
        spinBoxNeurons->setValue(0);
        spinBoxNeurons->setDisplayIntegerBase(10);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 110, 47, 21));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 140, 51, 31));
        lineEditInformation = new QLineEdit(centralWidget);
        lineEditInformation->setObjectName(QStringLiteral("lineEditInformation"));
        lineEditInformation->setGeometry(QRect(410, 460, 120, 22));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(340, 460, 71, 21));
        pushButtonConsole = new QPushButton(centralWidget);
        pushButtonConsole->setObjectName(QStringLiteral("pushButtonConsole"));
        pushButtonConsole->setGeometry(QRect(20, 460, 80, 22));
        pushButtonRemoveLayer = new QPushButton(centralWidget);
        pushButtonRemoveLayer->setObjectName(QStringLiteral("pushButtonRemoveLayer"));
        pushButtonRemoveLayer->setGeometry(QRect(150, 70, 22, 22));
        QIcon icon1;
        icon1.addFile(QStringLiteral("Extra Files/cancel-circle-20.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonRemoveLayer->setIcon(icon1);
        labelLoading = new QLabel(centralWidget);
        labelLoading->setObjectName(QStringLiteral("labelLoading"));
        labelLoading->setEnabled(true);
        labelLoading->setGeometry(QRect(798, 449, 40, 40));
        labelLoading->setScaledContents(true);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(0, 190, 181, 41));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 230, 51, 21));
        timeEdit = new QTimeEdit(centralWidget);
        timeEdit->setObjectName(QStringLiteral("timeEdit"));
        timeEdit->setGeometry(QRect(60, 230, 51, 22));
        timeEdit->setWrapping(false);
        timeEdit->setFrame(true);
        timeEdit->setReadOnly(true);
        timeEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
        timeEdit->setAccelerated(false);
        timeEdit->setKeyboardTracking(true);
        timeEdit->setProperty("showGroupSeparator", QVariant(false));
        timeEdit->setMaximumTime(QTime(23, 59, 59));
        timeEdit->setCalendarPopup(false);
        timeEdit->setTime(QTime(0, 0, 0));
        lineEditCount = new QLineEdit(centralWidget);
        lineEditCount->setObjectName(QStringLiteral("lineEditCount"));
        lineEditCount->setGeometry(QRect(60, 270, 50, 22));
        lineEditCount->setReadOnly(true);
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(130, 310, 41, 22));
        lineEdit_2->setReadOnly(true);
        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(130, 340, 41, 22));
        lineEdit_3->setReadOnly(true);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(180, 450, 51, 21));
        lineEditIteration = new QLineEdit(centralWidget);
        lineEditIteration->setObjectName(QStringLiteral("lineEditIteration"));
        lineEditIteration->setGeometry(QRect(230, 450, 50, 22));
        MainWindow->setCentralWidget(centralWidget);
        line->raise();
        line_2->raise();
        pushButtonCompute->raise();
        label_7->raise();
        labelClusteringRateMax->raise();
        comboBoxData->raise();
        labelProject->raise();
        tabWidget->raise();
        label_1->raise();
        label_2->raise();
        pushButtonAddLayer->raise();
        comboBoxLayer->raise();
        comboBoxActivationfunction->raise();
        spinBoxNeurons->raise();
        label_3->raise();
        label_4->raise();
        lineEditInformation->raise();
        label_5->raise();
        pushButtonConsole->raise();
        pushButtonRemoveLayer->raise();
        labelLoading->raise();
        label_6->raise();
        timeEdit->raise();
        lineEditCount->raise();
        lineEdit_2->raise();
        lineEdit_3->raise();
        label->raise();
        lineEditIteration->raise();

        retranslateUi(MainWindow);
        QObject::connect(pushButtonConsole, SIGNAL(clicked()), MainWindow, SLOT(on_pushButtonConsole_clicked()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButtonCompute->setText(QApplication::translate("MainWindow", "Compute", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Count :", nullptr));
        labelClusteringRateMax->setText(QApplication::translate("MainWindow", "Clustering Rate Max : ", nullptr));
        comboBoxData->setItemText(0, QApplication::translate("MainWindow", "MNIST", nullptr));
        comboBoxData->setItemText(1, QApplication::translate("MainWindow", "Iris", nullptr));
        comboBoxData->setItemText(2, QApplication::translate("MainWindow", "ParisTrees", nullptr));

        labelProject->setText(QApplication::translate("MainWindow", "Project :", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Graph of classification rate", nullptr));
        Image->setText(QString());
        labelImage->setText(QApplication::translate("MainWindow", "Label :", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Data visualization", nullptr));
        label_1->setText(QApplication::translate("MainWindow", "Clustering Rate :", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Layer  :", nullptr));
        pushButtonAddLayer->setText(QString());
        comboBoxActivationfunction->setItemText(0, QApplication::translate("MainWindow", "Sigmoid", nullptr));
        comboBoxActivationfunction->setItemText(1, QApplication::translate("MainWindow", "TanH", nullptr));
        comboBoxActivationfunction->setItemText(2, QApplication::translate("MainWindow", "ReLU", nullptr));
        comboBoxActivationfunction->setItemText(3, QApplication::translate("MainWindow", "Gaussian", nullptr));

        label_3->setText(QApplication::translate("MainWindow", "Neurons :", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "activation\n"
"function :", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Information :", nullptr));
        pushButtonConsole->setText(QApplication::translate("MainWindow", "Console", nullptr));
        pushButtonRemoveLayer->setText(QString());
        labelLoading->setText(QString());
        label_6->setText(QApplication::translate("MainWindow", "Timer :", nullptr));
        timeEdit->setDisplayFormat(QApplication::translate("MainWindow", "HH:mm:ss", nullptr));
        label->setText(QApplication::translate("MainWindow", "Iteration : ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
