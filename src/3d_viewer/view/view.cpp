#include "view.h"

#include "ui_view.h"

view::view(QWidget *parent, s21::Controller *controller)
    : QMainWindow(parent), ui(new Ui::view), controller_(controller) {
  ui->setupUi(this);
  ui->openGLWidget->setController(controller_);
  controller_->setView(this);

  ui->openGLWidget->getSetting().background_color_ = background_сolor_;
  ui->openGLWidget->getSetting() = loadSettings();
  applySettingsToUI();
}

view::~view() {
  saveSettings(ui->openGLWidget->getSetting());
  delete ui;
}

void view::on_open_file_clicked() {
  QString file_path = QFileDialog::getOpenFileName(
      this, tr("Open OBJ File"), QDir::homePath(), tr("OBJ Files (*.obj)"));

  if (!file_path.isEmpty()) {
    bool status = controller_->loadModel(file_path.toStdString());

    if (!status) {
      QMessageBox::information(this, tr("Некорректные данные в модели"),
                               tr("Некорректные данные в модели!!!"));
      controller_->clearModel();
      // return;
    }

    ui->path_file_->setText(file_path);
    QFileInfo fileInfo(file_path);
    QString file_name = fileInfo.fileName();
    ui->file_name_->setText(file_name);
    ui->count_edges_->setText(QString::number(controller_->getCountEdges()));
    ui->count_polygons_->setText(
        QString::number(controller_->getCountPolygons()));
    ui->count_vertexes_->setText(
        QString::number(controller_->getCountVertexes()));
  }
}

void view::on_move_x__valueChanged(int value) {
  controller_->moveModel((s21_sett_.move_x_ - value) / 50.0, 0, 0);
  s21_sett_.move_x_ = value;
  ui->openGLWidget->update();
}

void view::on_rotate_x__valueChanged(int value) {
  qDebug() << "The value is:" << s21_sett_.rotate_x_ - value << value;
  controller_->rotateModelX((s21_sett_.rotate_x_ - value) / 20.);
  s21_sett_.rotate_x_ = value;
  ui->openGLWidget->update();
}

void view::on_rotate_y__valueChanged(int value) {
  qDebug() << "The value is:" << s21_sett_.rotate_y_ - value << value;
  controller_->rotateModelY((s21_sett_.rotate_y_ - value) / 20.);
  s21_sett_.rotate_y_ = value;
  ui->openGLWidget->update();
}

void view::on_rotate_z__valueChanged(int value) {
  qDebug() << "The value is:" << s21_sett_.rotate_z_ - value << value;
  controller_->rotateModelZ((s21_sett_.rotate_z_ - value) / 20.);
  s21_sett_.rotate_z_ = value;
  ui->openGLWidget->update();
}

void view::on_move_y__valueChanged(int value) {
  controller_->moveModel(0, (s21_sett_.move_y_ - value) / 50.0, 0);
  s21_sett_.move_y_ = value;
  ui->openGLWidget->update();
}

void view::on_move_z__valueChanged(int value) {
  controller_->moveModel(0, 0, (s21_sett_.move_z_ - value) / 50.0);
  s21_sett_.move_z_ = value;
  ui->openGLWidget->update();
}

void view::on_scale__valueChanged(int value) {
  controller_->changeScale(value / s21_sett_.scale_);
  s21_sett_.scale_ = value;
  ui->openGLWidget->update();
}

void view::on_set_center__clicked() {
  ui->move_x_->setValue(0.);
  ui->move_y_->setValue(0.);
  ui->move_z_->setValue(0.);
  ui->rotate_x_->setValue(0.);
  ui->rotate_y_->setValue(0.);
  ui->rotate_z_->setValue(0.);
  ui->scale_->setValue(10.);
  s21_sett_ = {};
  if (!ui->path_file_->text().isEmpty())
    controller_->loadModel(ui->path_file_->text().toStdString());
  ui->openGLWidget->update();
}

void view::on_background_color__clicked() {
  ui->openGLWidget->getSetting().background_color_ =
      QColorDialog::getColor(Qt::white, this, "Выберите цвет фона");
  ui->openGLWidget->update();
}

void view::on_line_color__clicked() {
  ui->openGLWidget->getSetting().edge_color_ =
      QColorDialog::getColor(Qt::white, this, "Выберите цвет фона");
  ui->openGLWidget->update();
}

void view::on_vertexes_color__clicked() {
  ui->openGLWidget->getSetting().vertex_color_ =
      QColorDialog::getColor(Qt::white, this, "Выберите цвет фона");
  ui->openGLWidget->update();
}

void view::on_central_but__clicked() {
  ui->openGLWidget->getSetting().type_projection_ = CENTRAL;
  ui->openGLWidget->update();
}

void view::on_parralel_but__clicked() {
  ui->openGLWidget->getSetting().type_projection_ = PARALLEL;
  ui->openGLWidget->update();
}

void view::on_none__clicked() {
  ui->openGLWidget->getSetting().type_vertexes_ = VERTEX_NONE;
  ui->openGLWidget->update();
}

void view::on_square__clicked() {
  ui->openGLWidget->getSetting().type_vertexes_ = VERTEX_SQUARE;
  ui->openGLWidget->update();
}

void view::on_cicle__clicked() {
  ui->openGLWidget->getSetting().type_vertexes_ = VERTEX_CIRCLE;
  ui->openGLWidget->update();
}

void view::on_size_vertices__valueChanged(int value) {
  ui->openGLWidget->getSetting().vertex_thicknes_ = value;
  ui->openGLWidget->update();
}

void view::on_solid__clicked() {
  ui->openGLWidget->getSetting().type_line_ = SOLID;
  ui->openGLWidget->update();
}

void view::on_dotted__clicked() {
  ui->openGLWidget->getSetting().type_line_ = DASHED;
  ui->openGLWidget->update();
}

void view::on_line_thickness__valueChanged(int value) {
  ui->openGLWidget->getSetting().edge_thicknes_ = value / 10.;
  ui->openGLWidget->update();
}

void view::saveSettings(const s21::Setting &settings) {
  QSettings appSettings("YourOrganization", "YourApplication");

  appSettings.setValue("background_color", settings.background_color_.name());
  appSettings.setValue("vertex_color", settings.vertex_color_.name());
  appSettings.setValue("edge_color", settings.edge_color_.name());
  appSettings.setValue("type_vertexes", settings.type_vertexes_);
  appSettings.setValue("type_projection", settings.type_projection_);
  appSettings.setValue("type_line", settings.type_line_);
  appSettings.setValue("vertex_thickness", settings.vertex_thicknes_);
  appSettings.setValue("edge_thickness", settings.edge_thicknes_);
}

s21::Setting view::loadSettings() {
  QSettings appSettings("YourOrganization", "YourApplication");
  s21::Setting settings;
  settings.background_color_ =
      QColor(appSettings.value("background_color", QColor(Qt::black).name())
                 .toString());
  settings.vertex_color_ = QColor(
      appSettings.value("vertex_color", QColor(Qt::white).name()).toString());
  settings.edge_color_ = QColor(
      appSettings.value("edge_color", QColor(Qt::white).name()).toString());
  settings.type_vertexes_ =
      appSettings.value("type_vertexes", VERTEX_NONE).toInt();
  settings.type_projection_ =
      appSettings.value("type_projection", CENTRAL).toInt();
  settings.type_line_ = appSettings.value("type_line", SOLID).toInt();
  settings.vertex_thicknes_ =
      appSettings.value("vertex_thickness", 0.5).toFloat();
  settings.edge_thicknes_ = appSettings.value("edge_thickness", 0.5).toFloat();
  return settings;
}

void view::applySettingsToUI() {
  if (ui->openGLWidget->getSetting().type_projection_ == PARALLEL)
    ui->parralel_but_->setChecked(1);
  if (ui->openGLWidget->getSetting().type_line_ == DASHED)
    ui->dotted_->setChecked(1);
  ui->line_thickness_->setValue(ui->openGLWidget->getSetting().edge_thicknes_ *
                                10);
  if (ui->openGLWidget->getSetting().type_vertexes_ == VERTEX_CIRCLE)
    ui->cicle_->setChecked(1);
  if (ui->openGLWidget->getSetting().type_vertexes_ == VERTEX_SQUARE)
    ui->square_->setChecked(1);
  ui->size_vertices_->setValue(ui->openGLWidget->getSetting().vertex_thicknes_);
}

void view::on_save_jpg_clicked() { screen(s21_JPG); }

void view::screen(bool type) {
  if (!ui->path_file_->text().isEmpty()) {
    QImage qimage = ui->openGLWidget->grabFramebuffer();
    QString filePath = ui->path_file_->text();
    QFileInfo fileInfo(filePath);
    QDir directory = fileInfo.dir();
    QString directoryPath = directory.absolutePath();
    QString baseName = fileInfo.baseName();
    QString newFilePath =
        directoryPath + "/" + baseName + (type == s21_JPG ? ".jpg" : ".bmp");
    if (qimage.save(newFilePath)) {
      QMessageBox::information(this, tr("Сохранение файла"),
                               tr("Изображение сохранено в папке с моделью."));
    } else {
      QMessageBox::warning(
          this, tr("Ошибка сохранения"),
          tr("Не удалось сохранить изоражение. Проверьте права "
             "для записи в папке с моделью"));
    }
  } else {
    QMessageBox::warning(this, tr("Ошибка"),
                         tr("Не выбрана модель для рендеринга"));
    return;
  }
}

void view::on_save_bmp_clicked() { screen(s21_BMP); }

void view::on_save_gif_clicked() {
  if (ui->path_file_->text().isEmpty()) {
    QMessageBox::information(this, tr("Alert"),
                             tr("Вы не загрузили модель для демонстрации"));
    return;
  }

  auto reply = QMessageBox::information(
      this, tr("Alert"),
      tr("Будут записаны все действия с моделью в течении 5 секунд."),
      QMessageBox::Ok | QMessageBox::Cancel);

  if (reply == QMessageBox::Ok) {
    frames.clear();  // Очищаем предыдущие кадры

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &view::captureFrame);
    timer->start(100);  // Захват кадра каждые 100 мс

    QTimer::singleShot(5000, this, [this, timer]() {
      timer->stop();
      createGif();
    });
  }
}

void view::createGif() {
  QGifImage gif(QSize(640, 480));
  gif.setDefaultDelay(100);

  for (const QImage &frame : std::as_const(frames)) {
    gif.addFrame(frame);
  }

  QFileInfo fileInfo(ui->path_file_->text());
  QString directory = fileInfo.absolutePath();  // Получаем директорию файла
  QString baseName =
      fileInfo.baseName();  // Получаем базовое имя файла без расширения
  QString newFilePath = directory + "/" + baseName + ".gif";
  // Создаем новый путь с тем же базовым именем, но с расширением .jpg

  bool success = gif.save(newFilePath);
  if (!success) {
    // Обработка ошибки
    QMessageBox::warning(this, tr("Ошибка"),
                         tr("Не удалось сохранить анимацию."));
  } else {
    QMessageBox::information(this, tr("Успех!"),
                             tr("Анимация сохранена в папке с моделью."));
  }
}

void view::captureFrame() {
  QImage frame = ui->openGLWidget->grabFramebuffer();
  QImage scaledFrame =
      frame.scaled(640, 480, Qt::KeepAspectRatio, Qt::SmoothTransformation);
  frames.push_back(scaledFrame);
}
