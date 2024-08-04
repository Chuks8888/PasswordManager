#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "AES.h"
#include "randomGenerator.h"

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
    unsigned char random[33];
    randomString(random, 32);
    std::string key;

    for(int i = 0; i < 32; i++)
    {
        std::cout << random[i];
        key += random[i];
    }
    std::cout << std::endl;

    std::string message ="Two One Nine Two";
    Rijndael test(message, key, 1);
    Rijndael please(test.getmessage(), key, 0);


    QByteArray temp = QByteArray::fromStdString(please.getmessage());
    temp.toHex();
    ui->textBrowser->setText(temp);
}

