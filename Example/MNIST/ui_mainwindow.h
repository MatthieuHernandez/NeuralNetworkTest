/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QSpinBox *spinBoxImageId;
    QLabel *Image;
    QPushButton *pushButton;
    QLabel *labelImage;
    QComboBox *comboBoxSet;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(500, 500);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMinimumSize(QSize(0, 0));
        spinBoxImageId = new QSpinBox(centralWidget);
        spinBoxImageId->setObjectName(QStringLiteral("spinBoxImageId"));
        spinBoxImageId->setGeometry(QRect(10, 440, 81, 22));
        spinBoxImageId->setMaximum(9999);
        Image = new QLabel(centralWidget);
        Image->setObjectName(QStringLiteral("Image"));
        Image->setGeometry(QRect(100, 40, 280, 280));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(410, 440, 80, 21));
        labelImage = new QLabel(centralWidget);
        labelImage->setObjectName(QStringLiteral("labelImage"));
        labelImage->setGeometry(QRect(10, 420, 81, 16));
        comboBoxSet = new QComboBox(centralWidget);
        comboBoxSet->setObjectName(QStringLiteral("comboBoxSet"));
        comboBoxSet->setGeometry(QRect(10, 470, 81, 22));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        Image->setText(QString());
        pushButton->setText(QApplication::translate("MainWindow", "Compute", nullptr));
        labelImage->setText(QApplication::translate("MainWindow", "Label :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
