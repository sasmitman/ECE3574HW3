#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QGridLayout>
#include <QSignalMapper>
#include <QMessageBox>
#include <QTextEdit>

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::MainWindow()
{
    //central widget stores all other widgets
    QWidget *myCentralWidget = new QWidget();
    setCentralWidget (myCentralWidget);

    // When myLayout is put under myCentralWidget, it automatically becomes its child.
    QVBoxLayout *myLayout = new QVBoxLayout;
    myCentralWidget->setLayout (myLayout);

    QTextEdit *myTextEdit = new QTextEdit("Welcome to this program");
    myLayout->addWidget(myTextEdit);

    QPushButton* closeBtn = new QPushButton("Close");
    myLayout->addWidget(closeBtn);

    QPushButton* dialogBtn = new QPushButton("Open Dialog Box!");
    myLayout->addWidget(dialogBtn);

    //Mapping the signal to a slot map(). The parent of mySignal is QMainWindow object
    QSignalMapper *mySignal = new QSignalMapper(this);
    connect(closeBtn, SIGNAL(clicked()), mySignal, SLOT(map()));
    mySignal->setMapping(closeBtn, "c");
    connect(dialogBtn, SIGNAL(clicked()), mySignal, SLOT(map()));
    mySignal->setMapping(dialogBtn, "d");

    //Mapping mapped(const QString &s) to checkValue(QString) slot
    connect(mySignal, SIGNAL(mapped(QString)), this, SLOT(checkValue(QString))); //For all the buttons
    connect(this, SIGNAL(message(QString)), myTextEdit, SLOT(append(QString))); //For the text box
}

void MainWindow::checkValue (QString word)
{
    if (word == "c"){
        qApp->quit (); //Closes the MainWindow application Applied Software Design, Spring 2014

    }
    if (word == "d"){
        QMessageBox::information(this, "Information", "This is a dialog box!");
        //Opens a dialog box of information type with this message: “This a dialog box!”
    }
}
