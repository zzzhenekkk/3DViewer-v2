#pragma once
#include <string>
#include <vector>

#include "utils/affine.h"
#include "utils/parser.h"
#include "utils/validator.h"

namespace s21 {

/**
 * @brief Класс модели для хранения и управления геометрическими данными.
 *
 * Этот класс предоставляет функции для загрузки модели, добавления полигонов и
 * вершин, а также получения информации о модели, такой как количество вершин,
 * полигонов и ребер.
 */
class Model {
 public:
  // Удаление возможности копирования и присваивания
  Model(Model const&) = delete;
  void operator=(Model const&) = delete;

  /**
   * @brief Получение экземпляра класса Model.
   * @return Ссылка на экземпляр класса Model.
   */
  static Model& getInstance();

  /**
   * @brief Получение вектора вершин модели.
   * @return Ссылка на вектор вершин.
   */
  std::vector<float>& getVertexes();

  /**
   * @brief Получение вектора полигонов модели.
   * @return Ссылка на вектор полигонов.
   */
  std::vector<unsigned int>& getPolygons();

  /**
   * @brief Загрузка модели из файла.
   * @param path Путь к файлу модели.
   */
  void loadModel(std::string path);

  /**
   * @brief Добавление полигона в модель.
   * @param nums Вектор индексов вершин полигона.
   */
  void addPolygon(std::vector<unsigned int>& nums);

  /**
   * @brief Добавление вершины в модель.
   * @param a Координата X вершины.
   * @param b Координата Y вершины.
   * @param c Координата Z вершины.
   */
  void addVertex(float a, float b, float c);

  /**
   * @brief Очистка модели.
   */
  void clear();

  /**
   * @brief Получение количества вершин в модели.
   * @return Количество вершин.
   */
  int getCountVertexes();

  /**
   * @brief Получение количества полигонов в модели.
   * @return Количество полигонов.
   */
  int getCountPolygons();

  /**
   * @brief Получение количества ребер в модели.
   * @return Количество ребер.
   */
  int getCountEdges();

 private:
  // создать экземпляр класса мы можем только изнутри
  Model() {}

  std::vector<unsigned int> polygons_{};
  std::vector<float> vertexes_{};
  int count_edges_;
  int count_polygons_;
  int count_vertexes_;
};

/**
 * @brief Фасад для работы с моделью.
 *
 * Этот класс предоставляет удобный интерфейс для загрузки модели, изменения ее
 * положения, вращения, масштабирования, а также установки центра модели.
 */
class ModelFacade {
 public:
  /**
   * @brief Конструктор фасада модели.
   * @param model Ссылка на модель.
   */
  ModelFacade() : model_(Model::getInstance()) {}

  /**
   * @brief Загрузка модели из файла.
   * @param filename Имя файла модели.
   */
  bool loadModel(const std::string& filename);

  /**
   * @brief Перемещение модели.
   * @param x Смещение по оси X.
   * @param y Смещение по оси Y.
   * @param z Смещение по оси Z.
   */
  void moveModel(double x, double y, double z);

  /**
   * @brief Вращение модели вокруг оси X.
   * @param x Угол вращения.
   */
  void rotateModelX(double x);

  /**
   * @brief Вращение модели вокруг оси Y.
   * @param y Угол вращения.
   */
  void rotateModelY(double y);

  /**
   * @brief Вращение модели вокруг оси Z.
   * @param z Угол вращения.
   */
  void rotateModelZ(double z);

  /**
   * @brief Изменение масштаба модели.
   * @param scale Масштаб.
   */
  void changeScale(double scale);

  /**
   * @brief Установка центра модели.
   */
  void setCenter();

 private:
  Model& model_;
};

}  // namespace s21
