#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "AES.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    std::string keys = "\x60\x3d\xeb\x10\x15\xca\x71\xbe"
                            "\x2b\x73\xae\xf0\x85\x7d\x77\x81"
                            "\x1f\x35\x2c\x07\x3b\x61\x08\xd7"
                            "\x2d\x98\x10\xa3\x09\x14\xdf\xf4";
    std::string message ="Two One Nine Two";
    Rijndael test(message, keys);
    QByteArray temp = QByteArray::fromStdString(test.getmessage());

    temp.toHex();
    ui->textBrowser->setText(temp);
}

