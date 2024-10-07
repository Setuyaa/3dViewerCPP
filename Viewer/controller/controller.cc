#include "controller.h"

#include "../command/command.h"

namespace s21 {
int Controller::getAmount_vert() { return viewer.getAmount_vert(); }
int Controller::getAmount_polygons() { return viewer.getAmount_polygons(); }
void Controller::move(double sx, double sy, double sz) {
  MoveCommand moveCommand(viewer, sx, sy, sz);
  moveCommand.execute();
}
void Controller::rotate(double angle, int x, int y, int z) {
  RotateCommand rotateCommand(viewer, angle, x, y, z);
  rotateCommand.execute();
}
void Controller::scale(double scale_cur, double scale_prev) {
  ScaleCommand scaleCommand(viewer, scale_cur, scale_prev);
  scaleCommand.execute();
}
void Controller::parcer(std::string file, int *res) {
  ParserCommand parserCommand(viewer, file, res);
  parserCommand.execute();
}
int Controller::getSizeOfPolygonById(int i) {
  return viewer.getSizeOfPolygonById(i);
}
int Controller::getElementOfPolygonById(int i, int j) {
  return viewer.getElementOfPolygonById(i, j);
}
double Controller::getXfromVertexById(int i) {
  return viewer.getXfromVertexById(i);
}
double Controller::getYfromVertexById(int i) {
  return viewer.getYfromVertexById(i);
}
double Controller::getZfromVertexById(int i) {
  return viewer.getZfromVertexById(i);
}
}  // namespace s21
