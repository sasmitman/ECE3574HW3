#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QGridLayout>

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

 QPushButton* closeBtn = new QPushButton("Close");
 myLayout->addWidget(closeBtn);

 QPushButton* dialogBtn = new QPushButton("Open Dialog Box!");
 myLayout->addWidget(dialogBtn);
}

