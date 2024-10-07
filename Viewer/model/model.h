#ifndef MODEL_H
#define MODEL_H

#include <fstream>
#include <vector>

namespace s21 {
#define SUCCESS 0
#define FAILURE 2
#define eps 1e-7
#define PI 3.14159265358979323846

class Point {
 private:
  double x, y, z;

 public:
  Point() {}
  Point(const Point &other) = default;
  Point(Point &&other) = default;
  ~Point() {}
  void insertXYZ(double x, double y, double z);
  double getX();
  double getY();
  double getZ();
};

class Vertex {
 private:
  std::vector<Point> coord;
  double MinMax_X[2];
  double MinMax_Y[2];
  double MinMax_Z[2];

 public:
  Vertex() {}
  Vertex(const Vertex &other) = default;
  ~Vertex() {}

  void insertMinMaxX(double min, double max);
  void insertMinMaxY(double min, double max);
  void insertMinMaxZ(double min, double max);

  int getAmount_vert();
  void clearCoord();
  void pushBackPoint(Point point);
  Point getPointById(int i);
  double getCentreX();
  double getCentreY();
  double getCentreZ();

  void changeXYZ(int i, double x, double y, double z);
  void insertXYZ(double x, double y, double z);
  double getXById(int i);
  double getYById(int i);
  double getZById(int i);

  double getDiffMinMaxX();
  double getDiffMinMaxY();
  double getDiffMinMaxZ();
};

struct Polygon {
 private:
  std::vector<int> value_p;

 public:
 public:
  Polygon() {}
  Polygon(const Polygon &other) = default;
  Polygon(Polygon &&other) = default;
  ~Polygon() {}
  void insertP(int p);

  int getSizeById();
  void clearPolygon();
  int getElementById(int i);
};

class ViewerFacade {
 private:
  Vertex v;
  std::vector<Polygon> p;

  int parser(std::ifstream &fp);
  int parcer_line_v(std::string line_with_v);
  int parcer_line_f(std::string line_with_f, Polygon *polygon);
  void free_data();

  void min_max_X();
  void min_max_Y();
  void min_max_Z();

  void normalize();
  void matrix_transformation(double transformation_matrix[][4], double *vector,
                             int i);

 public:
  ViewerFacade() {}
  ViewerFacade(const ViewerFacade &other) = default;
  ViewerFacade(ViewerFacade &&other) = default;
  ~ViewerFacade() {}
  ViewerFacade &operator=(const ViewerFacade &other) = default;

  void main_parcer(std::string &file, int *res);

  void s21_move(double sx, double sy, double sz);
  void s21_scale(double scale_cur, double scale_prev);
  void s21_rotate(double angle, int x, int y, int z);

  int getAmount_vert();
  int getAmount_polygons();

  int getSizeOfPolygonById(int i);
  int getElementOfPolygonById(int i, int j);

  double getXfromVertexById(int i);
  double getYfromVertexById(int i);
  double getZfromVertexById(int i);
};

}  // namespace s21
#endif  // MODEL_H
