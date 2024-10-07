#include "myopenglwidget.h"

#include <sstream>

MyOpenGLWidget::MyOpenGLWidget(QWidget* parent) : QOpenGLWidget{parent} {}

MyOpenGLWidget::~MyOpenGLWidget() {}

void MyOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
}

void MyOpenGLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

void MyOpenGLWidget::paintGL() {
  if (!colorBack) {
    glClearColor(0, 0, 0, 0);
  } else if (colorBack == 1) {
    glClearColor(1, 0, 0, 0);
  } else if (colorBack == 2) {
    glClearColor(0, 1, 0, 0);
  } else if (colorBack == 3) {
    glClearColor(0, 0, 1, 0);
  }
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (projection) {
    glFrustum(-1, 1, -1, 1, 7, 12);
    glTranslatef(0, 0, -8);
  } else {
    glOrtho(-1, 1, -1, 1, -1, 1);
  }

  // вывод полигонов
  glLineWidth(sizeEdges);
  if (!viewEdges) {
    glDisable(GL_LINE_STIPPLE);
  } else if (viewEdges == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0x00FF);
  }
  if (!colorEdges) {
    glColor3d(1, 1, 1);
  } else if (colorEdges == 1) {
    glColor3d(1, 0, 0);
  } else if (colorEdges == 2) {
    glColor3d(0, 1, 0);
  } else if (colorEdges == 3) {
    glColor3d(0, 0, 1);
  }
  for (int i = 0; i < controller.getAmount_polygons(); ++i) {
    glBegin(GL_LINE_LOOP);
    for (int j = 0; j < controller.getSizeOfPolygonById(i); ++j) {
      int vertice = controller.getElementOfPolygonById(i, j);
      glVertex3d(controller.getXfromVertexById(vertice - 1),
                 controller.getYfromVertexById(vertice - 1),
                 controller.getZfromVertexById(vertice - 1));
    }
    glEnd();
  }

  // Вывод вершин
  if (controller.getAmount_polygons() != 0) {
    if (viewVertex == 1) {
      glEnable(GL_POINT_SMOOTH);
    } else {
      glDisable(GL_POINT_SMOOTH);
    }
    if (viewVertex) {
      glPointSize(sizeVertex);
      if (!colorVertex) {
        glColor3d(1, 1, 1);
      } else if (colorVertex == 1) {
        glColor3d(1, 0, 0);
      } else if (colorVertex == 2) {
        glColor3d(0, 1, 0);
      } else if (colorVertex == 3) {
        glColor3d(0, 0, 1);
      }
      for (int i = 0; i < controller.getAmount_vert(); ++i) {
        glBegin(GL_POINTS);
        // glVertex3d(controller.viewer.v.getXById(i),
        //           controller.viewer.v.getYById(i),
        //           controller.viewer.v.getZById(i));
        glVertex3d(controller.getXfromVertexById(i),
                   controller.getYfromVertexById(i),
                   controller.getZfromVertexById(i));
        glEnd();
      }
    }
  }
}
int MyOpenGLWidget::getAmount_vert() { return controller.getAmount_vert(); }
int MyOpenGLWidget::getAmount_polygon() {
  return controller.getAmount_polygons();
}
void MyOpenGLWidget::move(double sx, double sy, double sz) {
  controller.move(sx, sy, sz);
}
void MyOpenGLWidget::rotate(double angle, int x, int y, int z) {
  controller.rotate(angle, x, y, z);
}
void MyOpenGLWidget::scale(double scale_cur, double scale_prev) {
  controller.scale(scale_cur, scale_prev);
}
void MyOpenGLWidget::parcer(std::string file, int* res) {
  controller.parcer(file, res);
}

// SETTINGS

bool MyOpenGLWidget::saveBMPImage(const QImage& image,
                                  const QString& filename) {
  bool t = true;
  if (image.isNull() || filename.isNull())
    t = false;
  else
    t = image.save(filename, "BMP");
  return t;
}

bool MyOpenGLWidget::saveJPEGImage(const QImage& image,
                                   const QString& filename) {
  bool t = true;
  if (image.isNull() || filename.isNull())
    t = false;
  else
    t = image.save(filename, "JPEG");
  return t;
}
s21::Memento MyOpenGLWidget::createMemento() { return s21::Memento(&settings); }
void MyOpenGLWidget::setSettings(s21::Settings sets) {
  settings = s21::StateSettings(sets);
}
s21::Settings MyOpenGLWidget::getSettings() { return settings.getSettings(); }
s21::StateSettings Caretaker::loadSettingsFromFile() {
  s21::Settings settings = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  const char* home = std::getenv("HOME");
  std::string path = std::string(home) + "/settings.cfg";
  std::ifstream file(path);
  if (file) {
    std::string line;
    std::getline(file, line);
    std::istringstream iss(line);
    iss >> settings.moveX >> settings.moveY >> settings.moveZ >>
        settings.rotateX >> settings.rotateY >> settings.rotateZ >>
        settings.scale >> settings.projection >> settings.edgesScale >>
        settings.edgesType >> settings.edgesColor >> settings.verticesScale >>
        settings.verticesType >> settings.verticesColor >> settings.bgColor;
  }
  s21::StateSettings state = s21::StateSettings(settings);
  return state;
}

void Caretaker::loadSettingsToFile() {
  const char* home = std::getenv("HOME");
  std::string path = std::string(home) + "/settings.cfg";
  std::ofstream file(path);
  s21::Settings settings = memento_.getState()->getSettings();
  if (file.is_open()) {
    file << settings.moveX << " ";
    file << settings.moveY << " ";
    file << settings.moveZ << " ";
    file << settings.rotateX << " ";
    file << settings.rotateY << " ";
    file << settings.rotateZ << " ";
    file << settings.scale << " ";
    file << settings.projection << " ";
    file << settings.edgesScale << " ";
    file << settings.edgesType << " ";
    file << settings.edgesColor << " ";
    file << settings.verticesScale << " ";
    file << settings.verticesType << " ";
    file << settings.verticesColor << " ";
    file << settings.bgColor << " ";
    file.close();
  }
}

void Caretaker::save(MyOpenGLWidget* originator) {
  memento_ = originator->createMemento();  // получаем текущее состояние
  loadSettingsToFile();  // логика для сохранения сеттинга в файл
}
void Caretaker::restore(MyOpenGLWidget* originator) {
  s21::StateSettings state = loadSettingsFromFile();  // получить инфу из файла
  memento_ = s21::Memento(&state);  // фиксируем состояние
  originator->setSettings(memento_.getState()->getSettings());
}
