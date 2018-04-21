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
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QLabel *labelCount;
    QLabel *labelClusteringRateMax;
    QComboBox *comboBox;
    QLabel *labelProject;
    QTabWidget *tabWidget;
    QWidget *tab;
    QCustomPlot *custom_plot;
    QWidget *tab_2;
    QLabel *Image;
    QComboBox *comboBoxSet;
    QSpinBox *spinBoxImageId;
    QLabel *labelImage;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton_2;
    QComboBox *comboBox_3;
    QFrame *line;
    QComboBox *comboBox_2;
    QSpinBox *spinBox;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEditInformation;
    QLabel *label_5;
    QPushButton *pushButtonConsole;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(850, 500);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMinimumSize(QSize(0, 0));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(750, 460, 80, 22));
        labelCount = new QLabel(centralWidget);
        labelCount->setObjectName(QStringLiteral("labelCount"));
        labelCount->setGeometry(QRect(750, 440, 81, 16));
        labelClusteringRateMax = new QLabel(centralWidget);
        labelClusteringRateMax->setObjectName(QStringLiteral("labelClusteringRateMax"));
        labelClusteringRateMax->setGeometry(QRect(180, 459, 150, 21));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(70, 10, 90, 22));
        labelProject = new QLabel(centralWidget);
        labelProject->setObjectName(QStringLiteral("labelProject"));
        labelProject->setGeometry(QRect(10, 10, 60, 21));
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
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(180, 430, 111, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 70, 41, 21));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(110, 70, 61, 22));
        comboBox_3 = new QComboBox(centralWidget);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));
        comboBox_3->setGeometry(QRect(53, 70, 51, 22));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(0, 29, 181, 41));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        comboBox_2 = new QComboBox(centralWidget);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(60, 150, 106, 22));
        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(60, 110, 106, 22));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 110, 47, 21));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 140, 51, 31));
        lineEditInformation = new QLineEdit(centralWidget);
        lineEditInformation->setObjectName(QStringLiteral("lineEditInformation"));
        lineEditInformation->setGeometry(QRect(540, 460, 120, 22));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(467, 460, 71, 21));
        pushButtonConsole = new QPushButton(centralWidget);
        pushButtonConsole->setObjectName(QStringLiteral("pushButtonConsole"));
        pushButtonConsole->setGeometry(QRect(20, 460, 80, 22));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);
        QObject::connect(pushButtonConsole, SIGNAL(clicked()), MainWindow, SLOT(on_pushButtonConsole_clicked()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Compute", nullptr));
        labelCount->setText(QApplication::translate("MainWindow", "Count :", nullptr));
        labelClusteringRateMax->setText(QApplication::translate("MainWindow", "Clustering Max : ", nullptr));
        labelProject->setText(QApplication::translate("MainWindow", "Project :", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Graph of classification rate", nullptr));
        Image->setText(QString());
        labelImage->setText(QApplication::translate("MainWindow", "Label :", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Data visualization", nullptr));
        label->setText(QApplication::translate("MainWindow", "Clustering Rate :", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Layer  :", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "Add layer", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Neurons :", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "activation\n"
"function :", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Information :", nullptr));
        pushButtonConsole->setText(QApplication::translate("MainWindow", "Console", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
