#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    try {

        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    }
    catch (const std::exception &e) {
        QMessageBox::critical(nullptr, "Critical Error", e.what());
        return -1;
    }
    catch (...) {
        QMessageBox::critical(nullptr, "Critical Error", "An unknown error occurred.");
        return -1;
    }
}
