#ifndef GLVIEW_H
#define GLVIEW_H

#define GL_SILENCE_DEPRECATION

#include <QMouseEvent>
#include <QOpenGLWidget>

#include "../controller/controller.h"
#include "../model/model.h"
// #include "view.h"

#define PARALLEL 1
#define CENTRAL 0
#define SOLID 1
#define DASHED 0
#define VERTEX_NONE 0
#define VERTEX_CIRCLE 1
#define VERTEX_SQUARE 2

namespace s21 {
/**
 * @brief Структура настроек для glView.
 *
 * Содержит параметры для управления визуализацией, такие как перемещение,
 * вращение, масштабирование, цвета и типы вершин.
 */
typedef struct setting {
  int move_x_ = 0;      ///< Смещение по оси X.
  int move_y_ = 0;      ///< Смещение по оси Y.
  int move_z_ = 0;      ///< Смещение по оси Z.
  int rotate_x_ = 0;    ///< Вращение по оси X.
  int rotate_y_ = 0;    ///< Вращение по оси Y.
  int rotate_z_ = 0;    ///< Вращение по оси Z.
  double scale_ = 10.;  ///< Масштаб.

  QColor background_color_ = Qt::black;  ///< Цвет фона.
  QColor vertex_color_ = Qt::white,
         edge_color_ = Qt::white;  ///< Цвета вершин и ребер.

  int type_vertexes_ = VERTEX_NONE;  ///< Тип вершин.
  int type_projection_ = CENTRAL;    ///< Тип проекции.
  int type_line_ = SOLID;            ///< Тип линий.
  float vertex_thicknes_ = 0.5,
        edge_thicknes_ = 0.5;  ///< Толщина вершин и ребер.

} Setting;
}  // namespace s21

/**
 * @brief Класс для работы с OpenGL визуализацией.
 *
 * Этот класс предоставляет функциональность для отображения и взаимодействия с
 * 3D сценой.
 */
class glView : public QOpenGLWidget {
  Q_OBJECT
 public:
  /**
   * @brief Конструктор glView.
   * @param parent Указатель на родительский виджет.
   */
  glView(QWidget* parent = nullptr);
  float xRot = 0;  ///< Угол вращения по оси X.
  float yRot = 0;  ///< Угол вращения по оси Y.
  float xRotLast = 0;  ///< Предыдущий угол вращения по оси X.
  float yRotLast = 0;  ///< Предыдущий угол вращения по оси Y.
  QPoint mpos;  ///< Позиция мыши.
  /**
   * @brief Установка контроллера.
   * @param controller Указатель на контроллер.
   */
  void setController(s21::Controller* controller);
  /**
   * @brief Получение настроек.
   * @return Ссылка на настройки.
   */
  s21::Setting& getSetting();
  /**
   * @brief Захват кадра из буфера кадров.
   * @return QImage с захваченным кадром.
   */
  QImage s21_grabFrameBuffer();

 protected:
  /**
   * @brief Инициализация OpenGL.
   */
  void initializeGL() override;
  /**
   * @brief Изменение размера OpenGL виджета.
   * @param width Ширина виджета.
   * @param height Высота виджета.
   */
  void resizeGL(int width, int height) override;
  /**
   * @brief Рендеринг OpenGL.
   */
  void paintGL() override;

 private:
  /**
   * @brief Обработка события нажатия мыши.
   * @param event Событие мыши.
   */
  void mousePressEvent(QMouseEvent*) override;
  /**
   * @brief Обработка события перемещения мыши.
   * @param mo Событие мыши.
   */
  void mouseMoveEvent(QMouseEvent* mo) override;
  s21::Controller* controller_ = nullptr;  ///< Указатель на контроллер.
  s21::Setting setting_{};                 ///< Настройки.

  // public slots:
  //     void triggerRender(QString fileName);
};

#endif  // VIEW_H
