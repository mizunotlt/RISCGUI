#include "mainwindow.h"
#include <QApplication>
#include <RiscMachine.h>


int main(int argc, char *argv[])
{
    QStringList paths = QCoreApplication::libraryPaths();
        paths.append(".");
        paths.append("imageformats");
        paths.append("platforms");
        paths.append("sqldrivers");
        QCoreApplication::setLibraryPaths(paths);
    QApplication a(argc, argv);
    MainWindow w;
    w.setMinimumHeight(300);
    w.setMaximumHeight(300);
    w.setMinimumWidth(634);
    w.setMaximumWidth(634);
    w.setStyleSheet("background-color: #ccff90;");
    w.show();
    return a.exec();
}
