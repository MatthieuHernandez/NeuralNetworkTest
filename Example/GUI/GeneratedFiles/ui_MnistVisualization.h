/********************************************************************************
** Form generated from reading UI file 'MnistVisualization.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MNISTVISUALIZATION_H
#define UI_MNISTVISUALIZATION_H

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

class Ui_MnistVisualization
{
public:
    QLabel *labelImage;
    QSpinBox *spinBoxImageId;
    QLabel *Image;
    QComboBox *comboBoxSet;

    void setupUi(QWidget *MnistVisualization)
    {
        if (MnistVisualization->objectName().isEmpty())
            MnistVisualization->setObjectName(QStringLiteral("MnistVisualization"));
        MnistVisualization->resize(660, 420);
        labelImage = new QLabel(MnistVisualization);
        labelImage->setObjectName(QStringLiteral("labelImage"));
        labelImage->setGeometry(QRect(10, 330, 80, 16));
        spinBoxImageId = new QSpinBox(MnistVisualization);
        spinBoxImageId->setObjectName(QStringLiteral("spinBoxImageId"));
        spinBoxImageId->setGeometry(QRect(10, 350, 80, 22));
        spinBoxImageId->setMaximum(9999);
        Image = new QLabel(MnistVisualization);
        Image->setObjectName(QStringLiteral("Image"));
        Image->setGeometry(QRect(10, 10, 300, 300));
        comboBoxSet = new QComboBox(MnistVisualization);
        comboBoxSet->addItem(QString());
        comboBoxSet->addItem(QString());
        comboBoxSet->setObjectName(QStringLiteral("comboBoxSet"));
        comboBoxSet->setGeometry(QRect(10, 380, 80, 22));

        retranslateUi(MnistVisualization);

        QMetaObject::connectSlotsByName(MnistVisualization);
    } // setupUi

    void retranslateUi(QWidget *MnistVisualization)
    {
        MnistVisualization->setWindowTitle(QApplication::translate("MnistVisualization", "MnistVisualization", nullptr));
        labelImage->setText(QApplication::translate("MnistVisualization", "Label :", nullptr));
        Image->setText(QString());
        comboBoxSet->setItemText(0, QApplication::translate("MnistVisualization", "Testing", nullptr));
        comboBoxSet->setItemText(1, QApplication::translate("MnistVisualization", "Training", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MnistVisualization: public Ui_MnistVisualization {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MNISTVISUALIZATION_H
