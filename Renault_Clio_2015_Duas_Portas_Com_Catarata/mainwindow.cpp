#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tremA = new Trem(1,170,50,mutexes);
    tremB = new Trem(2,170,170,mutexes);
    tremC = new Trem(3,440,170,mutexes);
    tremD = new Trem(4,30,290,mutexes);
    tremE = new Trem(5,300,290,mutexes);
    tremF = new Trem(6,570,290,mutexes);

    connect(tremA,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(tremB,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(tremC,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(tremD,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(tremE,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(tremF,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));

    connect(ui->horizontalSliderA, &QSlider::valueChanged, this, [this](int v){ tremA->setVelocidade(v); });
    connect(ui->horizontalSliderB, &QSlider::valueChanged, this, [this](int v){ tremB->setVelocidade(v); });
    connect(ui->horizontalSliderC, &QSlider::valueChanged, this, [this](int v){ tremC->setVelocidade(v); });
    connect(ui->horizontalSliderD, &QSlider::valueChanged, this, [this](int v){ tremD->setVelocidade(v); });
    connect(ui->horizontalSliderE, &QSlider::valueChanged, this, [this](int v){ tremE->setVelocidade(v); });
    connect(ui->horizontalSliderF, &QSlider::valueChanged, this, [this](int v){ tremF->setVelocidade(v); });

    // Controle Mestre: atualiza a velocidade geral e alinha a interface gráfica
    connect(ui->horizontalSliderM, &QSlider::valueChanged, this, [this](int v){
        ui->horizontalSliderA->setValue(v);
        ui->horizontalSliderB->setValue(v);
        ui->horizontalSliderC->setValue(v);
        ui->horizontalSliderD->setValue(v);
        ui->horizontalSliderE->setValue(v);
        ui->horizontalSliderF->setValue(v);
    });

    tremA->start();
    tremB->start();
    tremC->start();
    tremD->start();
    tremE->start();
    tremF->start();
}

void MainWindow::updateInterface(int id, int x, int y){
    switch(id){
    case 1: ui->label_tremA->setGeometry(x,y,21,17); break;
    case 2: ui->label_tremB->setGeometry(x,y,21,17); break;
    case 3: ui->label_tremC->setGeometry(x,y,21,17); break;
    case 4: ui->label_tremD->setGeometry(x,y,21,17); break;
    case 5: ui->label_tremE->setGeometry(x,y,21,17); break;
    case 6: ui->label_tremF->setGeometry(x,y,21,17); break;
    default: break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
