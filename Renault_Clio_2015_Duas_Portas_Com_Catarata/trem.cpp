#include "trem.h"
#include <QtCore>

Trem::Trem(int ID, int x, int y, QMutex *mutexes){
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->velocidade = 100;
    this->mutexes = mutexes;
}

void Trem::setVelocidade(int v){
    this->velocidade = v;
}

void Trem::lockRegions(std::vector<int> regions) {
    // Ordena os mutexes para garantir aquisição hierárquica e sem deadlock
    std::sort(regions.begin(), regions.end());
    for (int r : regions) {
        if (!regionsLocked[r]) {
            mutexes[r - 1].lock();
            regionsLocked[r] = true;
        }
    }
}

void Trem::unlockRegion(int region) {
    if (regionsLocked[region]) {
        mutexes[region - 1].unlock();
        regionsLocked[region] = false;
    }
}

void Trem::run(){
    while(true){
        // Tratamento de velocidade zero
        if (velocidade == 0) {
            msleep(50);
            continue;
        }

        switch(ID){
        case 1: // Trem A (Loop Superior)
            // Bloqueia Regiões 1 e 2 antes de entrar na Região 1
            if (x == 170 && y == 160) lockRegions({1, 2});

            if (y < 170 && x == 170) y += 10;
            else if (x < 710 && y == 170) x += 10;
            else if (x == 710 && y > 50) y -= 10;
            else x -= 10;

            if (x == 450 && y == 170) unlockRegion(1);
            if (x == 710 && y == 160) unlockRegion(2);
            break;

        case 2: // Trem B (Loop Centro-Esquerdo)
            // Bloqueia Regiões 4 e 5 antes de descer para a via inferior
            if (x == 170 && y == 280) lockRegions({4, 5});
            // Bloqueia Regiões 1 e 3 ANTES de entrar no cruzamento x=440 (Região 3)
            if (x == 430 && y == 290) lockRegions({1, 3});

            if (y < 290 && x == 170) y += 10;
            else if (x < 440 && y == 290) x += 10;
            else if (x == 440 && y > 170) y -= 10;
            else x -= 10;

            if (x == 310 && y == 290) unlockRegion(4);
            if (x == 440 && y == 280) unlockRegion(5); // Saiu da via inferior
            if (x == 430 && y == 170) unlockRegion(3); // Saiu COMPLETAMENTE da Região 3
            if (x == 170 && y == 180) unlockRegion(1); // Saiu COMPLETAMENTE da Região 1
            break;

        case 3: // Trem C (Loop Centro-Direito)
            // Bloqueia Regiões 2 e 3 ANTES de entrar no topo da Região 2
            if (x == 710 && y == 180) lockRegions({2, 3});
            // Bloqueia Regiões 6 e 7 antes de chegar ao fundo do trecho vertical
            if (x == 440 && y == 280) lockRegions({6, 7});

            if (y < 290 && x == 440) y += 10;
            else if (x < 710 && y == 290) x += 10;
            else if (x == 710 && y > 170) y -= 10;
            else x -= 10;

            if (x == 440 && y == 180) unlockRegion(2); // Saiu da Região 2
            if (x == 450 && y == 290) unlockRegion(3); // Saiu COMPLETAMENTE da Região 3
            if (x == 580 && y == 290) unlockRegion(6);
            if (x == 710 && y == 280) unlockRegion(7);
            break;

        case 4: // Trem D (Loop Inferior-Esquerdo)
            if (x == 290 && y == 410) lockRegions({4, 8});

            if (y < 410 && x == 30) y += 10;
            else if (x < 300 && y == 410) x += 10;
            else if (x == 300 && y > 290) y -= 10;
            else x -= 10;

            if (x == 290 && y == 290) unlockRegion(8);
            if (x == 30 && y == 300) unlockRegion(4);
            break;

        case 5: // Trem E (Loop Inferior-Centro)
            if (x == 310 && y == 290) lockRegions({8});
            if (x == 560 && y == 410) lockRegions({5, 6, 9});

            if (y < 410 && x == 300) y += 10;
            else if (x < 570 && y == 410) x += 10;
            else if (x == 570 && y > 290) y -= 10;
            else x -= 10;

            if (x == 300 && y == 300) unlockRegion(5);
            if (x == 310 && y == 410) unlockRegion(8);
            if (x == 560 && y == 290) unlockRegion(9);
            if (x == 430 && y == 290) unlockRegion(6);
            break;

        case 6: // Trem F (Loop Inferior-Direito)
            if (x == 580 && y == 290) lockRegions({9});
            if (x == 840 && y == 300) lockRegions({7});

            if (y < 410 && x == 570) y += 10;
            else if (x < 840 && y == 410) x += 10;
            else if (x == 840 && y > 290) y -= 10;
            else x -= 10;

            if (x == 570 && y == 300) unlockRegion(7);
            if (x == 580 && y == 410) unlockRegion(9);
            break;

        default:
            break;
        }

        emit updateGUI(ID, x, y);

        int sleepTime = 200 - velocidade;
        if (sleepTime < 1) sleepTime = 1;
        msleep(sleepTime);
    }
}
