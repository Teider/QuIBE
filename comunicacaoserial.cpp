#include "comunicacaoserial.h"

#include <QSerialPort>

#include <QDebug>

quibe::ComunicacaoSerial::ComunicacaoSerial(QObject *parent) :
  QObject(parent) {
}

bool quibe::ComunicacaoSerial::conectar(SerialConfig config) {
  serialPort.setPortName(config.portName);
  if (!serialPort.open(QIODevice::ReadOnly)) return false;
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
