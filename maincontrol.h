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

public slots:
  void comando_esquerda();
  void comando_direita();
  void comando_frente();
  void comando_tras();
  void comando_subir();
  void comando_descer();
  void comando_horario();
  void comando_antihorario();

};

}

#endif // MAINCONTROL_H
