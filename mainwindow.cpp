#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // check if the fil with encrypted data exists
    // in order to see if its the first entry
    firstOpen = false;
    FILE *file = fopen("data.txt", "r");
    if(file)
    {
        firstOpen = true;
        fclose(file);
    }

    if(!firstOpen)
        ui->LoginInfo->setText("First entry, please enter new KEY (Must be 32 characters)");

    // disable the drag and connect the stop signal to the slot
    ui->keyinput->setDragEnabled(0);
    //connect(this, &MainWindow::endloopsignal, &swapper, &keyswapper::endloopslot);
}

MainWindow::~MainWindow()
{
    swapper.terminate();
    delete ui;
}

// show button for the login key
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
    if(arg1.size() != 32)
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

// clears the key input and stores it in
// an always changing thread loop
void MainWindow::on_LoginButton_clicked()
{
    // clear input and start loop
    swapper.givekey((ui->keyinput->text().toStdString()));
    for(int i = 0; i < 255; i++)
        ui->keyinput->setText("clearing. . .");
    ui->keyinput->clear();
    ui->keyinput->setDisabled(1);
    swapper.start();

    // change widget
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(1));
    ui->stackedWidget->widget(0)->setDisabled(1);
}


// Signal for ending the loop and getting the key
/*void MainWindow::on_testbutton_clicked()
{
    emit endloopsignal();
}*/

