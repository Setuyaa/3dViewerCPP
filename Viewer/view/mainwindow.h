#pragma once
#include <QFileDialog>
#include <QFileInfo>
#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>

#include "QtGifImage/gifimage/qgifimage.h"
// #include "controller.h"
#include "../myopenglwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  QString filenameGIF;
  Caretaker careTaker;
  // s21::Controller *controller;

 protected:
  void saveSettings();
  void loadSettings();
  s21::Settings getSettingsFromUI();

 private:
  int deltaX = 0;
  int deltaY = 0;
  int deltaZ = 0;
  int deltaRX = 0;
  int deltaRY = 0;
  int deltaRZ = 0;
  int deltaS = 0;
  void setupUIConnections();
  void setupUIMovingsXYZ();
  void setupUIRotatingXYZ();
  void setupUIScaleProjection();
  void setupUIScaleEdges();
  void setupUIScaleVertices();
  void setupUIScaleFile();
  void setupUIScaleCommon();

  void applySettingsToUI(const s21::Settings &settings);
  void resetView();
  void movedX();
  void movedY();
  void movedZ();
  void rotatedX();
  void rotatedY();
  void rotatedZ();
  void scaled();
  void projectionChanged();
  void edgesScaled();
  void edgesType();
  void edgesColor();
  void verticesScaled();
  void verticesType();
  void verticesColor();
  void backgroundColor();
  void saveBMP();
  void saveJPEG();
  void saveGIF();
  void frameGIF();
  void startGIFAnimation(const QString &filename);
  bool saveImage(const QImage &image, const QString &filename);
  void quitApp();
  void openOBJ();

  int startTime = 0;
  int stopTime = 100;
  float saveTime = 0;
  const int fps = 10;
  const int gifLength = 5;

  QTimer *timer;
  QGifImage *gif;

  Ui::MainWindow *ui;
};
