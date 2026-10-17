#ifndef TREM_H
#define TREM_H

#include <QThread>
#include <QMutex>

class Trem: public QThread{
    Q_OBJECT
public:
    Trem(int ID, int x, int y, QMutex *mutexes);
    void run();
    void setVelocidade(int v);

signals:
    void updateGUI(int, int, int);

private:
    int x;
    int y;
    int ID;
    int velocidade;
    QMutex *mutex;
    bool primeiroPasso; // Garante a reserva da região no arranque do programa
};

#endif // TREM_H
