#include "mainwindow.h"
#include "AES.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    std::string message ="";
    message += 0xdb;
    message += 0x13;
    message += 0x53;
    message += 0x45;
    message += 0xf2;
    message += 0x0a;
    message += 0x22;
    message += 0x5c;

    Rijndael test(message, "ILOVESTARWARS<3!");
    //test.testMixColumns();
    //test.testShiftRows();
    test.printBlocks();

    return a.exec();
}
