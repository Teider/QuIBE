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

  QObject::connect(controle, SIGNAL(message(QString)), this,
                   SLOT(displayMessage(QString)));
}
