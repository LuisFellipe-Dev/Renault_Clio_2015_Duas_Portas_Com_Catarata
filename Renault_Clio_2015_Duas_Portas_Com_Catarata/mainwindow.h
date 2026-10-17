#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMutex>
#include <QMainWindow>
#include "trem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void updateInterface(int,int,int);

private:
    Ui::MainWindow *ui;
    QMutex mutex[9];
    //Cria os objetos TREM's
    Trem *tremA;
    Trem *tremB;
    Trem *tremC;
    Trem *tremD;
    Trem *tremE;
    Trem *tremF;
};

#endif // MAINWINDOW_H
