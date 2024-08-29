#include <QApplication>

#include "../controller/controller.h"
#include "../model/model.h"
#include "view/view.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  s21::Model& m = s21::Model::getInstance();
  s21::Controller c(&m);

  view w(nullptr, &c);
  w.show();
  return a.exec();
}
