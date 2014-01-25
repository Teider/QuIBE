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

private:
  Ui::MainWindow *ui;

  quibe::MainControl *controle;

  void setupShortcuts();
  void setupSignals();

private slots:
  void toggleConectarSerial(bool conectar);
  void toggleConectarQuadricoptero(bool conectar);
  void toggleDecolar(bool decolar);

};

#endif // MAINWINDOW_H
