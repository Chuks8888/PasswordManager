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

void MainWindow::askForCopy(bool choice, std::string domain)
{
    // Function that save the encrypted text to the clipboard
    std::ifstream data("data.txt");
    std::string buffer;

    data.ignore(256, '\n');
    getline(data, buffer);

    while(!data.eof())
    {
        if(!buffer.compare(domain))
        {
            if(choice)
                data.ignore(64, '\n');

            getline(data, buffer);
            QByteArray temp = QByteArray::fromHex(QByteArray::fromStdString(buffer));

            buffer = temp.toStdString();
            temp.clear();

            // tell the keyswapping loop to stop
            emit signalLoop();
            if(!swapper.isFinished())
                swapper.wait();

            // ask for encryption and start the swapper again
            swapper.sendtext(buffer, 0);
            swapper.start();
            while(!swapper.isRunning()){
                //std::cerr << 0 << std::endl;
            };

            std::cerr << buffer << std::endl;
            break;
        }
        data.ignore(64, '\n');
        data.ignore(64, '\n');
        getline(data, buffer);
    }

    data.close();
}

