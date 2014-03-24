#include "maincontrol.h"

#include <QThread>
#include <QDebug>

quibe::MainControl::MainControl(QObject *parent) :
  QObject(parent) {
  velocidade = 50;

  velocidade_counter = 0;

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
  velocidade_counter++;
  if (velocidade_counter > 100) velocidade_counter = 100;
  //qDebug() << "Comando: Subir" << endl;
  qDebug() << "Velocidade Atual: " << velocidade_counter;
}

void quibe::MainControl::comando_descer() {
  serial.enviaComandoMovimento(ComunicacaoSerial::DESCER, velocidade/10);
  velocidade_counter--;
  if (velocidade_counter < 0) velocidade_counter = 0;
  //qDebug() << "Comando: Descer" << endl;
  qDebug() << "Velocidade Atual: " << velocidade_counter;
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
    serial.enviaComandoMovimento(ComunicacaoSerial::DECOLAR, 0);
  } else {
    serial.enviaComandoMovimento(ComunicacaoSerial::POUSAR, 0);
  }
}

void quibe::MainControl::velocidade_alterada(int velocidade) {
  this->velocidade = velocidade;
  qDebug() << "Velocidade alterada para: " << velocidade << "\%" << endl;
}

void quibe::MainControl::parse_message(QByteArray mensagem) {

  int id_motor;
  int vel;
  int comp;

  int delta_t;

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
    qDebug() << "Recebeu dados do sonar";
    uint sensor_cima, sensor_baixo, sensor_frente, sensor_tras, sensor_esquerda, sensor_direita;

    sensor_frente = (((uint)mensagem[4]) << 8) + ((uint)mensagem[5]);
    sensor_tras = (((uint)mensagem[6]) << 8) + ((uint)mensagem[7]);
    sensor_esquerda = (((uint)mensagem[8]) << 8) + ((uint)mensagem[9]);
    sensor_direita = (((uint)mensagem[10] << 8)) + ((uint)mensagem[11]);
    sensor_cima = (((uint)mensagem[12]) << 8) + ((uint)mensagem[13]);
    sensor_baixo = (((uint)mensagem[14]) << 8) + ((uint)mensagem[15]);

    emit dados_sonar_recebidos(sensor_cima, sensor_baixo, sensor_frente,
                               sensor_tras, sensor_esquerda, sensor_direita);

    break;
  case ComunicacaoSerial::MPU6050_DATA:
    int roll, pitch, yaw;

    //qDebug() << "Leitura do MPU recebido do micro: " <<  mensagem.toHex();

    roll = (((int)mensagem[4]) << 8) + (((int)mensagem[5]) & 0xFF);
    pitch = (((int)mensagem[6]) << 8) + (((int)mensagem[7]) & 0xFF);
    yaw = (((int)mensagem[8]) << 8) + (((int)mensagem[9]) & 0xFF);

    roll -= 180;
    pitch -= 180;
    yaw -= 180;

    qDebug() << "Leitura do MPU recebido do micro:";
    qDebug() << "Roll: " << roll << "    Pitch: " << pitch;

    emit dados_angulo_recebidos(roll, pitch, yaw);
    break;
  case ComunicacaoSerial::VELOCIDADE_MOTOR:
    id_motor = ((int)mensagem[4]);
    vel = ((int)mensagem[5]);
    comp = ((int)mensagem[6]);

    qDebug() << "Alterou velocidade do motor " << id_motor << "para " << vel <<
                " com compensação " << comp;
    //qDebug() << mensagem.toHex();
    break;
  case ComunicacaoSerial::DELTA_T:
    delta_t = (((int)mensagem[4]) << 8) + (((int)mensagem[5]) & 0xFF);

    qDebug() << "DELTA T: " << delta_t;
    //qDebug() << mensagem.toHex();
    break;
  case ComunicacaoSerial::STATUS_ON_AIR:
    emit decolou();
    break;
  case ComunicacaoSerial::STATUS_ON_GROUND:
    emit pousou();
    break;
  default:
    qDebug() << "ERRO! Recebida mensagem inesperada.";
    qDebug() << "Data Dump da mensagem:";
    for (int i = 0; i < 8; i++) {
      qDebug() << mensagem.left(4).toHex();
      mensagem.remove(0,4);
    }
    break;
  }
}
