#ifndef TREM_H
#define TREM_H

#include <QThread>
#include <QMutex>
#include <vector>
#include <algorithm>

class Trem: public QThread{
    Q_OBJECT
public:
    Trem(int ID, int x, int y, QMutex *mutexes);
    void run() override;
    void setVelocidade(int v);

signals:
    void updateGUI(int id, int x, int y);

private:
    int x;
    int y;
    int ID;
    int velocidade;
    QMutex *mutexes;
    bool regionsLocked[10] = {false};

    void lockRegions(std::vector<int> regions);
    void unlockRegion(int region);
};

#endif // TREM_H
