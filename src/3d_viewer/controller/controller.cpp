#include "controller.h"

namespace s21 {

bool Controller::loadModel(std::string path) {
  ModelFacade ModelFacade;
  return ModelFacade.loadModel(path);
}

// Функции для обработки действий пользователя
void Controller::moveModel(double x, double y, double z) {
  ModelFacade ModelFacade;
  ModelFacade.moveModel(x, y, z);
}

std::vector<float>& Controller::getVertexes() { return model_->getVertexes(); }

std::vector<unsigned int>& Controller::getPolygons() {
  return model_->getPolygons();
}

void Controller::rotateModelX(double x) {
  ModelFacade ModelFacade;
  ModelFacade.rotateModelX(x);
}
void Controller::rotateModelY(double y) {
  ModelFacade ModelFacade;
  ModelFacade.rotateModelY(y);
}
void Controller::rotateModelZ(double z) {
  ModelFacade ModelFacade;
  ModelFacade.rotateModelZ(z);
}

void Controller::changeScale(double scale) {
  ModelFacade ModelFacade;
  ModelFacade.changeScale(scale);
}

void Controller::setCenter() {
  ModelFacade ModelFacade;
  ModelFacade.setCenter();
}

int Controller::getCountVertexes() { return model_->getCountVertexes(); }
int Controller::getCountPolygons() { return model_->getCountPolygons(); }
int Controller::getCountEdges() { return model_->getCountEdges(); }

void Controller::clearModel() {
  // ModelFacade ModelFacade;

  // ModelFacade.clearModel();
  model_->clear();
}

}  // namespace s21
