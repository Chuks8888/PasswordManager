#include "mainwindow.h"
#include "AES.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    std::string keys = "Thats my Kung Fu";
    std::string message ="Two One Nine Two";
    Rijndael test(message, keys);
    test.printBlocks();
    test.encrypt();
    test.printBlocks();

    return a.exec();
}
