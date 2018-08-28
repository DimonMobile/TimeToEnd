#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("Big Black Duck");
    a.setApplicationName("Time to end");
    a.setApplicationDisplayName("Waiting for end");
    MainWindow w;
    w.show();

    return a.exec();
}
