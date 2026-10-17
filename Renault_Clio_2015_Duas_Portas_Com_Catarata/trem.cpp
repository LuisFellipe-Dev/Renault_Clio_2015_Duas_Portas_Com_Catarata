#include "trem.h"
#include <QtCore>

//Construtor
Trem::Trem(int ID, int x, int y, QMutex *mutexes){
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->mutex = mutexes;
    this->velocidade = 100;
    this->primeiroPasso = true;
}

void Trem::setVelocidade(int v){
    if (v == 0) {
        this->velocidade = 0;
    } else {
        this->velocidade = 201 - v;
    }
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        if (velocidade > 0) {
            switch(ID){
            case 1:
                if (x ==170 && y ==160) {
                    mutex[0].lock();
                }
                if (x==430 && y==170) {
                    mutex[1].lock();
                    mutex[0].unlock();
                }
                if (x == 700 && y==170) {
                    mutex[1].unlock();
                }

                if (y < 170 && x == 170)
                    y+=10;
                else if (x < 710 && y == 170)
                    x+=10;
                else if (x == 710 && y > 50)
                    y-=10;
                else
                    x-=10;
                emit updateGUI(ID, x, y);
                break;

            case 2:
                if (x==170 && y==280) {
                    mutex[3].lock();
                }
                if (x==290 && y==290) {
                    mutex[4].lock();
                    mutex[3].unlock();
                }
                if (x==430 && y==290) {
                    mutex[2].lock();
                    mutex[4].unlock();
                }
                if (x==440 && y==180) {
                    mutex[0].lock();
                    mutex[2].unlock();
                }
                if (x == 180 && y==170) {
                    mutex[0].unlock();
                }

                if (y < 290 && x == 170)
                    y += 10;
                else if (x < 440 && y == 290)
                    x += 10;
                else if (x == 440 && y > 170)
                    y -= 10;
                else
                    x -= 10;
                emit updateGUI(ID, x, y);
                break;

            case 3:
                if (primeiroPasso){
                    mutex[2].lock();
                    primeiroPasso = false;
                }
                if (x==440 && y==280){
                    mutex[5].lock();
                    mutex[2].unlock();
                }
                if (x==560 && y==290){
                    mutex[6].lock();
                    mutex[5].unlock();
                }
                if (x==700 && y==290){
                    mutex[6].unlock();
                }
                if (x==710 && y==180){
                    mutex[1].lock();
                }
                if (x==450  && y==170){
                    mutex[2].lock();
                    mutex[1].unlock();
                }

                if (y < 290 && x == 440)
                    y += 10;
                else if (x < 710 && y == 290)
                    x += 10;
                else if (x == 710 && y > 170)
                    y -= 10;
                else
                    x -= 10;
                emit updateGUI(ID,x,y);
                break;

            case 4:
                if (x==290 && y==410){
                    mutex[7].lock();
                }
                if (x==300 && y==300){
                    mutex[3].lock();
                   mutex[7].unlock();
                }
                if (x==160 && y==290){
                    mutex[3].unlock();
                }

                if (y < 410 && x == 30)
                    y += 10;
                else if (x < 300 && y == 410)
                    x += 10;
                else if (x == 300 && y > 290)
                    y -= 10;
                else
                    x -= 10;
                emit updateGUI(ID,x,y);
                break;

            case 5:     // Trem E
                if (primeiroPasso) {
                    mutex[7].lock();
                    primeiroPasso = false;
                }
                if (x ==560 && y ==410){
                    mutex[8].lock();
                    mutex[7].unlock();
                }
                if (x==570 && y==300){
                    mutex[5].lock();
                    mutex[8].unlock();
                }
                if (x==450 && y==290){
                    mutex[4].lock();
                    mutex[5].unlock();
                }
                if (x==310 && y==290){
                    mutex[7].lock();
                    mutex[4].unlock();
                }

                if (y<410 && x==300)
                    y += 10;
                else if (x < 570 && y == 410)
                    x += 10;
                else if (x == 570 && y > 290)
                    y -= 10;
                else
                    x -= 10;
                emit updateGUI(ID, x, y);
                break;

            case 6:
                if (primeiroPasso) {
                    mutex[8].lock();
                    primeiroPasso = false;
                }
                if (x==580 && y==410){
                    mutex[8].unlock();
                }
                if (x==720 && y==290){
                    mutex[6].lock();
                }
                if (x==580 && y==290){
                    mutex[8].lock();
                    mutex[6].unlock();
                }

                if (y < 410 && x == 570)
                    y += 10;
                else if (x < 840 && y == 410)
                    x += 10;
                else if (x==840 && y>290)
                    y -= 10;
                else
                    x -= 10;
                emit updateGUI(ID,x,y);
                break;

            default:
                break;
            }
            msleep(velocidade);
        } else {
            msleep(100);
        }
    }
}
