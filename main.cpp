#include "maincontrol.h"

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  quibe::MainControl controle;

  MainWindow w(&controle);
  w.show();

  return a.exec();
}
