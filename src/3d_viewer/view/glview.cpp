#include "glview.h"

glView::glView(QWidget* parent) : QOpenGLWidget(parent) {
  // Инициализация, специфичная для вашего виджета
}

void glView::initializeGL() {
  glEnable(GL_DEPTH_TEST);  // Включение теста глубины
}

void glView::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);  // Настройка видового порта
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

void glView::paintGL() {
  std::vector<float>& vertices = controller_->getVertexes();
  std::vector<unsigned int>& indices = controller_->getPolygons();
  glClearColor(
      setting_.background_color_.redF(), setting_.background_color_.greenF(),
      setting_.background_color_.blueF(), setting_.background_color_.alphaF());

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);  // выбирает текущую матрицу для последующих
                                // операций над матрицами как матрицу проекции.
                                // Это необходимо для настройки перспективы.

  glLoadIdentity();  // загружает единичную матрицу, сбрасывая предыдущие
                     // преобразования, что является хорошей практикой перед
                     // установкой новой проекции.

  if (setting_.type_projection_ == PARALLEL) {
    glOrtho(-1.0, 1.0, -1.0, 1.0, 2, 15);
  } else {
    glFrustum(-1, 1, -1, 1, 2, 15);
  }
  glTranslated(0, 0, -3);
  glRotatef(xRot, 1, 0, 0);
  glRotatef(yRot, 0, 1, 0);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices.data());

  if (setting_.type_vertexes_ != VERTEX_NONE) {
    glColor3f(setting_.vertex_color_.redF(), setting_.vertex_color_.greenF(),
              setting_.vertex_color_.blueF());
    glPointSize(setting_.vertex_thicknes_);
    if (setting_.type_vertexes_ == VERTEX_CIRCLE) {
      glEnable(GL_POINT_SMOOTH);
    } else {
      glDisable(GL_POINT_SMOOTH);
    }
    glDrawArrays(GL_POINTS, 0, vertices.size() / 3);  // v.num_vertex
  }

  glColor3f(setting_.edge_color_.redF(), setting_.edge_color_.greenF(),
            setting_.edge_color_.blueF());

  if (setting_.type_line_ == DASHED) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  }

  glLineWidth(setting_.edge_thicknes_);

  glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT,
                 indices.data());  // Отрисовка линий по индексам
  if (setting_.type_line_ == DASHED) glDisable(GL_LINE_STIPPLE);
  glDisableClientState(GL_VERTEX_ARRAY);
}

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

s21::Setting& glView::getSetting() { return setting_; }

QImage glView::s21_grabFrameBuffer() {
  return grabFramebuffer();  // Этот метод QOpenGLWidget захватывает текущий
                             // кадр как QImage
}
