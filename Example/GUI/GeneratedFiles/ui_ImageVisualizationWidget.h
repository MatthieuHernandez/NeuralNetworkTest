/********************************************************************************
** Form generated from reading UI file 'ImageVisualizationWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEVISUALIZATIONWIDGET_H
#define UI_IMAGEVISUALIZATIONWIDGET_H

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

class Ui_ImageVisualizationWidget
{
public:
    QSpinBox *spinBoxImageId;
    QLabel *labelImage;
    QComboBox *comboBoxSet;
    QLabel *Image;

    void setupUi(QWidget *ImageVisualizationWidget)
    {
        if (ImageVisualizationWidget->objectName().isEmpty())
            ImageVisualizationWidget->setObjectName(QStringLiteral("ImageVisualizationWidget"));
        ImageVisualizationWidget->resize(660, 420);
        spinBoxImageId = new QSpinBox(ImageVisualizationWidget);
        spinBoxImageId->setObjectName(QStringLiteral("spinBoxImageId"));
        spinBoxImageId->setGeometry(QRect(10, 360, 80, 22));
        spinBoxImageId->setMaximum(9999);
        labelImage = new QLabel(ImageVisualizationWidget);
        labelImage->setObjectName(QStringLiteral("labelImage"));
        labelImage->setGeometry(QRect(10, 340, 80, 16));
        comboBoxSet = new QComboBox(ImageVisualizationWidget);
        comboBoxSet->addItem(QString());
        comboBoxSet->addItem(QString());
        comboBoxSet->setObjectName(QStringLiteral("comboBoxSet"));
        comboBoxSet->setGeometry(QRect(10, 390, 80, 22));
        Image = new QLabel(ImageVisualizationWidget);
        Image->setObjectName(QStringLiteral("Image"));
        Image->setGeometry(QRect(10, 10, 50, 50));
        comboBoxSet->raise();
        spinBoxImageId->raise();
        labelImage->raise();
        Image->raise();

        retranslateUi(ImageVisualizationWidget);

        QMetaObject::connectSlotsByName(ImageVisualizationWidget);
    } // setupUi

    void retranslateUi(QWidget *ImageVisualizationWidget)
    {
        ImageVisualizationWidget->setWindowTitle(QApplication::translate("ImageVisualizationWidget", "ImageVisualizationWidget", nullptr));
        labelImage->setText(QApplication::translate("ImageVisualizationWidget", "Label :", nullptr));
        comboBoxSet->setItemText(0, QApplication::translate("ImageVisualizationWidget", "Testing", nullptr));
        comboBoxSet->setItemText(1, QApplication::translate("ImageVisualizationWidget", "Training", nullptr));

        Image->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ImageVisualizationWidget: public Ui_ImageVisualizationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEVISUALIZATIONWIDGET_H
