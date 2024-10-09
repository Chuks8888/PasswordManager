#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Keyholder/keyswapper.h"
#include "./ui_mainwindow.h"
#include "copywindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_ShowKey_toggled(bool checked);

    void on_keyinput_textEdited(const QString &arg1);

    void on_keyinput_returnPressed();

    void on_LoginButton_clicked();

    void on_createpass_clicked();

    void on_showpass_toggled(bool checked);

    void checkForAllParameters();

    void on_domaininput_textEdited(const QString &arg1);

    void on_usernameinput_textEdited(const QString &arg1);

    void on_passwordinput_textEdited();

    void on_submitbutton_clicked();

    void on_gobackbutton_clicked();

    void on_getpass_clicked();

    void on_backbutton2_clicked();

    void dynamicButtonClicked();

    void askForCopy(bool choice, std::string);

signals:
    // signal to stop the keyswapper
    void signalLoop();

private:
    // Boolean that checks for the frist use of app
    bool firstOpen;

    Ui::MainWindow *ui;
    // Qthread that keeps the key and encryps/decrypts data
    keyswapper swapper;

    // Layout for the scroll area when the user
    // tries to copy their passwords
    QVBoxLayout layout;
    void setupLayout();

    // Function for adding a button to the layout
    void addDomain(QString temp);

    // Function for passing the key from the input to ther swapper qthread
    void giveAwayKey();

    // Pop up window where the user copies the password and/or username
    copyWindow win;
};
#endif // MAINWINDOW_H
