#include "trem.h"
#include <QtCore>

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
}

void Trem::setVelocidade(int v){
    this->velocidade  = 200 - v;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1:     //Trem A
            if (y < 170 && x == 170)
                y+=10;
            else if (x < 710 && y == 170)
                x+=10;
            else if (x == 710 && y > 50)
                y-=10;
            else
                x-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: // Trem B
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
        case 3: // Trem C
            if (y < 290 && x == 440)
                y += 10;
            else if (x < 710 && y == 290)
                x += 10;
            else if (x == 710 && y > 170)
                y -= 10;
            else
                x -= 10;
            emit updateGUI(ID, x, y);
            break;
        case 4: // Trem D
            if (y < 410 && x == 30)
                y += 10;
            else if (x < 300 && y == 410)
                x += 10;
            else if (x == 300 && y > 290)
                y -= 10;
            else
                x -= 10;
            emit updateGUI(ID, x, y);
            break;
        case 5: // Trem E
            if (y < 410 && x == 300)
                y += 10;
            else if (x < 570 && y == 410)
                x += 10;
            else if (x == 570 && y > 290)
                y -= 10;
            else
                x -= 10;
            emit updateGUI(ID, x, y);
            break;
        case 6: // Trem F
            if (y < 410 && x == 570)
                y += 10;
            else if (x < 840 && y == 410)
                x += 10;
            else if (x == 840 && y > 290)
                y -= 10;
            else
                x -= 10;
            emit updateGUI(ID, x, y);
            break;
        default:
            break;
        }
        msleep(velocidade);
    }
}




