#pragma once

#define SCALE_FACTOR 1.5

#include <cmath>
#include <vector>

namespace s21 {
class AffineTest;
/**
 * @brief Класс для выполнения аффинных преобразований над вектором вершин.
 *
 * Этот класс предоставляет статические методы для нормализации, изменения
 * масштаба, центрирования, сдвига и вращения вектора вершин.
 */
class Affine {
 public:
  friend class AffineTest;
  /**
   * @brief Конструктор класса Affine запрещен.
   */
  Affine() = delete;

  /**
   * @brief Нормализует вектор вершин.
   *
   * @param vektorVertexes Вектор вершин для нормализации.
   */
  static void normalize(std::vector<float>& vektorVertexes);

  /**
   * @brief Изменяет масштаб вектора вершин.
   *
   * @param vektorVertexes Вектор вершин для изменения масштаба.
   * @param coef Коэффициент масштабирования.
   */
  static void changeScale(std::vector<float>& vektorVertexes, float coef);

  /**
   * @brief Центрирует вектор вершин.
   *
   * @param vektorVertexes Вектор вершин для центрирования.
   */
  static void centralize(std::vector<float>& vektorVertexes);

  /**
   * @brief Сдвигает вектор вершин.
   *
   * @param vektorVertexes Вектор вершин для сдвига.
   * @param value1 Сдвиг по оси X.
   * @param value2 Сдвиг по оси Y.
   * @param value3 Сдвиг по оси Z.
   */
  static void shift(std::vector<float>& vektorVertexes, double value1,
                    double value2, double value3);

  /**
   * @brief Вращает вектор вершин вокруг оси X.
   *
   * @param vektorVertexes Вектор вершин для вращения.
   * @param angle Угол вращения в градусах.
   */
  static void rotateX(std::vector<float>& vektorVertexes, float angle);

  /**
   * @brief Вращает вектор вершин вокруг оси Y.
   *
   * @param vektorVertexes Вектор вершин для вращения.
   * @param angle Угол вращения в градусах.
   */
  static void rotateY(std::vector<float>& vektorVertexes, float angle);

  /**
   * @brief Вращает вектор вершин вокруг оси Z.
   *
   * @param vektorVertexes Вектор вершин для вращения.
   * @param angle Угол вращения в градусах.
   */
  static void rotateZ(std::vector<float>& vektorVertexes, float angle);

 private:
  /**
   * @brief Конструктор копирования класса Affine запрещен.
   */
  Affine(const Affine&) = delete;

  /**
   * @brief Оператор присваивания класса Affine запрещен.
   */
  Affine& operator=(const Affine&) = delete;

  /**
   * @brief Получает центр вектора вершин по заданной оси.
   *
   * @param vektorVertexes Вектор вершин.
   * @param ax Ось (0 - X, 1 - Y, 2 - Z).
   * @return Центр вектора вершин по заданной оси.
   */
  static float getCenter(std::vector<float>& vektorVertexes, int ax);

  /**
   * @brief Устанавливает центр вектора вершин по заданной оси.
   *
   * @param vektorVertexes Вектор вершин.
   * @param ax Ось (0 - X, 1 - Y, 2 - Z).
   * @param cent Новое значение центра.
   */
  static void setCenter(std::vector<float>& vektorVertexes, int ax, float cent);
};

}  // namespace s21
