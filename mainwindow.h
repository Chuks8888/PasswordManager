#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "AES.h"
#include "keyswapper.h"

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

signals:
    void endloopsignal();

private slots:

    void on_ShowKey_toggled(bool checked);

    void on_keyinput_textEdited(const QString &arg1);

    void on_keyinput_returnPressed();

    void on_LoginButton_clicked();

private:

    bool firstOpen;
    Ui::MainWindow *ui;
    keyswapper swapper;

    void giveAwayKey();
};
#endif // MAINWINDOW_H
