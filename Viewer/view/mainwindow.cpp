#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setupUIConnections();
  loadSettings();
}
void MainWindow::setupUIConnections() {
  setupUIMovingsXYZ();
  setupUIRotatingXYZ();
  setupUIScaleProjection();
  setupUIScaleEdges();
  setupUIScaleVertices();
  setupUIScaleFile();
  setupUIScaleCommon();
}
void MainWindow::setupUIMovingsXYZ() {
  connect(ui->spinBoxMoveX,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          ui->horizontalSliderMoveX, &QSlider::setValue);
  connect(ui->horizontalSliderMoveX,
          static_cast<void (QSlider::*)(int)>(&QSlider::valueChanged),
          ui->spinBoxMoveX, &QSpinBox::setValue);
  connect(ui->horizontalSliderMoveX, &QSlider::valueChanged, this,
          &MainWindow::movedX);

  connect(ui->spinBoxMoveY,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          ui->horizontalSliderMoveY, &QSlider::setValue);
  connect(ui->horizontalSliderMoveY,
          static_cast<void (QSlider::*)(int)>(&QSlider::valueChanged),
          ui->spinBoxMoveY, &QSpinBox::setValue);
  connect(ui->horizontalSliderMoveY, &QSlider::valueChanged, this,
          &MainWindow::movedY);

  connect(ui->spinBoxMoveZ,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          ui->horizontalSliderMoveZ, &QSlider::setValue);
  connect(ui->horizontalSliderMoveZ,
          static_cast<void (QSlider::*)(int)>(&QSlider::valueChanged),
          ui->spinBoxMoveZ, &QSpinBox::setValue);
  connect(ui->horizontalSliderMoveZ, &QSlider::valueChanged, this,
          &MainWindow::movedZ);
}
void MainWindow::setupUIRotatingXYZ() {
  connect(ui->spinBoxRotateX,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          ui->horizontalSliderRotateX, &QSlider::setValue);
  connect(ui->horizontalSliderRotateX,
          static_cast<void (QSlider::*)(int)>(&QSlider::valueChanged),
          ui->spinBoxRotateX, &QSpinBox::setValue);
  connect(ui->horizontalSliderRotateX, &QSlider::valueChanged, this,
          &MainWindow::rotatedX);

  connect(ui->spinBoxRotateY,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          ui->horizontalSliderRotateY, &QSlider::setValue);
  connect(ui->horizontalSliderRotateY,
          static_cast<void (QSlider::*)(int)>(&QSlider::valueChanged),
          ui->spinBoxRotateY, &QSpinBox::setValue);
  connect(ui->horizontalSliderRotateY, &QSlider::valueChanged, this,
          &MainWindow::rotatedY);

  connect(ui->spinBoxRotateZ,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          ui->horizontalSliderRotateZ, &QSlider::setValue);
  connect(ui->horizontalSliderRotateZ,
          static_cast<void (QSlider::*)(int)>(&QSlider::valueChanged),
          ui->spinBoxRotateZ, &QSpinBox::setValue);
  connect(ui->horizontalSliderRotateZ, &QSlider::valueChanged, this,
          &MainWindow::rotatedZ);
}
void MainWindow::setupUIScaleProjection() {
  connect(ui->spinBoxScale,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          ui->horizontalSliderScale, &QSlider::setValue);
  connect(ui->horizontalSliderScale,
          static_cast<void (QSlider::*)(int)>(&QSlider::valueChanged),
          ui->spinBoxScale, &QSpinBox::setValue);
  connect(ui->horizontalSliderScale, &QSlider::valueChanged, this,
          &MainWindow::scaled);

  connect(ui->projectionComboBox, &QComboBox::currentIndexChanged, this,
          &MainWindow::projectionChanged);
}
void MainWindow::setupUIScaleEdges() {
  connect(ui->edgesSpinBoxScale,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          ui->edgesSliderScale, &QSlider::setValue);
  connect(ui->edgesSliderScale,
          static_cast<void (QSlider::*)(int)>(&QSlider::valueChanged),
          ui->edgesSpinBoxScale, &QSpinBox::setValue);
  connect(ui->edgesSliderScale, &QSlider::valueChanged, this,
          &MainWindow::edgesScaled);
  connect(ui->edgesTypeComboBox, &QComboBox::currentIndexChanged, this,
          &MainWindow::edgesType);
  connect(ui->edgesColorComboBox, &QComboBox::currentIndexChanged, this,
          &MainWindow::edgesColor);
}
void MainWindow::setupUIScaleVertices() {
  connect(ui->verticesSpinBoxScale,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          ui->verticesSliderScale, &QSlider::setValue);
  connect(ui->verticesSliderScale,
          static_cast<void (QSlider::*)(int)>(&QSlider::valueChanged),
          ui->verticesSpinBoxScale, &QSpinBox::setValue);
  connect(ui->verticesSliderScale, &QSlider::valueChanged, this,
          &MainWindow::verticesScaled);

  connect(ui->verticesTypeComboBox, &QComboBox::currentIndexChanged, this,
          &MainWindow::verticesType);
  connect(ui->verticesColorComboBox, &QComboBox::currentIndexChanged, this,
          &MainWindow::verticesColor);
}

void MainWindow::setupUIScaleFile() {
  connect(ui->bmpButton, &QAbstractButton::clicked, this, &MainWindow::saveBMP);

  connect(ui->jpegButton, &QAbstractButton::clicked, this,
          &MainWindow::saveJPEG);
  connect(ui->gifButton, &QAbstractButton::clicked, this, &MainWindow::saveGIF);
  connect(ui->openFileButton, &QAbstractButton::clicked, this,
          &MainWindow::openOBJ);
}
void MainWindow::setupUIScaleCommon() {
  connect(ui->backgroundColorComboBox, &QComboBox::currentIndexChanged, this,
          &MainWindow::backgroundColor);

  connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::quitApp);
}

MainWindow::~MainWindow() {
  saveSettings();
  delete ui;
}

void MainWindow::saveSettings() {
  s21::Settings settings = getSettingsFromUI();
  ui->widget->setSettings(settings);
  careTaker.save(ui->widget);
}
s21::Settings MainWindow::getSettingsFromUI() {
  s21::Settings settings = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  settings.moveX = ui->spinBoxMoveX->value();
  settings.moveY = ui->spinBoxMoveY->value();
  settings.moveZ = ui->spinBoxMoveZ->value();
  settings.rotateX = ui->spinBoxRotateX->value();
  settings.rotateY = ui->spinBoxRotateY->value();
  settings.rotateZ = ui->spinBoxRotateZ->value();
  settings.scale = ui->spinBoxScale->value();
  settings.projection = ui->projectionComboBox->currentIndex();
  settings.edgesScale = ui->edgesSpinBoxScale->value();
  settings.edgesType = ui->edgesTypeComboBox->currentIndex();
  settings.edgesColor = ui->edgesColorComboBox->currentIndex();
  settings.verticesScale = ui->verticesSpinBoxScale->value();
  settings.verticesType = ui->verticesTypeComboBox->currentIndex();
  settings.verticesColor = ui->verticesColorComboBox->currentIndex();
  settings.bgColor = ui->backgroundColorComboBox->currentIndex();
  return settings;
}

void MainWindow::applySettingsToUI(const s21::Settings& settings) {
  ui->spinBoxMoveX->setValue(settings.moveX);
  ui->spinBoxMoveY->setValue(settings.moveY);
  ui->spinBoxMoveZ->setValue(settings.moveZ);
  ui->spinBoxRotateX->setValue(settings.rotateX);
  ui->spinBoxRotateY->setValue(settings.rotateY);
  ui->spinBoxRotateZ->setValue(settings.rotateZ);
  ui->spinBoxScale->setValue(settings.scale);
  ui->projectionComboBox->setCurrentIndex(settings.projection);
  ui->edgesSpinBoxScale->setValue(settings.edgesScale);
  ui->edgesTypeComboBox->setCurrentIndex(settings.edgesType);
  ui->edgesColorComboBox->setCurrentIndex(settings.edgesColor);
  ui->verticesSpinBoxScale->setValue(settings.verticesScale);
  ui->verticesTypeComboBox->setCurrentIndex(settings.verticesType);
  ui->verticesColorComboBox->setCurrentIndex(settings.verticesColor);
  ui->backgroundColorComboBox->setCurrentIndex(settings.bgColor);
}

void MainWindow::loadSettings() {
  careTaker.restore(ui->widget);
  applySettingsToUI(ui->widget->getSettings());
}

void MainWindow::resetView() {
  ui->widget->viewVertex = 0;
  ui->spinBoxMoveX->setValue(0);
  ui->spinBoxMoveY->setValue(0);
  ui->spinBoxMoveZ->setValue(0);
  ui->spinBoxRotateX->setValue(0);
  ui->spinBoxRotateY->setValue(0);
  ui->spinBoxRotateZ->setValue(0);
  ui->spinBoxScale->setValue(0);
  ui->projectionComboBox->setCurrentIndex(0);
  ui->edgesSpinBoxScale->setValue(1);
  ui->edgesTypeComboBox->setCurrentIndex(0);
  ui->edgesColorComboBox->setCurrentIndex(0);
  ui->verticesSpinBoxScale->setValue(1);
  ui->verticesTypeComboBox->setCurrentIndex(0);
  ui->verticesColorComboBox->setCurrentIndex(0);
  ui->backgroundColorComboBox->setCurrentIndex(0);
}

void MainWindow::quitApp() { close(); }

void MainWindow::movedX() {
  int delta = ui->horizontalSliderMoveX->value() - deltaX;
  deltaX = ui->horizontalSliderMoveX->value();
  ui->widget->move((double)delta / 100.0f, 0, 0);
  ui->widget->update();
}

void MainWindow::movedY() {
  int delta = ui->horizontalSliderMoveY->value() - deltaY;
  deltaY = ui->horizontalSliderMoveY->value();
  ui->widget->move(0, (double)delta / 100.0f, 0);
  ui->widget->update();
}

void MainWindow::movedZ() {
  int delta = ui->horizontalSliderMoveZ->value() - deltaZ;
  deltaZ = ui->horizontalSliderMoveZ->value();
  ui->widget->move(0, 0, (double)delta / 100.0f);
  ui->widget->update();
}

void MainWindow::rotatedX() {
  int delta = ui->horizontalSliderRotateX->value() - deltaRX;
  deltaRX = ui->horizontalSliderRotateX->value();
  ui->widget->rotate(delta, 1, 0, 0);
  ui->widget->update();
}

void MainWindow::rotatedY() {
  int delta = ui->horizontalSliderRotateY->value() - deltaRY;
  deltaRY = ui->horizontalSliderRotateY->value();
  ui->widget->rotate(delta, 0, 1, 0);
  ui->widget->update();
}

void MainWindow::rotatedZ() {
  int delta = ui->horizontalSliderRotateZ->value() - deltaRZ;
  deltaRZ = ui->horizontalSliderRotateZ->value();
  ui->widget->rotate(delta, 0, 0, 1);
  ui->widget->update();
}

void MainWindow::scaled() {
  int delta = ui->horizontalSliderScale->value() - deltaS;
  deltaS = ui->horizontalSliderScale->value();
  if (delta > 0) {
    ui->widget->scale(1 + (double)delta / 100.0f, 1);
  } else {
    ui->widget->scale(1, 1 - (double)delta / 100.0f);
  }
  ui->widget->update();
}

void MainWindow::projectionChanged() {
  ui->widget->projection = ui->projectionComboBox->currentIndex();
  ui->widget->update();
}

void MainWindow::edgesScaled() {
  ui->widget->sizeEdges = ui->edgesSliderScale->value();
  ui->widget->update();
}

void MainWindow::edgesType() {
  ui->widget->viewEdges = ui->edgesTypeComboBox->currentIndex();
  ui->widget->update();
}

void MainWindow::edgesColor() {
  ui->widget->colorEdges = ui->edgesColorComboBox->currentIndex();
  ui->widget->update();
}

void MainWindow::verticesScaled() {
  ui->widget->sizeVertex = ui->verticesSliderScale->value();
  ui->widget->update();
}

void MainWindow::verticesType() {
  ui->widget->viewVertex = ui->verticesTypeComboBox->currentIndex();
  ui->widget->update();
}

void MainWindow::verticesColor() {
  ui->widget->colorVertex = ui->verticesColorComboBox->currentIndex();
  ui->widget->update();
}

void MainWindow::backgroundColor() {
  ui->widget->colorBack = ui->backgroundColorComboBox->currentIndex();
  ui->widget->update();
}
void MainWindow::saveBMP() {
  QString filename =
      QFileDialog::getSaveFileName(this, "Save file", nullptr, "Image(*.bmp)");
  if (!filename.isEmpty()) {
    QImage image = ui->widget->grabFramebuffer();
    if (ui->widget->saveBMPImage(image, filename)) {
      QMessageBox::information(nullptr, "Successfully saved file",
                               "Successfully saved file");
    } else {
      QMessageBox::information(nullptr, "File error", "Couldn'tsave file");
    }
  }
}

void MainWindow::saveJPEG() {
  QString filename =
      QFileDialog::getSaveFileName(this, "Save file", nullptr, "Image(*.jpeg)");
  if (!filename.isEmpty()) {
    QImage image = ui->widget->grabFramebuffer();
    if (ui->widget->saveJPEGImage(image, filename)) {
      QMessageBox::information(nullptr, "Successfully saved file",
                               "Successfully saved file");
    } else {
      QMessageBox::information(nullptr, "File error", "Couldn'tsave file");
    }
  }
}

void MainWindow::saveGIF() {
  filenameGIF =
      QFileDialog::getSaveFileName(this, "Save file", nullptr, "Image(*.gif)");
  if (!filenameGIF.isNull()) {
    startGIFAnimation(filenameGIF);
  }
  ui->gifButton->setEnabled(false);
}

void MainWindow::startGIFAnimation(const QString& filename) {
  ui->widget->grabFramebuffer().save(filename, "gif");
  gif = new QGifImage;
  gif->setDefaultDelay(1000 / fps);
  startTime = 0;
  stopTime = 1000 / fps;
  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &MainWindow::frameGIF);
  timer->start(1000 / fps);
}

void MainWindow::frameGIF() {
  if (startTime == stopTime) {
    QPixmap pic = QPixmap::fromImage(ui->widget->grabFramebuffer());
    QPixmap scaledPic = pic.scaled(QSize(640, 480), Qt::KeepAspectRatio,
                                   Qt::SmoothTransformation);
    gif->addFrame(scaledPic.toImage(), 1000 / fps);
    saveTime = (float)startTime * 1e-3;
    stopTime += 1000 / fps;
  }
  if (startTime == 1000 * gifLength) {
    gif->save(filenameGIF);
    timer->stop();

    disconnect(timer, &QTimer::timeout, this, &MainWindow::frameGIF);

    delete gif;
    delete timer;

    ui->gifButton->setEnabled(true);
  }
  startTime += 1000 / fps;
}

void MainWindow::openOBJ() {
  QString filename = QFileDialog::getOpenFileName(
      this, "Choose file", QDir::currentPath(), ".obj (*.obj)");
  if (!filename.isEmpty()) {
    int res = SUCCESS;
    ui->widget->parcer(filename.toStdString(), &res);
    if (res != FAILURE) {
      QFileInfo fname(filename);
      ui->filenameLabel->setText(fname.fileName());
      ui->verticesLabel->setText(QString::number(ui->widget->getAmount_vert()));
      ui->edgesLabel->setText(QString::number(ui->widget->getAmount_polygon()));
      deltaX = 0;
      deltaY = 0;
      deltaZ = 0;
      deltaRX = 0;
      deltaRY = 0;
      deltaRZ = 0;
      deltaS = 0;
      if (ui->checkResetted->isChecked()) {
        resetView();
      } else {
        movedX();
        movedY();
        movedZ();
        rotatedX();
        rotatedY();
        rotatedZ();
        scaled();
        projectionChanged();
        edgesScaled();
        edgesType();
        edgesColor();
        verticesScaled();
        verticesType();
        verticesColor();
        backgroundColor();
      }
    } else {
      QMessageBox::information(nullptr, "File error",
                               "Model file has been read with an error.");
    }
  }
}
