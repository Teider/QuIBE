#include "maincontrol.h"

#include <QThread>
#include <QDebug>

quibe::MainControl::MainControl(QObject *parent) :
  QObject(parent) {
  velocidade = 50;

  QObject::connect(&serial, SIGNAL(mensagemLida(QByteArray)),
                   this, SLOT(parse_message(QByteArray)));
}

void quibe::MainControl::comando_esquerda() {
  serial.enviaComandoMovimento(ComunicacaoSerial::ESQUERDA, velocidade/10);
  qDebug() << "Comando: Esquerda" << endl;
}

void quibe::MainControl::comando_direita() {
  serial.enviaComandoMovimento(ComunicacaoSerial::DIREITA, velocidade/10);
  qDebug() << "Comando: Direita" << endl;
}

void quibe::MainControl::comando_frente() {
  serial.enviaComandoMovimento(ComunicacaoSerial::FRENTE, velocidade/10);
  qDebug() << "Comando: Frente" << endl;
}

void quibe::MainControl::comando_tras() {
  serial.enviaComandoMovimento(ComunicacaoSerial::TRAS, velocidade/10);
  qDebug() << "Comando: Tras" << endl;
}

void quibe::MainControl::comando_subir() {
  serial.enviaComandoMovimento(ComunicacaoSerial::SUBIR, velocidade/10);
  qDebug() << "Comando: Subir" << endl;
}

void quibe::MainControl::comando_descer() {
  serial.enviaComandoMovimento(ComunicacaoSerial::DESCER, velocidade/10);
  qDebug() << "Comando: Descer" << endl;
}

void quibe::MainControl::comando_horario() {
  serial.enviaComandoMovimento(ComunicacaoSerial::HORARIO, velocidade/10);
  qDebug() << "Comando: Girar Sentido Horário" << endl;
}

void quibe::MainControl::comando_antihorario() {
  serial.enviaComandoMovimento(ComunicacaoSerial::ANTIHORARIO, velocidade/10);
  qDebug() << "Comando: Girar Sentido Anti-Horário" << endl;
}

void quibe::MainControl::comando_parar() {
  serial.enviaComandoMovimento(ComunicacaoSerial::PARAR, velocidade/10);
  qDebug() << "Comando: Parar" << endl;
}

void quibe::MainControl::conectar_serial(bool conectar, SerialConfig config) {
  if (conectar) {
    bool conectado = serial.conectar(config);
    emit serial_conectado(conectado);
  } else {
    serial.desconectar();
    emit serial_desconectado();
  }
}

void quibe::MainControl::conectar_quadricoptero(bool conectar) {
  if (conectar) {
    serial.enviaHandshake();
  }
  else {
    // Desconectar
  }
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

void quibe::MainControl::parse_message(QByteArray mensagem) {
  switch (mensagem[3]) {
  case ComunicacaoSerial::DIAGNOSTIC:
    qDebug() << "Recebeu mensagem de diagnóstico";
    if (mensagem[4] & ComunicacaoSerial::READY) {
      emit quadricoptero_conectado(true);
    }
    else {
      QThread::currentThread()->sleep(1);
      serial.enviaHandshake();
    }
    break;
  case ComunicacaoSerial::SONAR_DATA:
    uint sensor_cima, sensor_baixo, sensor_frente, sensor_tras, sensor_esquerda, sensor_direita;

    sensor_cima = (mensagem[4] << 8) + mensagem[5];
    sensor_baixo = (mensagem[6] << 8) + mensagem[7];
    sensor_frente = (mensagem[8] << 8) + mensagem[9];
    sensor_tras = (mensagem[10] << 8) + mensagem[11];
    sensor_esquerda = (mensagem[12] << 8) + mensagem[13];
    sensor_direita = (mensagem[14] << 8) + mensagem[15];

    emit dados_sonar_recebidos(sensor_cima, sensor_baixo, sensor_frente,
                               sensor_tras, sensor_esquerda, sensor_direita);

    break;
  default:
    break;
  }
}
