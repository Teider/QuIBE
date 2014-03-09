#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace quibe {
class MainControl;
}

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(quibe::MainControl *controle = 0, QWidget *parent = 0);
  ~MainWindow();

public slots:
  void enableConectarQuadricoptero(bool enable);
  void enableDecolar(bool enable);
  void enableComandos();
  void disableComandos();

  void displayMessage(QString message);

signals:
  void velocidade_alterada(int velocidade);

protected:
  void keyPressEvent(QKeyEvent *e);
  void keyReleaseEvent(QKeyEvent *e);

private:
  Ui::MainWindow *ui;

  quibe::MainControl *controle;

  bool noAr;

  void setupSignals();

private slots:
  void toggleConectarSerial(bool conectar);
  void toggleConectarQuadricoptero(bool conectar);
  void toggleDecolar(bool decolar);
  void mudarVelocidade(int nova_velocidade);
  void mudarVelocidade(QString nova_velocidade);

  void serialConectado(bool conectado);

};

#endif // MAINWINDOW_H
