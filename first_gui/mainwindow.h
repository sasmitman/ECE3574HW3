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
    void exit();

public slots:
    void checkValue(QString map); // After a button press

signals:
    void mapped(QString clicked);//Clicked is the QString for mapped
    void message(QString word); //For the text box

private:
    Ui::MainWindow *ui;
    QString getFortune();
    QString getWeather();
    QString getReminder();
};

#endif // MAINWINDOW_H
