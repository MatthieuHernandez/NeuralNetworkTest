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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MnistVisualization
{
public:
    QLabel *label;

    void setupUi(QWidget *MnistVisualization)
    {
        if (MnistVisualization->objectName().isEmpty())
            MnistVisualization->setObjectName(QStringLiteral("MnistVisualization"));
        MnistVisualization->resize(660, 420);
        label = new QLabel(MnistVisualization);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(340, 10, 310, 130));
        label->setTextFormat(Qt::AutoText);
        label->setScaledContents(false);
        label->setWordWrap(true);
        label->setOpenExternalLinks(false);

        retranslateUi(MnistVisualization);

        QMetaObject::connectSlotsByName(MnistVisualization);
    } // setupUi

    void retranslateUi(QWidget *MnistVisualization)
    {
        MnistVisualization->setWindowTitle(QApplication::translate("MnistVisualization", "MnistVisualization", nullptr));
        label->setText(QApplication::translate("MnistVisualization", "<html><body><p align=\"justify\">The MNIST database of handwritten digits, available from this page, has a training set of 60,000 examples, and a test set of 10,000 examples. It is a subset of a larger set available from NIST. The digits have been size-normalized and centered in a fixed-size image.</p><p align=\"justify\">It is a good database for people who want to try learning techniques and pattern recognition methods on real-world data while spending minimal efforts on preprocessing and formatting.</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MnistVisualization: public Ui_MnistVisualization {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MNISTVISUALIZATION_H
