#include "../mainwindow.h"

void MainWindow::setupLayout()
{
    std::ifstream domains("data.txt");
    std::string buffer;

    // ignore the hash and get domain name
    domains.ignore(256, '\n');
    getline(domains, buffer);

    while(!domains.eof())
    {
        addDomain(QString::fromStdString(buffer));
        domains.ignore(64, '\n');
        domains.ignore(64, '\n');
        getline(domains, buffer);
    }
    domains.close();
}

void MainWindow::addDomain(QString temp)
{
    static int index = 0;

    QPushButton* button = new QPushButton(temp, ui->stackedWidget->widget(2));
    connect(button, &QPushButton::clicked, this, &MainWindow::dynamicButtonClicked);
    layout.insertWidget(index, button);
    index++;
}

void MainWindow::on_backbutton2_clicked()
{
    if(ui->stackedWidget->widget(1))
        ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(1));
}

void MainWindow::dynamicButtonClicked()
{
    QPushButton* temp = qobject_cast<QPushButton*>(sender());
    win.setWindowTitle(temp->text());
    win.exec();
}
