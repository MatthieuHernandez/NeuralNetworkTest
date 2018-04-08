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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QSpinBox *spinBoxImageId;
    QPushButton *pushButton;
    QLabel *labelImage;
    QComboBox *comboBoxSet;
    QLabel *labelCount;
    QLabel *labelClusteringRateMax;
    QComboBox *comboBox;
    QLabel *labelProject;
    QTabWidget *tabWidget;
    QWidget *tab;
    QCustomPlot *custom_plot;
    QWidget *tab_2;
    QLabel *Image;
    QLabel *label;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(850, 500);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMinimumSize(QSize(0, 0));
        spinBoxImageId = new QSpinBox(centralWidget);
        spinBoxImageId->setObjectName(QStringLiteral("spinBoxImageId"));
        spinBoxImageId->setGeometry(QRect(10, 440, 81, 22));
        spinBoxImageId->setMaximum(9999);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(750, 460, 80, 21));
        labelImage = new QLabel(centralWidget);
        labelImage->setObjectName(QStringLiteral("labelImage"));
        labelImage->setGeometry(QRect(10, 420, 81, 16));
        comboBoxSet = new QComboBox(centralWidget);
        comboBoxSet->setObjectName(QStringLiteral("comboBoxSet"));
        comboBoxSet->setGeometry(QRect(10, 470, 81, 22));
        labelCount = new QLabel(centralWidget);
        labelCount->setObjectName(QStringLiteral("labelCount"));
        labelCount->setGeometry(QRect(750, 440, 81, 16));
        labelClusteringRateMax = new QLabel(centralWidget);
        labelClusteringRateMax->setObjectName(QStringLiteral("labelClusteringRateMax"));
        labelClusteringRateMax->setGeometry(QRect(180, 459, 150, 21));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(90, 10, 81, 22));
        labelProject = new QLabel(centralWidget);
        labelProject->setObjectName(QStringLiteral("labelProject"));
        labelProject->setGeometry(QRect(10, 10, 61, 22));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(180, 0, 671, 431));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        custom_plot = new QCustomPlot(tab);
        custom_plot->setObjectName(QStringLiteral("custom_plot"));
        custom_plot->setGeometry(QRect(10, 34, 651, 361));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        Image = new QLabel(tab_2);
        Image->setObjectName(QStringLiteral("Image"));
        Image->setGeometry(QRect(20, 10, 300, 300));
        tabWidget->addTab(tab_2, QString());
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(180, 430, 111, 21));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Compute", nullptr));
        labelImage->setText(QApplication::translate("MainWindow", "Label :", nullptr));
        labelCount->setText(QApplication::translate("MainWindow", "Count :", nullptr));
        labelClusteringRateMax->setText(QApplication::translate("MainWindow", "Clustering Max : ", nullptr));
        labelProject->setText(QApplication::translate("MainWindow", "Project :", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Graph of classification rate", nullptr));
        Image->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Data visualization", nullptr));
        label->setText(QApplication::translate("MainWindow", "Clustering Rate :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
