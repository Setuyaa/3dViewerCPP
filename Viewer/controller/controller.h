#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "../model/model.h"

namespace s21 {
class Controller {
 private:
  ViewerFacade viewer;

 public:
  Controller() {}
  Controller(const Controller &other) = default;
  Controller(Controller &&other) = default;
  ~Controller() {}
  Controller &operator=(const Controller &other) = default;

  int getAmount_vert();
  int getAmount_polygons();

  void move(double sx, double sy, double sz);
  void rotate(double angle, int x, int y, int z);
  void scale(double scale_cur, double scale_prev);
  void parcer(std::string file, int *res);

  int getSizeOfPolygonById(int i);
  int getElementOfPolygonById(int i, int j);

  double getXfromVertexById(int i);
  double getYfromVertexById(int i);
  double getZfromVertexById(int i);
};
}  // namespace s21
#endif  // CONTROLLER_H
