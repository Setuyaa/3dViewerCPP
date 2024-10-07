#include <iostream>
#include <sstream>

#include "model.h"

namespace s21 {
void ViewerFacade::main_parcer(std::string &file, int *res) {
  free_data();
  int result = SUCCESS;
  std::ifstream fp(file);
  if (fp) {
    result = parser(fp);
    fp.close();
  } else {
    std::cerr << "No such file";
    result = FAILURE;
  }
  *res = result;
}
int ViewerFacade::parser(std::ifstream &fp) {
  int result = SUCCESS;
  std::string line;

  while (result != FAILURE && std::getline(fp, line)) {
    if (line.rfind("v ", 0) == 0) {
      result = parcer_line_v(line);
    } else if (line.rfind("f ", 0) == 0) {
      Polygon polygon;
      result = parcer_line_f(line, &polygon);
      if (result != FAILURE) {
        p.push_back(polygon);
      }
    }
  }
  if (result != FAILURE) {
    min_max_X();
    min_max_Y();
    min_max_Z();
    normalize();
  }
  return result;
}

int ViewerFacade::parcer_line_v(const std::string line_with_v) {
  std::istringstream iss(line_with_v);
  std::string token;

  if (!(iss >> token) || token != "v") {
    return FAILURE;
  }
  Point point;
  double x;
  double y;
  double z;
  if (!(iss >> x) || !(iss >> y) || !(iss >> z)) {
    return FAILURE;
  }
  point.insertXYZ(x, y, z);
  v.pushBackPoint(point);
  return SUCCESS;
}
int ViewerFacade::parcer_line_f(std::string line_with_f, Polygon *polygon) {
  int result = SUCCESS;

  std::istringstream iss(line_with_f);
  std::string istr;

  iss >> istr;

  while (iss >> istr) {
    try {
      int value = std::stoi(istr);
      if (value > v.getAmount_vert()) {
        result = FAILURE;
        break;
      }
      polygon->insertP(value);
      // polygon->amount_p++;
    } catch (const std::invalid_argument &) {
      result = FAILURE;
      break;
    }
  }

  return result;
}
void ViewerFacade::min_max_X() {
  Point check = v.getPointById(0);

  double min = check.getX();
  double max = check.getX();
  for (int i = 1; i < v.getAmount_vert(); i++) {
    Point temp = v.getPointById(i);
    if (temp.getX() < min) {
      min = temp.getX();
    }
    if (temp.getX() > max) {
      max = temp.getX();
    }
  }
  v.insertMinMaxX(min, max);
}

void ViewerFacade::min_max_Y() {
  Point check = v.getPointById(0);
  double min = check.getY();
  double max = check.getY();
  for (int i = 1; i < v.getAmount_vert(); i++) {
    Point temp = v.getPointById(i);
    if (temp.getY() < min) {
      min = temp.getY();
    }
    if (temp.getY() > max) {
      max = temp.getY();
    }
  }
  v.insertMinMaxY(min, max);
}

void ViewerFacade::min_max_Z() {
  Point check = v.getPointById(0);
  double min = check.getZ();
  double max = check.getZ();
  for (int i = 1; i < v.getAmount_vert(); i++) {
    Point temp = v.getPointById(i);
    if (temp.getZ() < min) {
      min = temp.getZ();
    }
    if (temp.getZ() > max) {
      max = temp.getZ();
    }
  }
  v.insertMinMaxZ(min, max);
}

void ViewerFacade::normalize() {
  double centre_x = v.getCentreX();
  double centre_y = v.getCentreY();
  double centre_z = v.getCentreZ();

  for (int i = 0; i < v.getAmount_vert(); i++) {
    double tempX = v.getXById(i);
    double tempY = v.getYById(i);
    double tempZ = v.getZById(i);
    tempX -= centre_x;
    tempY -= centre_y;
    tempZ -= centre_z;
    v.changeXYZ(i, tempX, tempY, tempZ);
  }

  // нормализация от -1 до 1
  double x = v.getDiffMinMaxX();
  double y = v.getDiffMinMaxY();
  double z = v.getDiffMinMaxZ();
  double dmax = 0;
  if (x >= y) {
    dmax = x;
  } else {
    dmax = y;
  }
  if (dmax < z) dmax = z;
  double value = 1;
  double scale = (value - value * (-1)) / dmax;
  for (int i = 0; i < v.getAmount_vert(); i++) {
    double tempX = v.getXById(i);
    double tempY = v.getYById(i);
    double tempZ = v.getZById(i);
    tempX *= scale;
    tempY *= scale;
    tempZ *= scale;
    v.changeXYZ(i, tempX, tempY, tempZ);
  }
}

}  // namespace s21
