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
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MnistVisualization
{
public:
    QTextEdit *textEdit;

    void setupUi(QWidget *MnistVisualization)
    {
        if (MnistVisualization->objectName().isEmpty())
            MnistVisualization->setObjectName(QStringLiteral("MnistVisualization"));
        MnistVisualization->resize(400, 300);
        textEdit = new QTextEdit(MnistVisualization);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(-7, 0, 411, 301));

        retranslateUi(MnistVisualization);

        QMetaObject::connectSlotsByName(MnistVisualization);
    } // setupUi

    void retranslateUi(QWidget *MnistVisualization)
    {
        MnistVisualization->setWindowTitle(QApplication::translate("MnistVisualization", "MnistVisualization", nullptr));
        textEdit->setHtml(QApplication::translate("MnistVisualization", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:16pt; font-weight:600; color:#5500ff;\"><br /></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:16pt; font-weight:600; color:#5500ff;\"><br /></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empt"
                        "y; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:16pt; font-weight:600; color:#5500ff;\"><br /></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:16pt; font-weight:600; color:#5500ff;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600; color:#5500ff;\">VICTORY</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MnistVisualization: public Ui_MnistVisualization {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MNISTVISUALIZATION_H
