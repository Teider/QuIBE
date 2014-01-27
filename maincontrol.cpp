#include "maincontrol.h"

#include <QDebug>

quibe::MainControl::MainControl(QObject *parent) :
  QObject(parent) {
  velocidade = 50;

}

void quibe::MainControl::comando_esquerda() {
  qDebug() << "Comando: Esquerda" << endl;
}

void quibe::MainControl::comando_direita() {
  qDebug() << "Comando: Direita" << endl;
}

void quibe::MainControl::comando_frente() {
  qDebug() << "Comando: Frente" << endl;
}

void quibe::MainControl::comando_tras() {
  qDebug() << "Comando: Tras" << endl;
}

void quibe::MainControl::comando_subir() {
  qDebug() << "Comando: Subir" << endl;
}

void quibe::MainControl::comando_descer() {
  qDebug() << "Comando: Descer" << endl;
}

void quibe::MainControl::comando_horario() {
  qDebug() << "Comando: Girar Sentido Horário" << endl;
}

void quibe::MainControl::comando_antihorario() {
  qDebug() << "Comando: Girar Sentido Anti-Horário" << endl;
}

void quibe::MainControl::comando_parar() {
  qDebug() << "Comando: Parar" << endl;
}

void quibe::MainControl::conectar_serial(bool conectar) {
  emit serial_conectado(conectar);
}

void quibe::MainControl::conectar_quadricoptero(bool conectar) {
  emit quadricoptero_conectado(conectar);
}

void quibe::MainControl::comando_decolar_pousar(bool decolar) {
  if (decolar) {
    emit decolou();
  } else emit pousou();
}

void quibe::MainControl::velocidade_alterada(int velocidade) {
  this->velocidade = velocidade;
  qDebug() << "Velocidade alterada para: " << velocidade << "\%" << endl;
}
