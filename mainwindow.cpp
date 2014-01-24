#include "maincontrol.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(quibe::MainControl *controle, QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  this->controle = controle;

  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::setupSignals() {
  QObject::connect(ui->pushButton_esquerda, SIGNAL(clicked()), controle,
                   SLOT(comando_esquerda()));
  QObject::connect(ui->pushButton_direita, SIGNAL(clicked()), controle,
                   SLOT(comando_direita()));
  QObject::connect(ui->pushButton_frente, SIGNAL(clicked()), controle,
                   SLOT(comando_frente()));
  QObject::connect(ui->pushButton_tras, SIGNAL(clicked()), controle,
                   SLOT(comando_tras()));
  QObject::connect(ui->pushButton_subir, SIGNAL(clicked()), controle,
                   SLOT(comando_subir()));
  QObject::connect(ui->pushButton_descer, SIGNAL(clicked()), controle,
                   SLOT(comando_descer()));
  QObject::connect(ui->pushButton_horario, SIGNAL(clicked()), controle,
                   SLOT(comando_horario()));
  QObject::connect(ui->pushButton_antihorario, SIGNAL(clicked()), controle,
                   SLOT(comando_antihorario()));
}
