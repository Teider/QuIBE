#include "serialconfig.h"

quibe::SerialConfig::SerialConfig() {
}

void quibe::SerialConfig::setBaudRate(QString str) {
  int aux = str.toInt();

  switch (aux) {
  case QSerialPort::Baud1200:
    baudRate = QSerialPort::Baud1200;
  break;
  case QSerialPort::Baud2400:
    baudRate = QSerialPort::Baud2400;
  break;
  case QSerialPort::Baud4800:
    baudRate = QSerialPort::Baud4800;
  break;
  case QSerialPort::Baud9600:
    baudRate = QSerialPort::Baud9600;
  break;
  case QSerialPort::Baud19200:
    baudRate = QSerialPort::Baud19200;
  break;
  case QSerialPort::Baud38400:
    baudRate = QSerialPort::Baud38400;
  break;
  case QSerialPort::Baud57600:
    baudRate = QSerialPort::Baud57600;
  break;
  case QSerialPort::Baud115200:
    baudRate = QSerialPort::Baud115200;
  break;
  default:
    baudRate = QSerialPort::UnknownBaud;
  break;
  }
}

void quibe::SerialConfig::setDataBits(QString str) {
  int aux = str.toInt();

  switch (aux) {
  case QSerialPort::Data5:
    databits = QSerialPort::Data5;
    break;
  case QSerialPort::Data6:
    databits = QSerialPort::Data6;
    break;
  case QSerialPort::Data7:
    databits = QSerialPort::Data7;
    break;
  case QSerialPort::Data8:
    databits = QSerialPort::Data8;
    break;
  default:
    databits = QSerialPort::UnknownDataBits;
    break;
  }
}

void quibe::SerialConfig::setStopBits(QString str) {
  if (str == "One") stopBits = QSerialPort::OneStop;
  else if (str == "OneAndHalf") stopBits = QSerialPort::OneAndHalfStop;
  else if (str == "Two") stopBits = QSerialPort::TwoStop;
  else stopBits = QSerialPort::UnknownStopBits;
}

void quibe::SerialConfig::setParity(QString str) {
  if (str == "None") parity = QSerialPort::NoParity;
  else if (str == "Even") parity = QSerialPort::EvenParity;
  else if (str == "Odd") parity = QSerialPort::OddParity;
  else if (str == "Space") parity = QSerialPort::SpaceParity;
  else if (str == "Mark") parity = QSerialPort::MarkParity;
  else parity = QSerialPort::UnknownParity;
}
