/********************************************************************************
** Form generated from reading UI file 'Cifar10Visualization.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CIFAR10VISUALIZATION_H
#define UI_CIFAR10VISUALIZATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Cifar10Visualization
{
public:
    QLabel *labelImage_2;
    QLabel *Image_2;
    QSpinBox *spinBoxImageId_2;
    QComboBox *comboBoxSet_2;

    void setupUi(QWidget *Cifar10Visualization)
    {
        if (Cifar10Visualization->objectName().isEmpty())
            Cifar10Visualization->setObjectName(QStringLiteral("Cifar10Visualization"));
        Cifar10Visualization->resize(660, 420);
        labelImage_2 = new QLabel(Cifar10Visualization);
        labelImage_2->setObjectName(QStringLiteral("labelImage_2"));
        labelImage_2->setGeometry(QRect(10, 330, 80, 16));
        Image_2 = new QLabel(Cifar10Visualization);
        Image_2->setObjectName(QStringLiteral("Image_2"));
        Image_2->setGeometry(QRect(10, 10, 320, 320));
        spinBoxImageId_2 = new QSpinBox(Cifar10Visualization);
        spinBoxImageId_2->setObjectName(QStringLiteral("spinBoxImageId_2"));
        spinBoxImageId_2->setGeometry(QRect(10, 350, 80, 22));
        spinBoxImageId_2->setMaximum(9999);
        comboBoxSet_2 = new QComboBox(Cifar10Visualization);
        comboBoxSet_2->addItem(QString());
        comboBoxSet_2->addItem(QString());
        comboBoxSet_2->setObjectName(QStringLiteral("comboBoxSet_2"));
        comboBoxSet_2->setGeometry(QRect(10, 380, 80, 22));

        retranslateUi(Cifar10Visualization);

        QMetaObject::connectSlotsByName(Cifar10Visualization);
    } // setupUi

    void retranslateUi(QWidget *Cifar10Visualization)
    {
        Cifar10Visualization->setWindowTitle(QApplication::translate("Cifar10Visualization", "Cifar10Visualization", nullptr));
        labelImage_2->setText(QApplication::translate("Cifar10Visualization", "Label :", nullptr));
        Image_2->setText(QString());
        comboBoxSet_2->setItemText(0, QApplication::translate("Cifar10Visualization", "Testing", nullptr));
        comboBoxSet_2->setItemText(1, QApplication::translate("Cifar10Visualization", "Training", nullptr));

    } // retranslateUi

};

namespace Ui {
    class Cifar10Visualization: public Ui_Cifar10Visualization {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CIFAR10VISUALIZATION_H
