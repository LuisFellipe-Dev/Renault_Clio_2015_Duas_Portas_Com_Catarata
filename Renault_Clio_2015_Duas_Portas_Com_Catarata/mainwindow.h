#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMutex>
#include "trem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void updateInterface(int id, int x, int y);

private:
    Ui::MainWindow *ui;

    QMutex mutexes[9];

    Trem *tremA;
    Trem *tremB;
    Trem *tremC;
    Trem *tremD;
    Trem *tremE;
    Trem *tremF;
};

#endif // MAINWINDOW_H
