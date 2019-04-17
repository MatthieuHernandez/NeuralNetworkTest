#include "mainwindow.h"

/* DEBUG */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

/*RELEASE */
int WinMain(HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPSTR     lpCmdLine,
  int       nShowCmd)
{
	int argc = 0;

    QApplication a(argc, {});
    MainWindow w;
    w.show();

    return a.exec();
}