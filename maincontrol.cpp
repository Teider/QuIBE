#include "maincontrol.h"

quibe::MainControl::MainControl(QObject *parent) :
  QObject(parent) {

}

void quibe::MainControl::comando_esquerda() {
  emit this->message(QString("Botão esquerda clicado"));
}

void quibe::MainControl::comando_direita() {

}

void quibe::MainControl::comando_frente() {

}

void quibe::MainControl::comando_tras() {

}

void quibe::MainControl::comando_subir() {

}

void quibe::MainControl::comando_descer() {

}

void quibe::MainControl::comando_horario() {

}

void quibe::MainControl::comando_antihorario() {

}
