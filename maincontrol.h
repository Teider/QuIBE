#ifndef MAINCONTROL_H
#define MAINCONTROL_H

#include <QObject>

namespace quibe {

class MainControl : public QObject {
  Q_OBJECT
public:
  explicit MainControl(QObject *parent = 0);

signals:
  void message(QString message);
  void conexao_serial(bool conectado);
  void conexao_quadricoptero(bool conectado);
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

  void conectar_serial(bool conectar);
  void conectar_quadricoptero(bool conectar);
  void comando_decolar_pousar(bool decolar);

};

}

#endif // MAINCONTROL_H
