#ifndef COPYWINDOW_H
#define COPYWINDOW_H

#include <qboxlayout.h>
#include <qdialog.h>
#include <qpushbutton.h>

/* This class is a QDialog that popsup
 * when the user tries to acces their password
 * or username
 * in this small window the user has the option
 * to copy both the data above to their clipboard
*/
class copyWindow : public QDialog
{
    Q_OBJECT
public:
    copyWindow();
    ~copyWindow();
private:
    // the layout and the buttons on the window
    QVBoxLayout winLayout;
    QPushButton pass;
    QPushButton user;
signals:
    // this is the signals the method in MainWindow
    // that one of the button was pressed
    void signalForCopy(bool);
private slots:
    void passClicked();
    void userClicked();
};

#endif // COPYWINDOW_H
