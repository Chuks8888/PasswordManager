#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    //return a.exec();
    try {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    }
    catch (const std::exception &e) {
        QMessageBox::critical(nullptr, "Critical Error", e.what());  // Displays error message if an exception is caught
        return -1;  // Return an error code
    }
    catch (...) {
        QMessageBox::critical(nullptr, "Critical Error", "An unknown error occurred.");  // Catches non-standard exceptions
        return -1;  // Return an error code
    }
}
