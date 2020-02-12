/********************************************************************************
** Form generated from reading UI file 'Cifar10Visualization.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CIFAR10VISUALIZATION_H
#define UI_CIFAR10VISUALIZATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Cifar10Visualization
{
public:

    void setupUi(QWidget *Cifar10Visualization)
    {
        if (Cifar10Visualization->objectName().isEmpty())
            Cifar10Visualization->setObjectName(QString::fromUtf8("Cifar10Visualization"));
        Cifar10Visualization->resize(660, 420);

        retranslateUi(Cifar10Visualization);

        QMetaObject::connectSlotsByName(Cifar10Visualization);
    } // setupUi

    void retranslateUi(QWidget *Cifar10Visualization)
    {
        Cifar10Visualization->setWindowTitle(QCoreApplication::translate("Cifar10Visualization", "Cifar10Visualization", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Cifar10Visualization: public Ui_Cifar10Visualization {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CIFAR10VISUALIZATION_H
