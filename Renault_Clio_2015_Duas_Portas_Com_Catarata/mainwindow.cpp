#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Cria o trem com seu (ID, posição X, posição Y)
    tremA = new Trem(1,170,50, mutex);
    tremB = new Trem(2,170,170, mutex);
    tremC = new Trem(3,440,170, mutex);
    tremD = new Trem(4,30,290, mutex);
    tremE = new Trem(5,300,290, mutex);
    tremF = new Trem(6,570,290, mutex);

    /*
     * Conecta o sinal UPDATEGUI à função UPDATEINTERFACE.
     * Ou seja, sempre que o sinal UPDATEGUI foi chamado, será executada a função UPDATEINTERFACE.
     * Os 3 parâmetros INT do sinal serão utilizados na função.
     * Trem1 e Trem2 são os objetos que podem chamar o sinal. Se um outro objeto chamar o
     * sinal UPDATEGUI, não haverá execução da função UPDATEINTERFACE
     */
    connect(tremA,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(tremB,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(tremC,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(tremD,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(tremE,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(tremF,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));

    connect(ui->horizontalSliderA, &QSlider::valueChanged, this, [this](int v){
       tremA->setVelocidade(v);

    });
    connect(ui->horizontalSliderB, &QSlider::valueChanged, this, [this](int v){
      tremB->setVelocidade(v);
    });
    connect(ui->horizontalSliderC, &QSlider::valueChanged, this, [this](int v){
        tremC->setVelocidade(v);
    });
    connect(ui->horizontalSliderD, &QSlider::valueChanged, this, [this](int v){
      tremD->setVelocidade(v);

    });
    connect(ui->horizontalSliderE, &QSlider::valueChanged, this, [this](int v){
      tremE->setVelocidade(v);

    });
    connect(ui->horizontalSliderF, &QSlider::valueChanged, this, [this](int v){
      tremF->setVelocidade(v);
    });

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

//Função que será executada quando o sinal UPDATEGUI for emitido
void MainWindow::updateInterface(int id, int x, int y){
    switch(id){
    case 1: //Atualiza a posição do objeto da tela (quadrado) que representa o trem1
        ui->label_tremA->setGeometry(x,y,21,17);
        break;
    case 2: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_tremB->setGeometry(x,y,21,17);
        break;
    case 3:
        ui->label_tremC->setGeometry(x,y,21,17);
        break;
    case 4:
        ui->label_tremD->setGeometry(x,y,21,17);
        break;
    case 5:
        ui->label_tremE->setGeometry(x,y,21,17);
        break;
    case 6:
        ui->label_tremF->setGeometry(x,y,21,17);
        break;
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
