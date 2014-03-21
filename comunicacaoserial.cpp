#include "comunicacaoserial.h"

#include <QSerialPort>

#include <QDebug>

quibe::ComunicacaoSerial::ComunicacaoSerial(QObject *parent) :
  QObject(parent) {

  QObject::connect(&serialPort, SIGNAL(readyRead()),
                   this, SLOT(recebeBytes()));

  message_id = 1;
}

bool quibe::ComunicacaoSerial::conectar(SerialConfig config) {
  serialPort.setPortName(config.portName);
  if (!serialPort.open(QIODevice::ReadWrite)) return false;
  serialPort.setBaudRate(config.baudRate);
  serialPort.setDataBits(config.databits);
  serialPort.setParity(config.parity);
  serialPort.setStopBits(config.stopBits);
  serialPort.setFlowControl(config.flowControl);

  return true;
}

void quibe::ComunicacaoSerial::desconectar() {
  serialPort.close();
}

void quibe::ComunicacaoSerial::recebeBytes() {
  while (serialPort.bytesAvailable()) {
    buffer.append(serialPort.readAll());

    //qDebug() << "Recebeu bytes. Buffer está com " << buffer.size() << "bytes";

    if (buffer.size() >= 4) {

      //qDebug() << "Tipo da mensagem atual é " << buffer.mid(3,1).toHex();
      switch (buffer[3]) {
      case DIAGNOSTIC:
        //qDebug() << "Mensagem Atual é diagnóstico.";
      case COLLISION_DETECTED:
        if (buffer.size() >= 5) {
          emit mensagemLida(buffer.left(5));
          buffer.remove(0,5);
        }
        break;
      case SENSOR_DATA:
        if (buffer.size() >= 28) {
          emit mensagemLida(buffer.left(28));
          buffer.remove(0,28);
        }
        break;
      case MPU6050_DATA:
        if (buffer.size() >= 10) {
          emit mensagemLida(buffer.left(10));
          buffer.remove(0,10);
        };
        break;
      case SONAR_DATA:
        if (buffer.size() >= 16) {
          emit mensagemLida(buffer.left(16));
          buffer.remove(0,16);
        };
        break;
      case VELOCIDADE_MOTOR:
        if (buffer.size() >= 6) {
          emit mensagemLida(buffer.left(6));
          buffer.remove(0,6);
        }
      default:
        //Erro ocorreu, tratar
        if (buffer.size() >= 32) {
          emit mensagemLida(buffer.left(32));
          buffer.remove(0,32);
        }
        break;
      }
    }
  }
}

bool quibe::ComunicacaoSerial::emitirMensagem(QByteArray mensagem) {
  int msg_size = mensagem.size();
  int bytes_written = serialPort.write(mensagem);
  message_id += 2;
  if (message_id > 0xFFFFFF) message_id = 0;
  if (msg_size != bytes_written) return false;
  return true;
}

bool quibe::ComunicacaoSerial::enviaHandshake() {
  QByteArray msg;
  msg.append(id());
  msg.append((char)HANDSHAKE);
  return emitirMensagem(msg);
}

bool quibe::ComunicacaoSerial::enviaComandoMovimento(MOVE_TYPE tipo, int velocidade) {
  QByteArray msg;
  msg.append(id());
  msg.append((char)tipo);
  if (!((tipo == DECOLAR) || (tipo == POUSAR) || (tipo == PARAR)))
    msg.append((char)(velocidade & 0xFF));
  return emitirMensagem(msg);
}

QByteArray quibe::ComunicacaoSerial::id() {
  QByteArray ret;
  ret.append(((char)((message_id & 0xFF0000) >> 16)));
  ret.append(((char)((message_id & 0xFF00) >> 8)));
  ret.append(((char)((message_id & 0xFF))));
  return ret;
}
