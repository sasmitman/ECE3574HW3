#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow();
    ~MainWindow();

public slots:
    void checkValue(QString map); // After a button press

signals:
    void mapped(QString clicked);//Clicked is the QString for mapped
    void message(QString word); //For the text box

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
