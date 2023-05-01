#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QIcon>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QIcon appIcon("/app_logo.png");

    MainWindow window;

    window.show();
    a.setWindowIcon(appIcon);
    return a.exec();
}
