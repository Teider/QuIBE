#ifndef SERIALCONFIG_H
#define SERIALCONFIG_H

#include <QString>
#include <QtSerialPort/QSerialPort>

namespace quibe {

class SerialConfig
{
public:
  SerialConfig();

  QString portName;
  QSerialPort::BaudRate baudRate;
  QSerialPort::DataBits databits;
  QSerialPort::StopBits stopBits;
  QSerialPort::FlowControl flowControl;
  QSerialPort::Parity parity;

  void setBaudRate(QString str);
  void setDataBits(QString str);
  void setStopBits(QString str);
  void setParity(QString str);
};

}

#endif // SERIALCONFIG_H
