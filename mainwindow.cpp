#include "maincontrol.h"
#include "messagedialog.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(quibe::MainControl *controle, QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  this->controle = controle;

  ui->setupUi(this);

  this->setupShortcuts();
  this->setupSignals();
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::displayMessage(QString message) {
  MessageDialog *dialog = new MessageDialog(message, this);

  dialog->show();
  dialog->raise();
  dialog->activateWindow();
}

void MainWindow::setupShortcuts() {
  ui->pushButton_esquerda->setShortcut(Qt::Key_Left);
  ui->pushButton_direita->setShortcut(Qt::Key_Right);
  ui->pushButton_frente->setShortcut(Qt::Key_Up);
  ui->pushButton_tras->setShortcut(Qt::Key_Down);
  ui->pushButton_subir->setShortcut(Qt::Key_S);
  ui->pushButton_descer->setShortcut(Qt::Key_D);
  ui->pushButton_horario->setShortcut(Qt::Key_Period);
  ui->pushButton_antihorario->setShortcut(Qt::Key_Comma);
}

void MainWindow::setupSignals() {
  QObject::connect(ui->pushButton_esquerda, SIGNAL(clicked()),
                   controle, SLOT(comando_esquerda()));
  QObject::connect(ui->pushButton_direita, SIGNAL(clicked()),
                   controle, SLOT(comando_direita()));
  QObject::connect(ui->pushButton_frente, SIGNAL(clicked()),
                   controle, SLOT(comando_frente()));
  QObject::connect(ui->pushButton_tras, SIGNAL(clicked()),
                   controle, SLOT(comando_tras()));
  QObject::connect(ui->pushButton_subir, SIGNAL(clicked()),
                   controle, SLOT(comando_subir()));
  QObject::connect(ui->pushButton_descer, SIGNAL(clicked()),
                   controle, SLOT(comando_descer()));
  QObject::connect(ui->pushButton_horario, SIGNAL(clicked()),
                   controle, SLOT(comando_horario()));
  QObject::connect(ui->pushButton_antihorario, SIGNAL(clicked()),
                   controle, SLOT(comando_antihorario()));

  QObject::connect(ui->pushButton_conectar_serial, SIGNAL(clicked(bool)),
                   controle, SLOT(conectar_serial(bool)));
  QObject::connect(ui->pushButton_conectar_quadricoptero, SIGNAL(clicked(bool)),
                   controle, SLOT(conectar_quadricoptero(bool)));
  QObject::connect(ui->pushButton_decolar_pousar, SIGNAL(clicked(bool)),
                   controle, SLOT(comando_decolar_pousar(bool)));

  QObject::connect(controle, SIGNAL(serial_conectado(bool)),
                   this, SLOT(enableConectarQuadricoptero(bool)));
  QObject::connect(controle, SIGNAL(quadricoptero_conectado(bool)),
                   this, SLOT(enableDecolar(bool)));
  QObject::connect(controle, SIGNAL(decolou()), this, SLOT(enableComandos()));
  QObject::connect(controle, SIGNAL(pousou()), this, SLOT(disableComandos()));

  QObject::connect(controle, SIGNAL(message(QString)),
                   this, SLOT(displayMessage(QString)));

  QObject::connect(ui->pushButton_conectar_serial, SIGNAL(clicked(bool)),
                   this, SLOT(toggleConectarSerial(bool)));
  QObject::connect(ui->pushButton_conectar_quadricoptero, SIGNAL(clicked(bool)),
                   this, SLOT(toggleConectarQuadricoptero(bool)));
  QObject::connect(ui->pushButton_decolar_pousar, SIGNAL(clicked(bool)),
                   this, SLOT(toggleDecolar(bool)));
}

void MainWindow::enableConectarQuadricoptero(bool enable) {
  ui->pushButton_conectar_quadricoptero->setEnabled(enable);
  ui->pushButton_conectar_quadricoptero->setChecked(false);
  toggleConectarQuadricoptero(false);
  if (!enable) {
    enableDecolar(false);
  }
}

void MainWindow::enableDecolar(bool enable) {
  ui->pushButton_decolar_pousar->setEnabled(enable);
  if (!enable) {
    disableComandos();
  } else if (ui->pushButton_decolar_pousar->isChecked()) {
    enableComandos();
  }
}

void MainWindow::enableComandos() {
  ui->groupBox_comandos->setEnabled(true);
  ui->groupBox_inclinacao->setEnabled(true);
  ui->groupBox_sensores->setEnabled(true);
}

void MainWindow::disableComandos() {
  ui->groupBox_comandos->setEnabled(false);
  ui->groupBox_inclinacao->setEnabled(false);
  ui->groupBox_sensores->setEnabled(false);
}

void MainWindow::toggleConectarSerial(bool conectar) {
  if (conectar) {
    ui->pushButton_conectar_serial->setText("Desconectar Serial");
  } else {
    ui->pushButton_conectar_serial->setText("Conectar Serial");
  }
}

void MainWindow::toggleConectarQuadricoptero(bool conectar) {
  if (conectar) {
    ui->pushButton_conectar_quadricoptero->setText("Desconectar Quadricóptero");
  } else {
    ui->pushButton_conectar_quadricoptero->setText("Conectar Quadricóptero");
  }
}

void MainWindow::toggleDecolar(bool decolar) {
  if (decolar) {
    ui->pushButton_decolar_pousar->setText("Pousar");
  } else ui->pushButton_decolar_pousar->setText("Decolar");
}
