#include "model.h"
namespace s21 {
std::vector<float>& Model::getVertexes() { return vertexes_; }
std::vector<unsigned int>& Model::getPolygons() { return polygons_; }
Model& Model::getInstance() {
  static Model instance;
  return instance;
}

void Model::loadModel(std::string path) {
  this->clear();
  Parser::parse(path);
  Affine::centralize(this->getVertexes());
  Affine::normalize(this->getVertexes());
}

void Model::clear() {
  polygons_.clear();
  vertexes_.clear();
  count_edges_ = 0;
  count_polygons_ = 0;
  count_vertexes_ = 0;
}

void Model::addPolygon(std::vector<unsigned int>& nums) {
  polygons_.push_back(--nums.front());
  for (auto it = nums.begin() + 1; it != nums.end(); ++it) {
    polygons_.push_back(--(*it));
    ++count_edges_;
    polygons_.push_back(*it);
  }
  polygons_.push_back(nums.front());
  ++count_edges_;
  ++count_polygons_;
}

void Model::addVertex(float a, float b, float c) {
  vertexes_.push_back(a);
  vertexes_.push_back(b);
  vertexes_.push_back(c);
  ++count_vertexes_;
}

bool ModelFacade::loadModel(const std::string& filename) {
  bool status = true;
  try {
    model_.loadModel(filename);
  } catch (...) {
    status = false;
  }
  return Validator::validation(model_.getVertexes(), model_.getPolygons(),
                               model_.getCountVertexes()) &&
         status;
}

void ModelFacade::moveModel(double x, double y, double z) {
  Affine::shift(model_.getVertexes(), x, y, z);
}

void ModelFacade::rotateModelX(double x) {
  Affine::rotateX(model_.getVertexes(), x);
}

void ModelFacade::rotateModelY(double y) {
  Affine::rotateY(model_.getVertexes(), y);
}

void ModelFacade::rotateModelZ(double z) {
  Affine::rotateZ(model_.getVertexes(), z);
}

void ModelFacade::changeScale(double scale) {
  Affine::changeScale(model_.getVertexes(), scale);
}

void ModelFacade::setCenter() { Affine::centralize(model_.getVertexes()); }

int Model::getCountVertexes() { return count_vertexes_; }
int Model::getCountPolygons() { return count_polygons_; }
int Model::getCountEdges() { return count_edges_; }

}  // namespace s21
