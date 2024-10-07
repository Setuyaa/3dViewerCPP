#include "model.h"

namespace s21 {
int ViewerFacade::getAmount_vert() { return v.getAmount_vert(); }
int ViewerFacade::getAmount_polygons() { return p.size(); }
void ViewerFacade::free_data() {
  if (p.size() != 0) {
    for (int i = 0; i < (int)p.size(); i++)
      if (p[i].getSizeById() != 0) p[i].clearPolygon();
    p.clear();
  }
  if (getAmount_vert() != 0) v.clearCoord();
}
int ViewerFacade::getSizeOfPolygonById(int i) { return p[i].getSizeById(); }
int ViewerFacade::getElementOfPolygonById(int i, int j) {
  return p[i].getElementById(j);
}
double ViewerFacade::getXfromVertexById(int i) { return v.getXById(i); }
double ViewerFacade::getYfromVertexById(int i) { return v.getYById(i); }
double ViewerFacade::getZfromVertexById(int i) { return v.getZById(i); }
}  // namespace s21
