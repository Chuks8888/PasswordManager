#include "copywindow.h"
#include "iostream"

copyWindow::copyWindow()
{
    resize(350, 100);

    this->setLayout(&winLayout);

    pass.setText("copy password");
    winLayout.insertWidget(0, &pass);

    user.setText("copy username");
    winLayout.insertWidget(1, &user);

    connect(&pass, &QPushButton::clicked, this, &copyWindow::passClicked);
    connect(&user, &QPushButton::clicked, this, &copyWindow::userClicked);
}

copyWindow::~copyWindow()
{
    std::cerr << "deleting pop-up window object" << std::endl;
}

void copyWindow::passClicked()
{
    emit signalForCopy(1, this->windowTitle().toStdString());
}

void copyWindow::userClicked()
{
    emit signalForCopy(0, this->windowTitle().toStdString());
}
