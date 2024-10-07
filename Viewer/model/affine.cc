#include "math.h"
#include "model.h"

namespace s21 {

void ViewerFacade::s21_move(double sx, double sy, double sz) {
  for (int i = 0; i < getAmount_vert(); i++) {
    double vector[4] = {v.getXById(i), v.getYById(i), v.getZById(i), 1};
    double transformation_matrix[4][4] = {
        {1, 0, 0, sx}, {0, 1, 0, sy}, {0, 0, 1, sz}, {0, 0, 0, 1}};
    matrix_transformation(transformation_matrix, vector, i);
  }
}

void ViewerFacade::s21_scale(double scale_cur, double scale_prev) {
  if (scale_cur > 0 && scale_prev > 0) {
    for (int i = 0; i < getAmount_vert(); i++) {
      double res[4] = {0};

      res[0] = scale_cur / scale_prev * (v.getXById(i));
      res[1] = scale_cur / scale_prev * (v.getYById(i));
      res[2] = scale_cur / scale_prev * (v.getZById(i));

      v.changeXYZ(i, res[0], res[1], res[2]);
    }
  }
}

void ViewerFacade::s21_rotate(double angle, int x, int y, int z) {
  double radians = angle * PI / 180.0;
  double x_trans_matrix[4][4] = {{1, 0, 0, 0},
                                 {0, cos(radians), -sin(radians), 0},
                                 {0, sin(radians), cos(radians), 0},
                                 {0, 0, 0, 1}};
  double y_trans_matrix[4][4] = {{cos(radians), 0, sin(radians), 0},
                                 {0, 1, 0, 0},
                                 {-sin(radians), 0, cos(radians), 0},
                                 {0, 0, 0, 1}};
  double z_trans_matrix[4][4] = {{cos(radians), -sin(radians), 0, 0},
                                 {sin(radians), cos(radians), 0, 0},
                                 {0, 0, 1, 0},
                                 {0, 0, 0, 1}};
  for (int i = 0; i < getAmount_vert(); i++) {
    double vector[4] = {v.getXById(i), v.getYById(i), v.getZById(i), 1};
    if (x) {
      matrix_transformation(x_trans_matrix, vector, i);
    } else {
      if (y) {
        matrix_transformation(y_trans_matrix, vector, i);
      } else {
        if (z) matrix_transformation(z_trans_matrix, vector, i);
      }
    }
  }
}
void ViewerFacade::matrix_transformation(double transformation_matrix[][4],
                                         double *vector, int i) {
  double res[4] = {0};
  for (int j = 0; j < 4; j++) {
    for (int k = 0; k < 4; k++) {
      res[j] += transformation_matrix[j][k] * vector[k];
    }
  }
  v.changeXYZ(i, res[0], res[1], res[2]);
}
}  // namespace s21
