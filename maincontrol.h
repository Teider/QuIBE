#ifndef MAINCONTROL_H
#define MAINCONTROL_H

#include <QObject>

#include <comunicacaoserial.h>

namespace quibe {

class MainControl : public QObject {
  Q_OBJECT
public:
  explicit MainControl(QObject *parent = 0);

signals:
  void message(QString message);
  void serial_conectado(bool conectado);
  void quadricoptero_conectado(bool conectado);
  void decolou();
  void pousou();

public slots:
  void comando_esquerda();
  void comando_direita();
  void comando_frente();
  void comando_tras();
  void comando_subir();
  void comando_descer();
  void comando_horario();
  void comando_antihorario();
  void comando_parar();

  void conectar_serial(bool conectar, SerialConfig config);
  void conectar_quadricoptero(bool conectar);
  void comando_decolar_pousar(bool decolar);

  void velocidade_alterada(int velocidade);

private:

  int velocidade;
  ComunicacaoSerial serial;

};

}

#endif // MAINCONTROL_H
