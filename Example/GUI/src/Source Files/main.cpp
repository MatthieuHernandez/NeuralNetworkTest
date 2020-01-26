#define _HAS_STD_BYTE 0
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
int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	int argc = 0;
    QApplication a(argc, {});
    MainWindow w;
    w.show();

    return a.exec();
}