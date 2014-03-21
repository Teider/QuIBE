#ifndef COMUNICACAOSERIAL_H
#define COMUNICACAOSERIAL_H

#include <QObject>

#include <QSerialPort>

#include "serialconfig.h"

namespace quibe {

class ComunicacaoSerial : public QObject
{
  Q_OBJECT
public:
  explicit ComunicacaoSerial(QObject *parent = 0);

  enum MOVE_TYPE {
    ESQUERDA = 0x00,
    DIREITA = 0x01,
    FRENTE = 0x02,
    TRAS = 0x03,
    HORARIO = 0x04,
    ANTIHORARIO = 0x05,
    SUBIR = 0x06,
    DESCER = 0x07,
    PARAR = 0x08,
    DECOLAR = 0x09,
    POUSAR = 0x0A
  };

  enum ERROR_TYPE {
    UNKNOWN_ERROR = 0x0B,
    WRONG_MSG_ID_ERROR = 0x0C,
    CORRUPTED_MSG_ERROR = 0x0D,
    UNEXPECTED_VALUE_ERROR = 0x0E,
    INVALID_VALUE_ERROR = 0x0F
  };

  enum OTHER_TYPE {
    HANDSHAKE = 0x10,
    DISCONNECT = 0x11,
    KEEP_ALIVE = 0x12
  };

  enum QUAD_MSG_TYPE {
    DIAGNOSTIC = 0x13,
    SENSOR_DATA = 0x14,
    COLLISION_DETECTED = 0x15,
    STATUS_ON_AIR = 0x16,
    STATUS_ON_GROUND = 0x17,
    REQUEST_DATA = 0x18,
    MPU6050_DATA = 0x19,
    SONAR_DATA = 0x1A,
    REQUEST_SONAR = 0x1B
  };

  enum DEBUG_TYPE {
    VELOCIDADE_MOTOR = 0x1C
  };

  enum DIAGNOSTIC_STATUS_BITMASK {
    READY = 0x80,
    ON_AIR = 0x40
  };

  bool conectar(SerialConfig config);
  void desconectar();
  bool enviaHandshake();
  bool enviaComandoMovimento(MOVE_TYPE tipo, int velocidade);
  bool keepAlive();
  bool enviaErro(ERROR_TYPE tipo, int id);

  //QByteArray lerMensagem();
  bool emitirMensagem(QByteArray mensagem);

signals:
  void mensagemLida(QByteArray mensagem);

public slots:
  void recebeBytes();

private:

  QSerialPort serialPort;

  uint message_id;
  QByteArray buffer;

  QByteArray id();

};

}

#endif // COMUNICACAOSERIAL_H
