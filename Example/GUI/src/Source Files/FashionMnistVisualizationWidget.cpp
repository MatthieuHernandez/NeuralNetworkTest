#include "FashionMnistVisualizationWidget.h"
#include "ui_FashionMnistVisualization.h"
#include <ui_ImageVisualizationWidget.h>

FashionMnistVisualizationWidget::FashionMnistVisualizationWidget(QWidget* parent, Controller* controller)
    : ImageVisualizationWidget(parent, controller), ui(new Ui::FashionMnistVisualization)
{
    ui->setupUi(this);
    this->controller = controller;
    ImageVisualizationWidget::ui->Image->resize(280, 280);
    this->displayImage(0);
}

unsigned char FashionMnistVisualizationWidget::getPixel(int number, int x, int y, color) const
{
    return static_cast<unsigned char>((this->controller->getDataset().data->getData(displayedSet, number)[y * 28 + x] + 1.0) * 127.4);
}