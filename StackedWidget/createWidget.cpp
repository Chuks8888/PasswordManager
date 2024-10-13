#include "../mainwindow.h"

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

void MainWindow::on_submitbutton_clicked()
{
    // Firstly we check if the domain is unique
    std::ifstream file("data.txt");


    std::string buffer;
    file.ignore(256, '\n');
    getline(file, buffer);

    while(!file.eof())
    {
        // compare domain names
        if(!buffer.compare(ui->domaininput->text().toStdString()))
        {
            ui->domaininput->clear();
            file.close();
            // std::cerr << "Repeating domain" << std::endl;
            return;
        }
        file.ignore(64, '\n');
        file.ignore(64, '\n');
        getline(file, buffer);
    }
    file.close();

    // now we save the data on the file
    std::ofstream save("data.txt", std::ios::app);

    // save domain name
    save << ui->domaininput->text().toStdString() << std::endl;
    addDomain(ui->domaininput->text());

    // get username and password
    std::string temp = ui->usernameinput->text().toStdString();
    std::string temp2 = ui->passwordinput->text().toStdString();

    // tell the keyswapping loop to stop
    emit signalLoop();
    if(!swapper.isFinished())
        swapper.wait();

    // ask for encryption and start the swapper again
    swapper.sendtext(temp, 1);
    swapper.sendtext(temp2, 1);
    swapper.start();
    while(!swapper.isRunning()){};

    // turn it to hex and save to file
    QByteArray user = QByteArray::fromStdString(temp);
    temp = "";
    save <<  user.toHex().toStdString() << std::endl;
    user.clear();

    QByteArray pass = QByteArray::fromStdString(temp2);
    temp2 = "";
    save <<  pass.toHex().toStdString() << std::endl;
    pass.clear();

    // close the file and go back
    save.close();
    on_gobackbutton_clicked();
}

void MainWindow::on_gobackbutton_clicked()
{
    ui->domaininput->clear();
    ui->usernameinput->clear();
    ui->passwordinput->clear();
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(1));
}
