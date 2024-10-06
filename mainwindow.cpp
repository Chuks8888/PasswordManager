#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // check if the fil with encrypted data exists
    // in order to see if its the first entry
    firstOpen = false;
    FILE *file = fopen("data.txt", "r");
    if(!file)
        firstOpen = true;
    else
        fclose(file);

    if(firstOpen)
    {
        ui->LoginInfo->setText("First entry, please enter new KEY (Must be 32 characters)");
        ui->getpass->setEnabled(0);
    }
    // disable the drag and connect the stop signal to the slot
    ui->keyinput->setDragEnabled(0);
    //connect(this, &MainWindow::endloopsignal, &swapper, &keyswapper::endloopslot);
}

MainWindow::~MainWindow()
{
    swapper.terminate();
    delete ui;
}

void MainWindow::on_createpass_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(2));
}

void MainWindow::on_showpass_toggled(bool checked)
{
    auto& temp = ui->passwordinput;
    if(temp->echoMode() == temp->Password)
        temp->setEchoMode(temp->Normal);
    else
        temp->setEchoMode(temp->Password);
}

void MainWindow::checkForAllParameters()
{
    ui->submitbutton->setEnabled(0);

    if(!ui->domaininput->text().isEmpty())
        if(!ui->passwordinput->text().isEmpty())
            if(!ui->usernameinput->text().isEmpty())
                ui->submitbutton->setEnabled(1);
}

void MainWindow::on_domaininput_textEdited(const QString &arg1)
{
    checkForAllParameters();
}
void MainWindow::on_usernameinput_textEdited(const QString &arg1)
{
    checkForAllParameters();
}

void MainWindow::on_passwordinput_textEdited()
{
    checkForAllParameters();
}

void MainWindow::on_pushButton_clicked()
{
    ui->domaininput->clear();
    ui->usernameinput->clear();
    ui->passwordinput->clear();
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(1));
}

