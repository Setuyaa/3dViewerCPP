#include "model.h"

namespace s21 {
void Vertex::insertMinMaxX(double min, double max) {
  MinMax_X[0] = min;
  MinMax_X[1] = max;
}
void Vertex::insertMinMaxY(double min, double max) {
  MinMax_Y[0] = min;
  MinMax_Y[1] = max;
}

void Vertex::insertMinMaxZ(double min, double max) {
  MinMax_Z[0] = min;
  MinMax_Z[1] = max;
}

int Vertex::getAmount_vert() { return coord.size(); }
void Vertex::clearCoord() { coord.clear(); }
void Vertex::pushBackPoint(Point point) { coord.push_back(point); }
Point Vertex::getPointById(int i) { return coord[i]; }
double Vertex::getCentreX() {
  return MinMax_X[0] + (MinMax_X[1] - MinMax_X[0]) / 2;
}
double Vertex::getCentreY() {
  return MinMax_Y[0] + (MinMax_Y[1] - MinMax_Y[0]) / 2;
}
double Vertex::getCentreZ() {
  return MinMax_Z[0] + (MinMax_Z[1] - MinMax_Z[0]) / 2;
}

void Vertex::changeXYZ(int i, double x, double y, double z) {
  coord[i].insertXYZ(x, y, z);
}
double Vertex::getXById(int i) { return coord[i].getX(); }
double Vertex::getYById(int i) { return coord[i].getY(); }
double Vertex::getZById(int i) { return coord[i].getZ(); }
double Vertex::getDiffMinMaxX() { return MinMax_X[1] - MinMax_X[0]; }
double Vertex::getDiffMinMaxY() { return MinMax_Y[1] - MinMax_Y[0]; }
double Vertex::getDiffMinMaxZ() { return MinMax_Z[1] - MinMax_Z[0]; }
}  // namespace s21
