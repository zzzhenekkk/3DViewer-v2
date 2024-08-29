/*!
\file Affine.h
\brief Функции для аффинных преобразований геометрических данных

Этот заголовочный файл содержит определения функций для выполнения аффинных
преобразований над геометрическими данными, такими как нормализация,
масштабирование, централизация и поворот. Эти функции используются для изменения
положения и ориентации геометрических объектов в трехмерном пространстве.
*/

#include "affine.h"

namespace s21 {

/**
 * @brief Нормализует вершины объекта.
 *
 * @param obj Указатель на структуру v_data, содержащую данные вершин.
 */
void Affine::normalize(std::vector<float>& vektorVertexes) {
  double max_v = 0.0;
  for (int i = 0; i < (int)vektorVertexes.size(); i++) {
    if (fabs(vektorVertexes[i]) > max_v) max_v = fabs(vektorVertexes[i]);
  }
  if (max_v != 0.) {
    for (int i = 0; i < (int)vektorVertexes.size(); i++) {
      vektorVertexes[i] /= max_v * SCALE_FACTOR;
    }
  }
}

/**
 * @brief Изменяет масштаб объекта.
 *
 * @param obj Указатель на структуру v_data, содержащую данные вершин.
 * @param coef Коэффициент масштабирования.
 */
void Affine::changeScale(std::vector<float>& vektorVertexes, float coef) {
  if (fabs(coef - 1.0) <= 1e-03) return;
  for (int i = 0; i < (int)vektorVertexes.size(); i++) {
    vektorVertexes[i] *= coef;
  }
}

/**
 * @brief Централизует объект.
 *
 * @param obj Указатель на структуру v_data, содержащую данные вершин.
 */
void Affine::centralize(std::vector<float>& vektorVertexes) {
  // float centx = getCenter(vektorVertexes, 0);
  // float centy = getCenter(vektorVertexes, 1);
  // float centz = getCenter(vektorVertexes, 2);
  setCenter(vektorVertexes, 0, 0);
  setCenter(vektorVertexes, 1, 0);
  setCenter(vektorVertexes, 2, 0);
}

/**
 * @brief Возвращает координату центра объекта по указанной оси.
 *
 * @param obj Указатель на структуру v_data, содержащую данные вершин.
 * @param ax Ось (0 - X, 1 - Y, 2 - Z).
 * @return Координата центра по выбранной оси.
 */
float Affine::getCenter(std::vector<float>& vektorVertexes, int ax) {
  float min = vektorVertexes[ax];
  float max = vektorVertexes[ax];

  for (int i = 0; i < (int)vektorVertexes.size() / 3; i++) {
    float value = vektorVertexes[i * 3 + ax];
    if (value < min) min = value;
    if (value > max) max = value;
  }
  return (max + min) / 2;
}

/**
 * @brief Централизует объект по указанной оси.
 *
 * @param obj Указатель на структуру v_data, содержащую данные вершин.
 * @param ax Ось (0 - X, 1 - Y, 2 - Z).
 * @param cent Новая координата центра по выбранной оси.
 */
void Affine::setCenter(std::vector<float>& vektorVertexes, int ax,
                       float newCenter) {
  float currentCenter = getCenter(vektorVertexes, ax);
  float delta = newCenter - currentCenter;

  for (int i = 0; i < (int)vektorVertexes.size() / 3; i++) {
    vektorVertexes[i * 3 + ax] += delta;
  }
}

/**
 * @brief Сдвигает объект по трем осям.
 *
 * @param obj Указатель на структуру v_data, содержащую данные вершин.
 * @param value1 Значение сдвига по оси X.
 * @param value2 Значение сдвига по оси Y.
 * @param value3 Значение сдвига по оси Z.
 */
void Affine::shift(std::vector<float>& vektorVertexes, double value1,
                   double value2, double value3) {
  for (int i = 0; i < (int)vektorVertexes.size() / 3; i++) {
    vektorVertexes[i * 3 + 0] += value1;
    vektorVertexes[i * 3 + 1] += value2;
    vektorVertexes[i * 3 + 2] += value3;
  }
}

/**
 * @brief Поворачивает объект вокруг оси X.
 *
 * @param obj Указатель на структуру v_data, содержащую текущие данные вершин.
 * @param obj_copy Указатель на структуру v_data, содержащую копию исходных
 * данных вершин.
 * @param angle Угол поворота в радианах.
 */
void Affine::rotateX(std::vector<float>& vektorVertexes, float angle) {
  for (int i = 0; i < (int)vektorVertexes.size() / 3; i++) {
    vektorVertexes[i * 3 + 0] = vektorVertexes[i * 3 + 0];
    float y = vektorVertexes[i * 3 + 1];  // copy_y
    vektorVertexes[i * 3 + 1] = cos(angle) * vektorVertexes[i * 3 + 1] +
                                sin(angle) * vektorVertexes[i * 3 + 2];  // y
    vektorVertexes[i * 3 + 2] =
        -sin(angle) * y + cos(angle) * vektorVertexes[i * 3 + 2];  // z
  }
}

/**
 * @brief Поворачивает объект вокруг оси Y.
 *
 * @param obj Указатель на структуру v_data, содержащую текущие данные вершин.
 * @param obj_copy Указатель на структуру v_data, содержащую копию исходных
 * данных вершин.
 * @param angle Угол поворота в радианах.
 */
void Affine::rotateY(std::vector<float>& vektorVertexes, float angle) {
  for (int i = 0; i < (int)vektorVertexes.size() / 3; i++) {
    float x = vektorVertexes[i * 3];  // copy_x
    vektorVertexes[i * 3 + 1] = vektorVertexes[i * 3 + 1];
    vektorVertexes[i * 3] = cos(angle) * vektorVertexes[i * 3] +
                            sin(angle) * vektorVertexes[i * 3 + 2];  // x
    vektorVertexes[i * 3 + 2] =
        -sin(angle) * x + cos(angle) * vektorVertexes[i * 3 + 2];  // z
  }
}

/**
 * @brief Поворачивает объект вокруг оси Z.
 *
 * @param obj Указатель на структуру v_data, содержащую текущие данные вершин.
 * @param obj_copy Указатель на структуру v_data, содержащую копию исходных
 * данных вершин.
 * @param angle Угол поворота в радианах.
 */
void Affine::rotateZ(std::vector<float>& vektorVertexes, float angle) {
  for (int i = 0; i < (int)vektorVertexes.size() / 3; i++) {
    float oldX = vektorVertexes[i * 3];
    float oldY = vektorVertexes[i * 3 + 1];

    vektorVertexes[i * 3] = cos(angle) * oldX + sin(angle) * oldY;
    vektorVertexes[i * 3 + 1] = -sin(angle) * oldX + cos(angle) * oldY;
    vektorVertexes[i * 3 + 2] = vektorVertexes[i * 3 + 2];
  }
}

}  // namespace s21
