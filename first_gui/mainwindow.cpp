#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QGridLayout>
#include <QSignalMapper>
#include <QMessageBox>
#include <QTextEdit>
#include <QFile>
#include <QList>
#include <QStringList>
#include <QTextStream>
#include <QDebug>
#include <qglobal.h>

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
        emit message("Advice: "+ getFortune());
    }

    if (word == "w")
    {
        emit message("Weather: "+getWeather());
    }

    if (word == "c"){
        exit(); //Closes the MainWindow application

    }
    if (word == "d"){
        QMessageBox::information(this, "Reminder", getReminder());
        //Opens a dialog box of information type with this message: “This a reminder!”
    }
}
int MainWindow::randInt(int low, int high)
{
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
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
    QString temp;
    QList<QString> final;
    QList<QString> fortunes;
    QString path = "fortune.dat";
    QFile input(path);
    //input.open(QIODevice::ReadOnly);
    QTextStream stream(&input);
    if (!input.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug()<<"Error: Could not find file";
    }
    //File is ready for reading
    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        fortunes.append(line);
    }
    input.close();//Close the file
    for (int i = 0; i<fortunes.size(); i++)
    {
        //qDebug()<<"Entered for loop";
        temp = fortunes.at(i);
        temp = temp.trimmed();
        if (temp.endsWith("\\"))
        {
            //qDebug()<<"Entered if loop";
            while (temp.endsWith("\\"))
            {
                // qDebug()<<"Entered while loop";
                temp.remove("\\");
                temp = temp + " " +fortunes.at(i+1);
                temp = temp.trimmed();
                i++;
            }
        }
        final.append(temp);
    }
    qDebug()<<final.at(3);//Should be outputting
    return final[randInt(0,(final.size()-1))];
}

QString MainWindow::getWeather()
{
    QString temp;
    QList<QString> weather;
    QList<QString> final;
    QString path = "weather.dat";
    QFile input(path);
    QTextStream stream(&input);
    if (!input.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug()<<"Error: Could not find file";
    }
    //File is ready for reading
    while (!stream.atEnd())
    {
        QString line;
        line = stream.readLine();
        weather.append(line);
    }
    input.close();//Close the file
    for (int i = 0; i<weather.size(); i++)
    {
        temp = weather.at(i);
        temp = temp.trimmed();
        if (temp.endsWith("\\"))
        {
            //qDebug()<<"Entered if loop";
            while (temp.endsWith("\\"))
            {
                // qDebug()<<"Entered while loop";
                temp.remove("\\");
                temp = temp + " " +weather.at(i+1);
                temp = temp.trimmed();
                i++;
            }
        }
        final.append(temp);
    }
    //qDebug()<<final.at(3);//Should be outputting
    return final[randInt(0,(final.size()-1))];
}

QString MainWindow::getReminder()
{
    QString temp;
    QList<QString> reminder;
    QList<QString> final;
    QString path = "reminder.dat";
    QFile input(path);
    QTextStream stream(&input);
    if (!input.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug()<<"Error: Could not find file";
    }
    //File is ready for reading
    while (!stream.atEnd())
    {
        QString line;
        line = stream.readLine();
        reminder.append(line);
    }
    input.close();//Close the file
    for (int i = 0; i<reminder.size(); i++)
    {
        temp = reminder.at(i);
        temp = temp.trimmed();
        if (temp.endsWith("\\"))
        {
            //qDebug()<<"Entered if loop";
            while (temp.endsWith("\\"))
            {
                // qDebug()<<"Entered while loop";
                temp.remove("\\");
                temp = temp + " " +reminder.at(i+1);
                temp = temp.trimmed();
                i++;
            }
        }
        final.append(temp);
    }
    //qDebug()<<final.at(3);//Should be outputting
    return final[randInt(0,(final.size()-1))];
}

