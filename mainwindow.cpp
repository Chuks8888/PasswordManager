#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "randomGenerator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    firstOpen = false;
    FILE *file = fopen("data.txt", "r");
    if(file)
    {
        firstOpen = true;
        fclose(file);
    }

    if(!firstOpen)
        ui->LoginInfo->setText("First entry, please enter new KEY (Max 32 characters)");

    ui->keyinput->setDragEnabled(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ShowKey_toggled(bool checked)
{
    auto& temp = ui->keyinput;
    if(temp->echoMode() == temp->Password)
        temp->setEchoMode(temp->Normal);
    else
        temp->setEchoMode(temp->Password);
}

void MainWindow::on_keyinput_textEdited(const QString &arg1)
{
    if(arg1.isEmpty())
        ui->LoginButton->setEnabled(0);
    else
    {
        if(ui->LoginButton->isEnabled())
            return;
        else
            ui->LoginButton->setEnabled(1);
    }
}


void MainWindow::on_keyinput_returnPressed()
{
    emit ui->LoginButton->clicked(true);
}


void MainWindow::on_LoginButton_clicked()
{
    //
}

