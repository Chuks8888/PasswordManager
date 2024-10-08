#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    layout = new QVBoxLayout(ui->stackedWidget->widget(2));
    if(layout != NULL)
    {
        ui->scrollAreaWidgetContents->setLayout(layout);
        layout->addStretch();
    }
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
        //ui->getpass->setEnabled(0);
    }
    else
    {
        std::ifstream domains("data.txt");
        std::string buffer;

        // first getline is to skip the hash
        getline(domains, buffer);
        getline(domains, buffer);

        int index = 0;
        int i = 3;
        while(!domains.eof())
        {
            if(i == 3)
            {
                QPushButton* button = new QPushButton(QString::fromStdString(buffer), ui->stackedWidget->widget(2));
                layout->insertWidget(index, button);
                connect(button, &QPushButton::clicked, this, &MainWindow::dynamicButtonClicked);
                index++;
                i=0;
            }
            getline(domains, buffer);
            i++;
        }
        domains.close();
    }
    // disable the drag and connect the stop signal to the slot
    ui->keyinput->setDragEnabled(0);
    connect(this, &MainWindow::signalLoop, &swapper, &keyswapper::endloopslot);

    connect(&win, &copyWindow::signalForCopy, this, &MainWindow::askForCopy);
}

MainWindow::~MainWindow()
{
    swapper.terminate();
    delete ui;
}

void MainWindow::addDomain(QString temp)
{
    QPushButton* button = new QPushButton(temp, ui->stackedWidget->widget(2));
    connect(button, &QPushButton::clicked, this, &MainWindow::dynamicButtonClicked);
    layout->addWidget(button);
}

void MainWindow::on_createpass_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(3));
}

void MainWindow::on_getpass_clicked()
{
    if(layout != NULL)
        ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(2));
}

void MainWindow::on_backbutton2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(1));
}

void MainWindow::dynamicButtonClicked()
{
    QPushButton* temp = qobject_cast<QPushButton*>(sender());
    std::cerr << temp->text().toStdString() << std::endl;
    win.setWindowTitle(temp->text());
    win.exec();
}

void MainWindow::askForCopy(bool choice)
{
    // Function that save the encrypted text to the clipboard
}

