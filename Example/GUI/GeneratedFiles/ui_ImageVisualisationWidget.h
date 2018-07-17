/********************************************************************************
** Form generated from reading UI file 'ImageVisualisationWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEVISUALISATIONWIDGET_H
#define UI_IMAGEVISUALISATIONWIDGET_H

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

class Ui_ImageVisualisationWidget
{
public:
    QSpinBox *spinBoxImageId;
    QLabel *labelImage;
    QComboBox *comboBoxSet;
    QLabel *Image;

    void setupUi(QWidget *ImageVisualisationWidget)
    {
        if (ImageVisualisationWidget->objectName().isEmpty())
            ImageVisualisationWidget->setObjectName(QStringLiteral("ImageVisualisationWidget"));
        ImageVisualisationWidget->resize(660, 420);
        spinBoxImageId = new QSpinBox(ImageVisualisationWidget);
        spinBoxImageId->setObjectName(QStringLiteral("spinBoxImageId"));
        spinBoxImageId->setGeometry(QRect(10, 360, 80, 22));
        spinBoxImageId->setMaximum(9999);
        labelImage = new QLabel(ImageVisualisationWidget);
        labelImage->setObjectName(QStringLiteral("labelImage"));
        labelImage->setGeometry(QRect(10, 340, 80, 16));
        comboBoxSet = new QComboBox(ImageVisualisationWidget);
        comboBoxSet->addItem(QString());
        comboBoxSet->addItem(QString());
        comboBoxSet->setObjectName(QStringLiteral("comboBoxSet"));
        comboBoxSet->setGeometry(QRect(10, 390, 80, 22));
        Image = new QLabel(ImageVisualisationWidget);
        Image->setObjectName(QStringLiteral("Image"));
        Image->setGeometry(QRect(10, 10, 50, 50));
        comboBoxSet->raise();
        spinBoxImageId->raise();
        labelImage->raise();
        Image->raise();

        retranslateUi(ImageVisualisationWidget);

        QMetaObject::connectSlotsByName(ImageVisualisationWidget);
    } // setupUi

    void retranslateUi(QWidget *ImageVisualisationWidget)
    {
        ImageVisualisationWidget->setWindowTitle(QApplication::translate("ImageVisualisationWidget", "ImageVisualisationWidget", nullptr));
        labelImage->setText(QApplication::translate("ImageVisualisationWidget", "Label :", nullptr));
        comboBoxSet->setItemText(0, QApplication::translate("ImageVisualisationWidget", "Testing", nullptr));
        comboBoxSet->setItemText(1, QApplication::translate("ImageVisualisationWidget", "Training", nullptr));

        Image->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ImageVisualisationWidget: public Ui_ImageVisualisationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEVISUALISATIONWIDGET_H
