#include "Console.h"

Console::Console(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->hide();
}

Console::~Console()
{
}

void Console::write(const std::string text)
{
	ui.textEdit->append(QString::fromStdString(text));
} 
