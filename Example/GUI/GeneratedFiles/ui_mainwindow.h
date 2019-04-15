/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCharts>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButtonCompute;
    QTabWidget *tabWidgetData;
    QWidget *tab;
    QChartView *chartView;
    QPushButton *pushButtonResetGraph;
    QWidget *tab_2;
    QWidget *gridLayoutWidget;
    QGridLayout *layout;
    QLineEdit *lineEditInformation;
    QLabel *label_5;
    QPushButton *pushButtonConsole;
    QLabel *labelLoading;
    QLabel *label;
    QSpinBox *spinBoxIteration;
    QTabWidget *tabWidgetNeuralNetwork;
    QWidget *tab_3;
    QFrame *line;
    QLabel *labelProject;
    QComboBox *comboBoxData;
    QLabel *label_7;
    QLabel *labelMax;
    QLabel *label_6;
    QLabel *label_1;
    QSpinBox *spinBoxCount;
    QSpinBox *spinBoxTrainingRating;
    QTimeEdit *timeEdit;
    QLabel *label_9;
    QLabel *label_8;
    QDoubleSpinBox *doubleSpinBoxCR;
    QDoubleSpinBox *doubleSpinBoxCRM;
    QPushButton *pushButtonEvaluate;
    QPushButton *pushButtonLoad;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonReset;
    QCheckBox *checkBoxAutoSave;
    QLabel *label_11;
    QLabel *label_12;
    QDoubleSpinBox *doubleSpinBoxWCR;
    QDoubleSpinBox *doubleSpinBoxF1S;
    QWidget *tab_4;
    QPushButton *pushButtonRemoveLayer;
    QLabel *label_2;
    QSpinBox *spinBoxNeurons;
    QComboBox *comboBoxLayer;
    QLabel *labelNeurons;
    QComboBox *comboBoxActivationFunction;
    QPushButton *pushButtonAddLayer;
    QLabel *label_4;
    QDoubleSpinBox *spinBoxLearningRate;
    QLabel *label_3;
    QLabel *label_10;
    QDoubleSpinBox *spinBoxMomentum;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(850, 500);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setMinimumSize(QSize(0, 0));
        pushButtonCompute = new QPushButton(centralWidget);
        pushButtonCompute->setObjectName(QString::fromUtf8("pushButtonCompute"));
        pushButtonCompute->setGeometry(QRect(720, 460, 70, 22));
        tabWidgetData = new QTabWidget(centralWidget);
        tabWidgetData->setObjectName(QString::fromUtf8("tabWidgetData"));
        tabWidgetData->setGeometry(QRect(180, 1, 670, 440));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        chartView = new QChartView(tab);
        chartView->setObjectName(QString::fromUtf8("chartView"));
        chartView->setGeometry(QRect(0, 0, 664, 414));
        pushButtonResetGraph = new QPushButton(chartView);
        pushButtonResetGraph->setObjectName(QString::fromUtf8("pushButtonResetGraph"));
        pushButtonResetGraph->setEnabled(false);
        pushButtonResetGraph->setGeometry(QRect(642, 0, 22, 22));
        QIcon icon;
        icon.addFile(QString::fromUtf8("Extra Files/cancel-circle-20.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonResetGraph->setIcon(icon);
        pushButtonResetGraph->setCheckable(false);
        tabWidgetData->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayoutWidget = new QWidget(tab_2);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 661, 420));
        layout = new QGridLayout(gridLayoutWidget);
        layout->setSpacing(6);
        layout->setContentsMargins(11, 11, 11, 11);
        layout->setObjectName(QString::fromUtf8("layout"));
        layout->setContentsMargins(0, 0, 0, 0);
        tabWidgetData->addTab(tab_2, QString());
        lineEditInformation = new QLineEdit(centralWidget);
        lineEditInformation->setObjectName(QString::fromUtf8("lineEditInformation"));
        lineEditInformation->setGeometry(QRect(410, 460, 120, 22));
        lineEditInformation->setReadOnly(true);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(340, 460, 71, 21));
        pushButtonConsole = new QPushButton(centralWidget);
        pushButtonConsole->setObjectName(QString::fromUtf8("pushButtonConsole"));
        pushButtonConsole->setGeometry(QRect(20, 460, 70, 22));
        labelLoading = new QLabel(centralWidget);
        labelLoading->setObjectName(QString::fromUtf8("labelLoading"));
        labelLoading->setEnabled(true);
        labelLoading->setGeometry(QRect(798, 449, 40, 40));
        labelLoading->setScaledContents(true);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(180, 450, 51, 21));
        spinBoxIteration = new QSpinBox(centralWidget);
        spinBoxIteration->setObjectName(QString::fromUtf8("spinBoxIteration"));
        spinBoxIteration->setGeometry(QRect(230, 450, 45, 22));
        spinBoxIteration->setReadOnly(true);
        spinBoxIteration->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBoxIteration->setProperty("showGroupSeparator", QVariant(true));
        spinBoxIteration->setMaximum(999999);
        tabWidgetNeuralNetwork = new QTabWidget(centralWidget);
        tabWidgetNeuralNetwork->setObjectName(QString::fromUtf8("tabWidgetNeuralNetwork"));
        tabWidgetNeuralNetwork->setGeometry(QRect(1, 1, 180, 440));
        tabWidgetNeuralNetwork->setTabBarAutoHide(false);
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        line = new QFrame(tab_3);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 20, 181, 41));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        labelProject = new QLabel(tab_3);
        labelProject->setObjectName(QString::fromUtf8("labelProject"));
        labelProject->setGeometry(QRect(10, 1, 60, 21));
        comboBoxData = new QComboBox(tab_3);
        comboBoxData->addItem(QString());
        comboBoxData->addItem(QString());
        comboBoxData->addItem(QString());
        comboBoxData->addItem(QString());
        comboBoxData->addItem(QString());
        comboBoxData->setObjectName(QString::fromUtf8("comboBoxData"));
        comboBoxData->setGeometry(QRect(60, 1, 111, 22));
        label_7 = new QLabel(tab_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 100, 51, 21));
        labelMax = new QLabel(tab_3);
        labelMax->setObjectName(QString::fromUtf8("labelMax"));
        labelMax->setGeometry(QRect(150, 120, 31, 16));
        QFont font;
        font.setPointSize(6);
        labelMax->setFont(font);
        label_6 = new QLabel(tab_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 60, 51, 21));
        label_1 = new QLabel(tab_3);
        label_1->setObjectName(QString::fromUtf8("label_1"));
        label_1->setGeometry(QRect(10, 140, 91, 21));
        QFont font1;
        font1.setKerning(true);
        label_1->setFont(font1);
        spinBoxCount = new QSpinBox(tab_3);
        spinBoxCount->setObjectName(QString::fromUtf8("spinBoxCount"));
        spinBoxCount->setGeometry(QRect(50, 100, 50, 22));
        spinBoxCount->setReadOnly(true);
        spinBoxCount->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBoxCount->setProperty("showGroupSeparator", QVariant(true));
        spinBoxCount->setMaximum(999999);
        spinBoxCount->setValue(0);
        spinBoxTrainingRating = new QSpinBox(tab_3);
        spinBoxTrainingRating->setObjectName(QString::fromUtf8("spinBoxTrainingRating"));
        spinBoxTrainingRating->setGeometry(QRect(115, 100, 55, 22));
        spinBoxTrainingRating->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBoxTrainingRating->setProperty("showGroupSeparator", QVariant(true));
        spinBoxTrainingRating->setMaximum(999999);
        spinBoxTrainingRating->setValue(0);
        timeEdit = new QTimeEdit(tab_3);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setGeometry(QRect(50, 60, 50, 22));
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
        label_9 = new QLabel(tab_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(105, 100, 16, 21));
        label_8 = new QLabel(tab_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 230, 111, 21));
        doubleSpinBoxCR = new QDoubleSpinBox(tab_3);
        doubleSpinBoxCR->setObjectName(QString::fromUtf8("doubleSpinBoxCR"));
        doubleSpinBoxCR->setGeometry(QRect(120, 140, 50, 22));
        doubleSpinBoxCR->setWrapping(false);
        doubleSpinBoxCR->setFrame(true);
        doubleSpinBoxCR->setReadOnly(true);
        doubleSpinBoxCR->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxCR->setDecimals(3);
        doubleSpinBoxCR->setMaximum(100.000000000000000);
        doubleSpinBoxCRM = new QDoubleSpinBox(tab_3);
        doubleSpinBoxCRM->setObjectName(QString::fromUtf8("doubleSpinBoxCRM"));
        doubleSpinBoxCRM->setGeometry(QRect(120, 230, 50, 22));
        doubleSpinBoxCRM->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxCRM->setDecimals(3);
        doubleSpinBoxCRM->setMaximum(100.000000000000000);
        doubleSpinBoxCRM->setValue(0.000000000000000);
        pushButtonEvaluate = new QPushButton(tab_3);
        pushButtonEvaluate->setObjectName(QString::fromUtf8("pushButtonEvaluate"));
        pushButtonEvaluate->setGeometry(QRect(0, 390, 70, 22));
        pushButtonLoad = new QPushButton(tab_3);
        pushButtonLoad->setObjectName(QString::fromUtf8("pushButtonLoad"));
        pushButtonLoad->setGeometry(QRect(100, 330, 70, 22));
        pushButtonSave = new QPushButton(tab_3);
        pushButtonSave->setObjectName(QString::fromUtf8("pushButtonSave"));
        pushButtonSave->setGeometry(QRect(100, 360, 70, 22));
        pushButtonReset = new QPushButton(tab_3);
        pushButtonReset->setObjectName(QString::fromUtf8("pushButtonReset"));
        pushButtonReset->setGeometry(QRect(100, 300, 70, 22));
        checkBoxAutoSave = new QCheckBox(tab_3);
        checkBoxAutoSave->setObjectName(QString::fromUtf8("checkBoxAutoSave"));
        checkBoxAutoSave->setGeometry(QRect(100, 390, 70, 22));
        label_11 = new QLabel(tab_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 170, 131, 21));
        label_12 = new QLabel(tab_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 200, 91, 21));
        doubleSpinBoxWCR = new QDoubleSpinBox(tab_3);
        doubleSpinBoxWCR->setObjectName(QString::fromUtf8("doubleSpinBoxWCR"));
        doubleSpinBoxWCR->setGeometry(QRect(120, 170, 50, 22));
        doubleSpinBoxWCR->setWrapping(false);
        doubleSpinBoxWCR->setFrame(true);
        doubleSpinBoxWCR->setReadOnly(true);
        doubleSpinBoxWCR->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxWCR->setDecimals(3);
        doubleSpinBoxWCR->setMaximum(100.000000000000000);
        doubleSpinBoxF1S = new QDoubleSpinBox(tab_3);
        doubleSpinBoxF1S->setObjectName(QString::fromUtf8("doubleSpinBoxF1S"));
        doubleSpinBoxF1S->setGeometry(QRect(120, 200, 50, 22));
        doubleSpinBoxF1S->setWrapping(false);
        doubleSpinBoxF1S->setFrame(true);
        doubleSpinBoxF1S->setReadOnly(true);
        doubleSpinBoxF1S->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBoxF1S->setDecimals(3);
        doubleSpinBoxF1S->setMaximum(100.000000000000000);
        tabWidgetNeuralNetwork->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        pushButtonRemoveLayer = new QPushButton(tab_4);
        pushButtonRemoveLayer->setObjectName(QString::fromUtf8("pushButtonRemoveLayer"));
        pushButtonRemoveLayer->setGeometry(QRect(150, 10, 22, 22));
        pushButtonRemoveLayer->setIcon(icon);
        label_2 = new QLabel(tab_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 10, 41, 21));
        spinBoxNeurons = new QSpinBox(tab_4);
        spinBoxNeurons->setObjectName(QString::fromUtf8("spinBoxNeurons"));
        spinBoxNeurons->setGeometry(QRect(60, 50, 50, 22));
        spinBoxNeurons->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinBoxNeurons->setMaximum(20000);
        spinBoxNeurons->setValue(0);
        spinBoxNeurons->setDisplayIntegerBase(10);
        comboBoxLayer = new QComboBox(tab_4);
        comboBoxLayer->addItem(QString());
        comboBoxLayer->setObjectName(QString::fromUtf8("comboBoxLayer"));
        comboBoxLayer->setGeometry(QRect(60, 10, 61, 22));
        labelNeurons = new QLabel(tab_4);
        labelNeurons->setObjectName(QString::fromUtf8("labelNeurons"));
        labelNeurons->setGeometry(QRect(10, 50, 47, 21));
        comboBoxActivationFunction = new QComboBox(tab_4);
        comboBoxActivationFunction->addItem(QString());
        comboBoxActivationFunction->addItem(QString());
        comboBoxActivationFunction->addItem(QString());
        comboBoxActivationFunction->addItem(QString());
        comboBoxActivationFunction->addItem(QString());
        comboBoxActivationFunction->setObjectName(QString::fromUtf8("comboBoxActivationFunction"));
        comboBoxActivationFunction->setGeometry(QRect(70, 90, 101, 22));
        pushButtonAddLayer = new QPushButton(tab_4);
        pushButtonAddLayer->setObjectName(QString::fromUtf8("pushButtonAddLayer"));
        pushButtonAddLayer->setGeometry(QRect(125, 10, 22, 22));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("Extra Files/add-circle-20.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonAddLayer->setIcon(icon1);
        label_4 = new QLabel(tab_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 80, 51, 31));
        spinBoxLearningRate = new QDoubleSpinBox(tab_4);
        spinBoxLearningRate->setObjectName(QString::fromUtf8("spinBoxLearningRate"));
        spinBoxLearningRate->setGeometry(QRect(90, 130, 55, 22));
        spinBoxLearningRate->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBoxLearningRate->setDecimals(6);
        spinBoxLearningRate->setMaximum(100.000000000000000);
        label_3 = new QLabel(tab_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 130, 71, 21));
        label_10 = new QLabel(tab_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 170, 71, 21));
        spinBoxMomentum = new QDoubleSpinBox(tab_4);
        spinBoxMomentum->setObjectName(QString::fromUtf8("spinBoxMomentum"));
        spinBoxMomentum->setGeometry(QRect(90, 170, 55, 22));
        spinBoxMomentum->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBoxMomentum->setDecimals(6);
        spinBoxMomentum->setMaximum(100.000000000000000);
        tabWidgetNeuralNetwork->addTab(tab_4, QString());
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabWidgetData->setCurrentIndex(0);
        tabWidgetNeuralNetwork->setCurrentIndex(0);
        comboBoxData->setCurrentIndex(2);
        comboBoxLayer->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButtonCompute->setText(QApplication::translate("MainWindow", "Compute", nullptr));
        pushButtonResetGraph->setText(QString());
        tabWidgetData->setTabText(tabWidgetData->indexOf(tab), QApplication::translate("MainWindow", "Graph of classification rate", nullptr));
        tabWidgetData->setTabText(tabWidgetData->indexOf(tab_2), QApplication::translate("MainWindow", "Data visualization", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Information :", nullptr));
        pushButtonConsole->setText(QApplication::translate("MainWindow", "Console", nullptr));
        labelLoading->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Iteration : ", nullptr));
        spinBoxIteration->setSpecialValueText(QString());
        labelProject->setText(QApplication::translate("MainWindow", "Project :", nullptr));
        comboBoxData->setItemText(0, QApplication::translate("MainWindow", "Iris", nullptr));
        comboBoxData->setItemText(1, QApplication::translate("MainWindow", "Wine", nullptr));
        comboBoxData->setItemText(2, QApplication::translate("MainWindow", "MNIST", nullptr));
        comboBoxData->setItemText(3, QApplication::translate("MainWindow", "CIFAR-10", nullptr));
        comboBoxData->setItemText(4, QApplication::translate("MainWindow", "CurrencyRates", nullptr));

        label_7->setText(QApplication::translate("MainWindow", "Count :", nullptr));
        labelMax->setText(QApplication::translate("MainWindow", "Max", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Timer :", nullptr));
        label_1->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; color:#0000ff;\">Clustering Rate :</span></p></body></html>", nullptr));
        timeEdit->setDisplayFormat(QApplication::translate("MainWindow", "HH:mm:ss", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "/", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "Clustering Rate Max : ", nullptr));
        doubleSpinBoxCR->setSpecialValueText(QString());
        doubleSpinBoxCR->setPrefix(QString());
        doubleSpinBoxCR->setSuffix(QApplication::translate("MainWindow", "%", nullptr));
        doubleSpinBoxCRM->setSpecialValueText(QString());
        doubleSpinBoxCRM->setSuffix(QApplication::translate("MainWindow", "%", nullptr));
        pushButtonEvaluate->setText(QApplication::translate("MainWindow", "Evaluate", nullptr));
        pushButtonLoad->setText(QApplication::translate("MainWindow", "Load...", nullptr));
        pushButtonSave->setText(QApplication::translate("MainWindow", "Save...", nullptr));
        pushButtonReset->setText(QApplication::translate("MainWindow", "Reset", nullptr));
        checkBoxAutoSave->setText(QApplication::translate("MainWindow", "Auto save", nullptr));
        label_11->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; color:#ff0000;\">Weighted CR :</span></p></body></html>", nullptr));
        label_12->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; color:#00ff00;\">F1 Score :</span></p></body></html>", nullptr));
        doubleSpinBoxWCR->setSpecialValueText(QString());
        doubleSpinBoxWCR->setPrefix(QString());
        doubleSpinBoxWCR->setSuffix(QApplication::translate("MainWindow", "%", nullptr));
        doubleSpinBoxF1S->setSpecialValueText(QString());
        doubleSpinBoxF1S->setPrefix(QString());
        doubleSpinBoxF1S->setSuffix(QApplication::translate("MainWindow", "%", nullptr));
        tabWidgetNeuralNetwork->setTabText(tabWidgetNeuralNetwork->indexOf(tab_3), QApplication::translate("MainWindow", "Data", nullptr));
        pushButtonRemoveLayer->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "Layer  :", nullptr));
        comboBoxLayer->setItemText(0, QApplication::translate("MainWindow", "Loading", nullptr));

        labelNeurons->setText(QApplication::translate("MainWindow", "Neurons :", nullptr));
        comboBoxActivationFunction->setItemText(0, QApplication::translate("MainWindow", "Sigmoid", nullptr));
        comboBoxActivationFunction->setItemText(1, QApplication::translate("MainWindow", "Improved Sigmoid", nullptr));
        comboBoxActivationFunction->setItemText(2, QApplication::translate("MainWindow", "TanH", nullptr));
        comboBoxActivationFunction->setItemText(3, QApplication::translate("MainWindow", "ReLU", nullptr));
        comboBoxActivationFunction->setItemText(4, QApplication::translate("MainWindow", "Gaussian", nullptr));

        pushButtonAddLayer->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "Activation\n"
"function :", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Learning rate :", nullptr));
        label_10->setText(QApplication::translate("MainWindow", "Momentum :", nullptr));
        tabWidgetNeuralNetwork->setTabText(tabWidgetNeuralNetwork->indexOf(tab_4), QApplication::translate("MainWindow", "Neural Network", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
