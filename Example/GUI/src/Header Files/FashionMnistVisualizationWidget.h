#pragma once
#include "Controller.h"
#include "ImageVisualizationWidget.h"

namespace Ui
{
    class FashionMnistVisualization;
};

class FashionMnistVisualizationWidget : public ImageVisualizationWidget
{
Q_OBJECT

public:
    FashionMnistVisualizationWidget(QWidget* parent, Controller* controller);
    ~FashionMnistVisualizationWidget() = default;

private:
    Ui::FashionMnistVisualization* ui;
    unsigned char getPixel(int number, int x, int y, color color) const override;
};
