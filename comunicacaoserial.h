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

  bool conectar(SerialConfig config);
  void desconectar();
  bool enviaHandshake();
  bool enviaComandoMovimento(MOVE_TYPE tipo, int velocidade);
  bool keepAlive();
  bool enviaErro(ERROR_TYPE tipo, int id);

  QByteArray lerMensagem();
  bool emitirMensagem(QByteArray mensagem);

signals:

public slots:

private:

  QSerialPort serialPort;

};

}

#endif // COMUNICACAOSERIAL_H
