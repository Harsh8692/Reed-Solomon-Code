#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;

    QIcon icon(":/img/images.ico");
    mainWindow.setWindowIcon(icon);

    mainWindow.setStyleSheet("background-color: #cecece; color: black;");
    mainWindow.show();
    return app.exec();
}
