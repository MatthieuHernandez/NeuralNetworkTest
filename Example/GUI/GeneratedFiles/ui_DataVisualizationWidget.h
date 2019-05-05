/********************************************************************************
** Form generated from reading UI file 'DataVisualizationWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAVISUALIZATIONWIDGET_H
#define UI_DATAVISUALIZATIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataVisualizationWidget
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label_5;
    QLabel *labelName;
    QLabel *label;
    QLabel *labelDataSize;
    QLabel *label_2;
    QLabel *labelNumberOfLabel;
    QLabel *label_3;
    QLabel *label_10;
    QLabel *labelTestingSetSize;
    QLabel *label_12;
    QLabel *labelTrainingSetSize;
    QFrame *line;
    QFrame *line_2;

    void setupUi(QWidget *DataVisualizationWidget)
    {
        if (DataVisualizationWidget->objectName().isEmpty())
            DataVisualizationWidget->setObjectName(QString::fromUtf8("DataVisualizationWidget"));
        DataVisualizationWidget->resize(660, 420);
        formLayoutWidget = new QWidget(DataVisualizationWidget);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(340, 220, 198, 111));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        formLayout->setRowWrapPolicy(QFormLayout::DontWrapRows);
        formLayout->setHorizontalSpacing(6);
        formLayout->setVerticalSpacing(6);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(formLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_5);

        labelName = new QLabel(formLayoutWidget);
        labelName->setObjectName(QString::fromUtf8("labelName"));

        formLayout->setWidget(0, QFormLayout::FieldRole, labelName);

        label = new QLabel(formLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        labelDataSize = new QLabel(formLayoutWidget);
        labelDataSize->setObjectName(QString::fromUtf8("labelDataSize"));

        formLayout->setWidget(1, QFormLayout::FieldRole, labelDataSize);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        labelNumberOfLabel = new QLabel(formLayoutWidget);
        labelNumberOfLabel->setObjectName(QString::fromUtf8("labelNumberOfLabel"));

        formLayout->setWidget(2, QFormLayout::FieldRole, labelNumberOfLabel);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        label_10 = new QLabel(formLayoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_10);

        labelTestingSetSize = new QLabel(formLayoutWidget);
        labelTestingSetSize->setObjectName(QString::fromUtf8("labelTestingSetSize"));

        formLayout->setWidget(4, QFormLayout::FieldRole, labelTestingSetSize);

        label_12 = new QLabel(formLayoutWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        formLayout->setWidget(5, QFormLayout::FieldRole, label_12);

        labelTrainingSetSize = new QLabel(formLayoutWidget);
        labelTrainingSetSize->setObjectName(QString::fromUtf8("labelTrainingSetSize"));

        formLayout->setWidget(3, QFormLayout::FieldRole, labelTrainingSetSize);

        line = new QFrame(DataVisualizationWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(320, 0, 20, 420));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(DataVisualizationWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(330, 200, 330, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        retranslateUi(DataVisualizationWidget);

        QMetaObject::connectSlotsByName(DataVisualizationWidget);
    } // setupUi

    void retranslateUi(QWidget *DataVisualizationWidget)
    {
        DataVisualizationWidget->setWindowTitle(QApplication::translate("DataVisualizationWidget", "DataVisualizationWidget", nullptr));
        label_5->setText(QApplication::translate("DataVisualizationWidget", "Name of Data Set : ", nullptr));
        labelName->setText(QString());
        label->setText(QApplication::translate("DataVisualizationWidget", "Size of Data :", nullptr));
        labelDataSize->setText(QString());
        label_2->setText(QApplication::translate("DataVisualizationWidget", "Number of Label :", nullptr));
        labelNumberOfLabel->setText(QString());
        label_3->setText(QApplication::translate("DataVisualizationWidget", "Size of Trainig Set :", nullptr));
        label_10->setText(QApplication::translate("DataVisualizationWidget", "Size of Testing Set :", nullptr));
        labelTestingSetSize->setText(QString());
        label_12->setText(QString());
        labelTrainingSetSize->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DataVisualizationWidget: public Ui_DataVisualizationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAVISUALIZATIONWIDGET_H
