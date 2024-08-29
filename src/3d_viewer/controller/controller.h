// #pragma once
#ifndef CH
#define CH

#include <string>
#include <vector>
// #include <QMainWindow>
// #include <QFileDialog>

#include "../model/model.h"
// #include "../view/glview.h"
class view;

namespace s21 {

/**
 * @brief Класс контроллера для управления моделью и представлением.
 *
 * Этот класс предоставляет функции для загрузки модели, изменения ее положения,
 * вращения, масштабирования, а также получения информации о модели, такой как
 * количество вершин, полигонов и ребер.
 */
class Controller {
 public:
  /**
   * @brief Конструктор контроллера.
   * @param model Указатель на модель.
   */
  Controller(Model* model) : model_(model){};

  /**
   * @brief Установка представления.
   * @param viewTmp_ Указатель на представление.
   */
  void setView(view* viewTmp_) { view_ = viewTmp_; }

  /**
   * @brief Загрузка модели из файла.
   * @param path Путь к файлу модели.
   */
  bool loadModel(std::string path);

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
   * @param x Угол вращения.
   */
  void rotateModelY(double x);

  /**
   * @brief Вращение модели вокруг оси Z.
   * @param x Угол вращения.
   */
  void rotateModelZ(double x);

  /**
   * @brief Изменение масштаба модели.
   * @param scale Масштаб.
   */
  void changeScale(double scale);

  /**
   * @brief Установка центра модели.
   */
  void setCenter();

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

  void clearModel();

 private:
  Model* model_;          ///< Указатель на модель.
  view* view_ = nullptr;  ///< Указатель на представление.
};

}  // namespace s21
#endif
