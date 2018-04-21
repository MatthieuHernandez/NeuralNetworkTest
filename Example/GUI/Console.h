#pragma once

#include <QWidget>
#include "ui_Console.h"

class Console : public QWidget
{
	Q_OBJECT

public:
	Console(QWidget *parent = Q_NULLPTR);
	~Console();

private:
	Ui::Console ui;
};
