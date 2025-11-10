#include "Headers/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Smart Music Playlist Generator");
    w.resize(1200, 700);
    w.show();
    return a.exec();
}
