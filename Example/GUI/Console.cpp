#include "Console.h"

using namespace std;

Console::Console(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

Console::~Console()
{
}

void Console::write(const string text)
{
	ui.textEdit->append(QString::fromStdString(text));
}
