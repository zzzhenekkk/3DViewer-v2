#ifndef VIEW_H
#define VIEW_H

#include <qgifimage.h>

#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QProcess>
#include <QSettings>
#include <QTimer>

#include "../controller/controller.h"
#include "../model/model.h"
#include "glview.h"

#define s21_JPG 0
#define s21_BMP 1

/*!
 * \mainpage
 * \authors turkeysn mutteria sageaure
 * \version 2.0
 * \section intro_sec 3DViewer_v2.0 was done with
 * 1. C++ language \n
 * 2. Qt Creator, Qt
 * 3. Qmake6
 * 4. Doxygen
 */

QT_BEGIN_NAMESPACE
namespace Ui {
class view;
}
QT_END_NAMESPACE

namespace s21 {
/**
 * @brief Структура настроек для s21.
 */
struct s21_sett_ {
  int move_x_ = 0;
  int move_y_ = 0;
  int move_z_ = 0;
  int rotate_x_ = 0;
  int rotate_y_ = 0;
  int rotate_z_ = 0;
  double scale_ = 10.;
};

}  // namespace s21

/**
 * @brief Класс представления для работы с графическим интерфейсом.
 */
class view : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief Конструктор класса view.
   * @param parent Родительский виджет.
   * @param controller Указатель на контроллер.
   */
  view(QWidget *parent = nullptr, s21::Controller *controller = nullptr);
  ~view();

 private slots:
  void on_open_file_clicked();
  void on_move_x__valueChanged(int value);
  void on_rotate_x__valueChanged(int value);
  void on_rotate_y__valueChanged(int value);
  void on_rotate_z__valueChanged(int value);
  void on_move_y__valueChanged(int value);
  void on_move_z__valueChanged(int value);
  void on_scale__valueChanged(int value);
  void on_set_center__clicked();
  void on_background_color__clicked();
  void on_line_color__clicked();
  void on_vertexes_color__clicked();
  void on_central_but__clicked();
  void on_parralel_but__clicked();
  void on_none__clicked();
  void on_square__clicked();
  void on_cicle__clicked();
  void on_size_vertices__valueChanged(int value);
  void on_solid__clicked();
  void on_dotted__clicked();
  void on_line_thickness__valueChanged(int value);
  void on_save_jpg_clicked();
  void on_save_bmp_clicked();
  void on_save_gif_clicked();
  void captureFrame();
  void createGif();

 private:
  void saveSettings(const s21::Setting &settings);
  s21::Setting loadSettings();
  void applySettingsToUI();
  void screen(bool type);

  Ui::view *ui;
  s21::Controller *controller_;
  s21::Model *model_;
  s21::s21_sett_ s21_sett_;
  QColor background_сolor_ = palette().color(QPalette::Window);
  QList<QImage> frames;
};

#endif  // VIEW_H
