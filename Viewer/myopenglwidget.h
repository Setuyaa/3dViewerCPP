#pragma once

#include <QColor>
#include <QMessageBox>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "memento/memento.h"
// #include <fstream>
//  #include <iostream>
#include "controller/controller.h"

#define RGB_MIN 1
#define RGB_MAX 255
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MyOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT
 private:
  s21::StateSettings settings;
  s21::Controller controller;

 public:
  MyOpenGLWidget(QWidget* parent = nullptr);
  ~MyOpenGLWidget();

  void restore(s21::StateSettings* setting);
  s21::Memento createMemento();
  void setSettings(s21::Settings sets);
  s21::Settings getSettings();

  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;
  bool saveBMPImage(const QImage& image, const QString& filename);
  bool saveJPEGImage(const QImage& image, const QString& filename);
  int getAmount_vert();
  int getAmount_polygon();
  void move(double sx, double sy, double sz);
  void rotate(double angle, int x, int y, int z);
  void scale(double scale_cur, double scale_prev);
  void parcer(std::string file, int* res);
  int projection = 0;
  int sizeEdges = 1;
  int viewEdges = 0;
  int colorEdges = 0;
  int sizeVertex = 1;
  int viewVertex = 0;
  int colorVertex = 0;
  int colorBack = 0;
};
class Caretaker {
 public:
  void save(MyOpenGLWidget* originator);
  void restore(MyOpenGLWidget* originator);
  void loadSettingsToFile();
  s21::StateSettings loadSettingsFromFile();

 private:
  s21::Memento memento_;
};
