#include "maincontrol.h"
#include "messagedialog.h"

#include <QKeyEvent>

#include <QSerialPortInfo>
#include <serialconfig.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(quibe::MainControl *controle, QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  noAr = false;

  this->controle = controle;

  ui->setupUi(this);

  this->setupSignals();
  foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
    ui->comboBox_porta->addItem(info.portName());
  }
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

void MainWindow::setupSignals() {
  QObject::connect(ui->pushButton_esquerda, SIGNAL(pressed()),
                   controle, SLOT(comando_esquerda()));
  QObject::connect(ui->pushButton_direita, SIGNAL(pressed()),
                   controle, SLOT(comando_direita()));
  QObject::connect(ui->pushButton_frente, SIGNAL(pressed()),
                   controle, SLOT(comando_frente()));
  QObject::connect(ui->pushButton_tras, SIGNAL(pressed()),
                   controle, SLOT(comando_tras()));
  QObject::connect(ui->pushButton_subir, SIGNAL(pressed()),
                   controle, SLOT(comando_subir()));
  QObject::connect(ui->pushButton_descer, SIGNAL(pressed()),
                   controle, SLOT(comando_descer()));
  QObject::connect(ui->pushButton_horario, SIGNAL(pressed()),
                   controle, SLOT(comando_horario()));
  QObject::connect(ui->pushButton_antihorario, SIGNAL(pressed()),
                   controle, SLOT(comando_antihorario()));

  QObject::connect(ui->pushButton_esquerda, SIGNAL(released()),
                   controle, SLOT(comando_parar()));
  QObject::connect(ui->pushButton_direita, SIGNAL(released()),
                   controle, SLOT(comando_parar()));
  QObject::connect(ui->pushButton_frente, SIGNAL(released()),
                   controle, SLOT(comando_parar()));
  QObject::connect(ui->pushButton_tras, SIGNAL(released()),
                   controle, SLOT(comando_parar()));
  QObject::connect(ui->pushButton_subir, SIGNAL(released()),
                   controle, SLOT(comando_parar()));
  QObject::connect(ui->pushButton_descer, SIGNAL(released()),
                   controle, SLOT(comando_parar()));
  QObject::connect(ui->pushButton_horario, SIGNAL(released()),
                   controle, SLOT(comando_parar()));
  QObject::connect(ui->pushButton_antihorario, SIGNAL(released()),
                   controle, SLOT(comando_parar()));

  QObject::connect(ui->pushButton_conectar_quadricoptero, SIGNAL(clicked(bool)),
                   controle, SLOT(conectar_quadricoptero(bool)));
  QObject::connect(ui->pushButton_decolar_pousar, SIGNAL(clicked(bool)),
                   controle, SLOT(comando_decolar_pousar(bool)));

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

  QObject::connect(ui->verticalSlider_velocidade, SIGNAL(valueChanged(int)),
                   this, SLOT(mudarVelocidade(int)));
  QObject::connect(ui->lineEdit_velocidade, SIGNAL(textEdited(QString)),
                   this, SLOT(mudarVelocidade(QString)));
  QObject::connect(this, SIGNAL(velocidade_alterada(int)),
                   controle, SLOT(velocidade_alterada(int)));

  QObject::connect(controle, SIGNAL(serial_conectado(bool)),
                   this, SLOT(serialConectado(bool)));
  QObject::connect(controle, SIGNAL(serial_desconectado()),
                   this, SLOT(serialDesconectado()));
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
  noAr = true;
}

void MainWindow::disableComandos() {
  ui->groupBox_comandos->setEnabled(false);
  ui->groupBox_inclinacao->setEnabled(false);
  ui->groupBox_sensores->setEnabled(false);
  noAr = false;
}

void MainWindow::toggleConectarSerial(bool conectar) {
  quibe::SerialConfig config;
  config.portName = ui->comboBox_porta->currentText();
  config.setBaudRate(ui->comboBox_baud_rate->currentText());
  config.setDataBits(ui->comboBox_bits->currentText());
  config.setParity(ui->comboBox_paridade->currentText());
  config.setStopBits(ui->comboBox_stop_bits->currentText());
  config.flowControl = QSerialPort::NoFlowControl;
  if (conectar) {
    ui->pushButton_conectar_serial->setText("Conectando...");
    controle->conectar_serial(true, config);
  } else {
    ui->pushButton_conectar_serial->setText("Conectar Serial");
    controle->conectar_serial(false, config);
  }
}

void MainWindow::serialConectado(bool conectado) {
  if (conectado) {
    ui->pushButton_conectar_serial->setText("Desconectar Serial");
    ui->pushButton_conectar_quadricoptero->setEnabled(true);
  } else {
    displayMessage("Não foi possível conectar à porta serial");
    ui->pushButton_conectar_serial->setText("Conectar Serial");
    ui->pushButton_conectar_serial->toggled(false);
  }
}

void MainWindow::serialDesconectado() {
  ui->pushButton_conectar_serial->setText("Conectar Serial");
  ui->pushButton_conectar_serial->toggled(false);
  ui->pushButton_conectar_quadricoptero->setEnabled(false);
  ui->pushButton_conectar_quadricoptero->toggled(false);
  toggleConectarQuadricoptero(false);
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

void MainWindow::mudarVelocidade(int nova_velocidade) {
  if (nova_velocidade > 100) nova_velocidade = 100;
  if (nova_velocidade < 10) nova_velocidade = 10;
  if (nova_velocidade % 10) nova_velocidade -= (nova_velocidade % 10);
  int aux = ui->lineEdit_velocidade->text().toInt();
  if (aux != nova_velocidade) {
    ui->lineEdit_velocidade->setText(QString::number(nova_velocidade));
    emit velocidade_alterada(nova_velocidade);
  }
}

void MainWindow::mudarVelocidade(QString nova_velocidade) {
  int aux = nova_velocidade.toInt();
  if (aux > 100) aux = 100;
  if (aux < 10) aux = 10;
  if (aux % 10) aux -= (aux % 10);
  if (ui->verticalSlider_velocidade->value() != aux) {
    ui->verticalSlider_velocidade->setValue(aux);
    emit velocidade_alterada(aux);
  }
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
  if (noAr && !e->isAutoRepeat()) {
    switch (e->key()) {
    case Qt::Key_Left:
      emit ui->pushButton_esquerda->pressed();
      ui->pushButton_esquerda->setDown(true);
      setFocus();
    break;
    case Qt::Key_Right:
      emit ui->pushButton_direita->pressed();
      ui->pushButton_direita->setDown(true);
      setFocus();
    break;
    case Qt::Key_Up:
      emit ui->pushButton_frente->pressed();
      ui->pushButton_frente->setDown(true);
      setFocus();
    break;
    case Qt::Key_Down:
      emit ui->pushButton_tras->pressed();
      ui->pushButton_tras->setDown(true);
      setFocus();
    break;
    case Qt::Key_S:
      emit ui->pushButton_subir->pressed();
      ui->pushButton_subir->setDown(true);
      setFocus();
    break;
    case Qt::Key_D:
      emit ui->pushButton_descer->pressed();
      ui->pushButton_descer->setDown(true);
      setFocus();
    break;
    case Qt::Key_Period:
      emit ui->pushButton_horario->pressed();
      ui->pushButton_horario->setDown(true);
      setFocus();
    break;
    case Qt::Key_Comma:
      emit ui->pushButton_antihorario->pressed();
      ui->pushButton_antihorario->setDown(true);
      setFocus();
    break;
    default:
    break;
    }
  }
}

void MainWindow::keyReleaseEvent(QKeyEvent *e) {
  if (noAr && !e->isAutoRepeat()) {
    switch (e->key()) {
    case Qt::Key_Left:
      emit ui->pushButton_esquerda->released();
      ui->pushButton_esquerda->setDown(false);
      setFocus();
    break;
    case Qt::Key_Right:
      emit ui->pushButton_direita->released();
      ui->pushButton_direita->setDown(false);
      setFocus();
    break;
    case Qt::Key_Up:
      emit ui->pushButton_frente->released();
      ui->pushButton_frente->setDown(false);
      setFocus();
    break;
    case Qt::Key_Down:
      emit ui->pushButton_tras->released();
      ui->pushButton_tras->setDown(false);
      setFocus();
    break;
    case Qt::Key_S:
      emit ui->pushButton_subir->released();
      ui->pushButton_subir->setDown(false);
      setFocus();
    break;
    case Qt::Key_D:
      emit ui->pushButton_descer->released();
      ui->pushButton_descer->setDown(false);
      setFocus();
    break;
    case Qt::Key_Period:
      emit ui->pushButton_horario->released();
      ui->pushButton_horario->setDown(false);
      setFocus();
    break;
    case Qt::Key_Comma:
      emit ui->pushButton_antihorario->released();
      ui->pushButton_antihorario->setDown(false);
      setFocus();
    break;
    default:
    break;
    }
  }
}
