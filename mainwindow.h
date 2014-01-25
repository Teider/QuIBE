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
  void displayMessage(QString message);

private:
  Ui::MainWindow *ui;

  quibe::MainControl *controle;

  void setupShortcuts();
  void setupSignals();
};

#endif // MAINWINDOW_H
