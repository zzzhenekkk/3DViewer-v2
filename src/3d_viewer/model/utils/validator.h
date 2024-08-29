#pragma once
#include <vector>

#include "../model.h"

namespace s21 {

/**
 * @brief Класс для проверки валидности вершин и граней.
 *
 * Этот класс предоставляет методы для проверки валидности коллекций вершин и
 * граней. Реализует синглтон паттерн для обеспечения единственного экземпляра
 * валидатора.
 */
class Validator {
 public:
  Validator() = delete;

  static bool validation(std::vector<float>& vektorVertexes,
                         std::vector<unsigned int>& polygons,
                         int count_vertexes);

 private:
  Validator(const Validator&) = delete;

  Validator& operator=(const Validator&) = delete;

  /**
   * @brief Проверяет валидность коллекции вершин.
   *
   * @param v Коллекция вершин для проверки.
   * @return true, если коллекция вершин валидна, иначе false.
   */
  static bool checkVertexes(std::vector<float>& vektorVertexes);

  /**
   * @brief Проверяет валидность коллекции граней.
   *
   * @param p Коллекция граней для проверки.
   * @return true, если коллекция граней валидна, иначе false.
   */
  static bool checkFacets(std::vector<unsigned int>& polygons,
                          int count_vertexes);
};

}  // namespace s21
