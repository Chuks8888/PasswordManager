#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //layout = new QVBoxLayout(ui->stackedWidget->widget(2));
    ui->scrollAreaWidgetContents->setLayout(&layout);
    layout.addStretch();

    // check if the file with encrypted data exists
    // in order to see if its the first entry
    firstOpen = false;
    FILE *file = fopen("data.txt", "r");
    if(!file)
        firstOpen = true;
    else
        fclose(file);

    if(firstOpen)
        ui->LoginInfo->setText("First entry, please enter new KEY (Must be 32 characters)");
    else
        setupLayout();

    // disable the drag and connect the stop signal to the slot
    ui->keyinput->setDragEnabled(0);

    // Signal to end swapping loop
    connect(this, &MainWindow::signalLoop, &swapper, &keyswapper::endloopslot);

    // Signal to copy one of the parametes (password or username)
    connect(&win, &copyWindow::signalForCopy, this, &MainWindow::askForCopy);
}

MainWindow::~MainWindow()
{
    swapper.terminate();
    delete ui;
}

void MainWindow::on_createpass_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(3));
}

void MainWindow::on_getpass_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(2));
}



void MainWindow::askForCopy(bool choice)
{
    // Function that save the encrypted text to the clipboard
}

