#include "glview.h"

glView::glView(QWidget* parent) : QOpenGLWidget(parent) {
  // Инициализация, специфичная для вашего виджета
}

void glView::initializeGL() {
  // initializeOpenGLFunctions();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Черный фон
  glEnable(GL_DEPTH_TEST);  // Включение теста глубины
}

void glView::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);  // Настройка видового порта

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // glOrtho(-1.0, 1.0, -1.0, 1.0, 2.0, 15.0); // Ортографическая проекция
}

void glView::paintGL() {
  std::vector<float> vertices = controller_->getVertexes();
  std::vector<GLuint> indices = controller_->getPolygons();

  // GLfloat vertices[] = {
  //     -0.5f, -0.5f, -0.5f, // Вершина 0
  //     0.5f, -0.5f, -0.5f,  // Вершина 1
  //     0.5f,  0.5f, -0.5f,  // Вершина 2
  //     -0.5f,  0.5f, -0.5f, // Вершина 3
  //     -0.5f, -0.5f,  0.5f, // Вершина 4
  //     0.5f, -0.5f,  0.5f,  // Вершина 5
  //     0.5f,  0.5f,  0.5f,  // Вершина 6
  //     -0.5f,  0.5f,  0.5f  // Вершина 7
  // };

  // // Пример массива индексов для отрисовки треугольника линиями
  // GLuint indices[] = {
  //     0, 1, // Ребро между вершинами 0 и 1
  //     1, 2, // Ребро между вершинами 1 и 2
  //     2, 3, // Ребро между вершинами 2 и 3
  //     3, 0, // Ребро между вершинами 3 и 0
  //     4, 5, // Ребро между вершинами 4 и 5
  //     5, 6, // Ребро между вершинами 5 и 6
  //     6, 7, // Ребро между вершинами 6 и 7
  //     7, 4, // Ребро между вершинами 7 и 4
  //     0, 4, // Ребро между вершинами 0 и 4
  //     1, 5, // Ребро между вершинами 1 и 5
  //     2, 6, // Ребро между вершинами 2 и 6
  //     3, 7  // Ребро между вершинами 3 и 7
  // };

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);  // выбирает текущую матрицу для последующих
                                // операций над матрицами как матрицу проекции.
                                // Это необходимо для настройки перспективы.

  glLoadIdentity();  // загружает единичную матрицу, сбрасывая предыдущие
                     // преобразования, что является хорошей практикой перед
                     // установкой новой проекции.

  glFrustum(-1, 1, -1, 1, 2, 15);  //
  // glOrtho(-1.0, 1.0, -1.0, 1.0, 2, 15);
  glTranslated(0.0, 0.0, -3.0);  // Сдвигаем сцену назад, чтобы объект был виден

  glRotatef(xRot, 1, 0, 0);
  glRotatef(yRot, 0, 1, 0);

  glEnableClientState(
      GL_VERTEX_ARRAY);  // Включение использования массива вершин

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  // glVertexPointer(3, GL_FLOAT, 0, parser.getVertexes().data()); // Указание
  // данных о вершинах
  glVertexPointer(3, GL_FLOAT, 0, vertices);  // Указание данных о вершинах

  glDrawElements(GL_LINES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT,
                 indices);  // Отрисовка линий по индексам

  glDisableClientState(
      GL_VERTEX_ARRAY);  // Отключение использования массива вершин
}

// void glView::triggerRender(QString fileName) {
//   auto& parser = s21::Parser::getInstance();
//   parser.parse(fileName.toStdString());
//   qDebug() << "PROVERKAAA" << fileName;

//   update();

// }

void glView::mousePressEvent(QMouseEvent* mo) {
  mpos = mo->pos();
  xRotLast = xRot;  // сохраняем текущее вращение
  yRotLast = yRot;
}

void glView::mouseMoveEvent(QMouseEvent* mo) {
  float dx = 2 / M_PI * (mo->pos().y() - mpos.y());
  float dy = 2 / M_PI * (mo->pos().x() - mpos.x());
  xRot = xRotLast + dx;
  yRot = yRotLast + dy;
  update();
}

void glView::setController(s21::Controller* controller) {
  this->controller_ = controller;
}
