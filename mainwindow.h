#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Keyholder/keyswapper.h"
#include "./ui_mainwindow.h"

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

    // Login screen Slots ////////////////////////////
    void on_ShowKey_toggled(bool checked);

    void on_keyinput_textEdited(const QString &arg1);

    void on_keyinput_returnPressed();

    void on_LoginButton_clicked();
    /////////////////////////////////////////////////
    void on_createpass_clicked();

    void on_showpass_toggled(bool checked);

    void checkForAllParameters();

    void on_domaininput_textEdited(const QString &arg1);

    void on_usernameinput_textEdited(const QString &arg1);

    void on_passwordinput_textEdited();

    void on_pushButton_clicked();

private:

    bool firstOpen;
    Ui::MainWindow *ui;
    keyswapper swapper;

    void giveAwayKey();
};
#endif // MAINWINDOW_H
