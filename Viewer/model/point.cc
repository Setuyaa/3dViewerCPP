#include "model.h"

namespace s21 {
void Point::insertXYZ(double sx, double sy, double sz) {
  x = sx;
  y = sy;
  z = sz;
}
double Point::getX() { return x; }
double Point::getY() { return y; }
double Point::getZ() { return z; }
}  // namespace s21
