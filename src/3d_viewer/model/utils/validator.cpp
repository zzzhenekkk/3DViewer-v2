#include "validator.h"

namespace s21 {
bool Validator::checkVertexes(std::vector<float>& vektorVertexes) {
  return vektorVertexes.size() % 3 == 0;
}

bool Validator::checkFacets(std::vector<unsigned int>& polygons,
                            int count_vertexes) {
  bool status = true;
  for (unsigned int element : polygons) {
    if ((int)element >= count_vertexes) status = false;
  }
  return (polygons.size() % 2 == 0) && status;
}

bool Validator::validation(std::vector<float>& vektorVertexes,
                           std::vector<unsigned int>& polygons,
                           int count_vertexes) {
  return checkVertexes(vektorVertexes) && checkFacets(polygons, count_vertexes);
}

}  // namespace s21
