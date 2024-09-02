#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "AES.h"
#include "randomGenerator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Message Line edit
    auto& Message = ui->message;
    Message->setPlaceholderText("message");

    // Key input line edit
    auto& Key = ui->keyInput;
    Key->setPlaceholderText("key");
    Key->setMaxLength(32);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //unsigned char random[33];
    //randomString(random, 32);

    if(ui->message->text() == "" || ui->keyInput->text() == "")
    {
        std::cout << "Missing parameters" << std::endl;
        return;
    }

    std::string key = ui->keyInput->text().toStdString();
    std::string message = ui->message->text().toStdString();

    std::cout << "Key: " << key << std::endl;
    std::cout << "Message: " << message << std::endl;

    Rijndael encode(message, key, 1);
    Rijndael decode(encode.getmessage(), key, 0);

    QByteArray temp = QByteArray::fromStdString(decode.getmessage());
    temp.toHex();
    ui->textBrowser->setText(temp);
}

