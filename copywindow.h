#ifndef COPYWINDOW_H
#define COPYWINDOW_H

#include <qboxlayout.h>
#include <qdialog.h>
#include <qpushbutton.h>

class copyWindow : public QDialog
{
    Q_OBJECT
public:
    copyWindow();
    ~copyWindow();
private:
    QVBoxLayout winLayout;
    QPushButton pass;
    QPushButton user;
signals:
    void signalForCopy(bool);
private slots:
    void passClicked();
    void userClicked();
};

#endif // COPYWINDOW_H
