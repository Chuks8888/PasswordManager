#include "copywindow.h"

copyWindow::copyWindow()
{
    resize(350, 100);

    // set the vertical layout
    this->setLayout(&winLayout);

    // create the buttons
    pass.setText("copy password");
    winLayout.insertWidget(0, &pass);

    user.setText("copy username");
    winLayout.insertWidget(1, &user);

    connect(&pass, &QPushButton::clicked, this, &copyWindow::passClicked);
    connect(&user, &QPushButton::clicked, this, &copyWindow::userClicked);
}

copyWindow::~copyWindow()
{
    //std::cerr << "deleting pop-up window object" << std::endl;
}

void copyWindow::passClicked()
{
    // signal the copying process
    emit signalForCopy(1, this->windowTitle().toStdString());
}

void copyWindow::userClicked()
{
    // signal the copying process
    emit signalForCopy(0, this->windowTitle().toStdString());
}
