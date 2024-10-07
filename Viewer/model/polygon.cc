#include "model.h"

namespace s21 {
int Polygon::getSizeById() { return value_p.size(); }
void Polygon::clearPolygon() { value_p.clear(); }
void Polygon::insertP(int p) { value_p.push_back(p); }

int Polygon::getElementById(int i) { return value_p[i]; }
}  // namespace s21
