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
    connect(this, &MainWindow::signalLoop, &swapper, &keyswapper::endloopslot);
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
