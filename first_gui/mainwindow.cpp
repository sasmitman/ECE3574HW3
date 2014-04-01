#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QGridLayout>
#include <QSignalMapper>
#include <QMessageBox>
#include <QTextEdit>
#include <QFile>
#include <QList>
#include <QTextStream>
#include <cstdlib>

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

    QPushButton* adviseBtn = new QPushButton("Advise");
    myLayout->addWidget(adviseBtn);

    QPushButton* weatherBtn = new QPushButton("Weather");
    myLayout->addWidget(weatherBtn);

    QPushButton* reminderBtn = new QPushButton("Reminder");
    myLayout->addWidget(reminderBtn);

    QPushButton* closeBtn = new QPushButton("Quit");
    myLayout->addWidget(closeBtn);

    //Mapping the signal to a slot map(). The parent of mySignal is QMainWindow object
    QSignalMapper *mySignal = new QSignalMapper(this);

    connect(adviseBtn, SIGNAL(clicked()), mySignal, SLOT(map()));//Signal for when advise is pressed
    mySignal->setMapping(adviseBtn, "a");

    connect(weatherBtn, SIGNAL(clicked()), mySignal, SLOT(map()));
    mySignal->setMapping(weatherBtn, "w");

    connect(reminderBtn, SIGNAL(clicked()), mySignal, SLOT(map()));//Signal for when reminder is pressed
    mySignal->setMapping(reminderBtn, "d");

    connect(closeBtn, SIGNAL(clicked()), mySignal, SLOT(map()));//Signal for when the close button is pressed
    mySignal->setMapping(closeBtn, "c");

    //Mapping mapped(const QString &s) to checkValue(QString) slot
    connect(mySignal, SIGNAL(mapped(QString)), this, SLOT(checkValue(QString))); //For all the buttons
    connect(this, SIGNAL(message(QString)), myTextEdit, SLOT(append(QString))); //For the text box
}

void MainWindow::checkValue (QString word)
{
    if (word == "a")
    {
        emit message(getFortune());
    }

    if (word == "w")
    {
        emit message(QString("Weather:"));
    }

    if (word == "c"){
        exit(); //Closes the MainWindow application

    }
    if (word == "d"){
        QMessageBox::information(this, "Reminder", "This is a reminder!");
        //Opens a dialog box of information type with this message: “This a reminder!”
    }
}

void MainWindow::exit()
{
    QMessageBox::StandardButton popup;
    popup = QMessageBox::question(this, "", "Are you sure you want to quit the program?", QMessageBox::Yes|QMessageBox::No);
    if (popup == QMessageBox::Yes)
    {
        qApp->quit();
    }
}

QString MainWindow::getFortune()
{
    int n = 0;//Count of how many lines
    QList<QString> fortunes;
    QString path = "fortune.dat";
    QFile input(path);
    input.open(QIODevice::ReadOnly);
    QTextStream stream(&input);
    //File is ready for reading
    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        fortunes.append(line);
        n = n+1;
    }
    input.close();//Close the file

    return fortunes[rand()*n];
}
