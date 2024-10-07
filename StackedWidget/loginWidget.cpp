#include "../mainwindow.h"

// show button for the login key
void MainWindow::on_ShowKey_toggled(bool checked)
{
    auto& temp = ui->keyinput;
    if(temp->echoMode() == temp->Password)
        temp->setEchoMode(temp->Normal);
    else
        temp->setEchoMode(temp->Password);
}


// enables the button only if there are 32 characters in the key input line
void MainWindow::on_keyinput_textEdited(const QString &arg1)
{
    if(arg1.size() != 32)
        ui->LoginButton->setEnabled(0);
    else
        ui->LoginButton->setEnabled(1);
}

// if enter is pressed go throug with the logging in
void MainWindow::on_keyinput_returnPressed()
{
    emit ui->LoginButton->clicked(true);
}

// Checks if the key is correct and then it
// clears the key input and stores it in
// an always changing thread loop
void MainWindow::on_LoginButton_clicked()
{
    // Firstly we distribute the input and clear it
    QByteArray keyhash = ui->keyinput->text().toUtf8();
    swapper.givekey((ui->keyinput->text().toStdString()));

    for(int i = 0; i < 255; i++)
        ui->keyinput->setText("clearing. . .");
    ui->keyinput->clear();

    // Then check if the input is correct by using the hash in the file
    QCryptographicHash hashing(QCryptographicHash::Sha256);

    hashing.addData(keyhash);
    keyhash = hashing.result();

    std::string input_hash = keyhash.toHex().toStdString();

    // if there was no file (due to first time use)
    // we create the file and fill it with our hash
    if(firstOpen)
    {
        std::ofstream file("data.txt");
        file << input_hash << std::endl;
        file.close();
    }
    else
    {
        //input_hash += "\n";

        // open the file and get the hash and then compare it
        std::ifstream file("data.txt");

        if(!file.is_open())
            exit(1);

        std::string file_hash;
        std::getline(file, file_hash);

        if(file_hash.compare(input_hash) != 0)
        {
            ui->LoginInfo->setText("Invalid Key !");
            file.close();
            return;
        }
        file.close();
    }

    // if the input was correct we disable the widget and start the key encryping thread
    ui->keyinput->setDisabled(1);

    ////////////////////////////
    // Swapper is turned on ///
    ///////////////////////////
    swapper.start();///////////
    ///////////////////////////

    // change widget
    ui->stackedWidget->setCurrentWidget(ui->stackedWidget->widget(1));
    ui->stackedWidget->widget(0)->setDisabled(1);
}
