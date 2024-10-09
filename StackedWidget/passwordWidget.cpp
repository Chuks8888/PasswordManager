#include "../mainwindow.h"

void MainWindow::setupLayout()
{
    std::ifstream domains("data.txt");
    std::string buffer;

    // first getline is to skip the hash
    getline(domains, buffer);
    getline(domains, buffer);

    int i = 4;
    while(!domains.eof())
    {
        if(i & 4)
        {
            addDomain(QString::fromStdString(buffer));
            i = 1;
        }
        getline(domains, buffer);
        i++;
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
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(1));
}

void MainWindow::dynamicButtonClicked()
{
    QPushButton* temp = qobject_cast<QPushButton*>(sender());
    std::cerr << temp->text().toStdString() << std::endl;
    win.setWindowTitle(temp->text());
    win.exec();
}
