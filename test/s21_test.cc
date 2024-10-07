#include <gtest/gtest.h>

#include "../Viewer/model/model.h"

namespace s21 {

TEST(PointTest, test_1) {
  Point p;
  p.insertXYZ(1.0, 2.0, 3.0);

  EXPECT_DOUBLE_EQ(p.getX(), 1.0);
  EXPECT_DOUBLE_EQ(p.getY(), 2.0);
  EXPECT_DOUBLE_EQ(p.getZ(), 3.0);
}

TEST(VertexTest, test_2) {
  Vertex v;
  Point p1, p2;
  p1.insertXYZ(1.0, 2.0, 3.0);
  p2.insertXYZ(4.0, 5.0, 6.0);

  v.pushBackPoint(p1);
  v.pushBackPoint(p2);

  EXPECT_EQ(v.getAmount_vert(), 2);
  EXPECT_DOUBLE_EQ(v.getXById(0), 1.0);
  EXPECT_DOUBLE_EQ(v.getYById(1), 5.0);
}

TEST(VertexTest, test_3) {
  Vertex v;
  v.insertMinMaxX(1.0, 5.0);
  v.insertMinMaxY(2.0, 6.0);
  v.insertMinMaxZ(3.0, 7.0);

  EXPECT_DOUBLE_EQ(v.getDiffMinMaxX(), 4.0);
  EXPECT_DOUBLE_EQ(v.getDiffMinMaxY(), 4.0);
  EXPECT_DOUBLE_EQ(v.getDiffMinMaxZ(), 4.0);
}

TEST(PolygonTest, test_4) {
  Polygon poly;

  poly.insertP(1);
  poly.insertP(2);

  EXPECT_EQ(poly.getSizeById(), 2);
  EXPECT_EQ(poly.getElementById(1), 2);
}

TEST(PolygonTest, test_5) {
  Polygon poly;

  poly.insertP(1);
  poly.clearPolygon();

  EXPECT_EQ(poly.getSizeById(), 0);
}

TEST(ViewerFacadeTest, test_6) {
  ViewerFacade vf;
  int result = SUCCESS;
  std::string path = "./test_file/test.obj";

  vf.main_parcer(path, &result);

  EXPECT_EQ(result, SUCCESS);
}

TEST(ViewerFacadeTest, test_7) {
  ViewerFacade vf;
  int result = SUCCESS;
  std::string path = "./test_file/cessna.obj";

  vf.main_parcer(path, &result);

  EXPECT_EQ(result, SUCCESS);
}

// ошибка в строчке v
TEST(ViewerFacadeTest, test_8) {
  ViewerFacade vf;
  int result = SUCCESS;
  std::string path = "./test_file/error_2.obj";
  vf.main_parcer(path, &result);

  EXPECT_EQ(result, FAILURE);
}

TEST(ViewerFacadeTest, test_9) {
  ViewerFacade vf;
  int result = SUCCESS;
  std::string path = "./test_file/no_test.obj";

  vf.main_parcer(path, &result);

  EXPECT_EQ(result, FAILURE);
}

TEST(ViewerFacadeTest, test_10) {
  ViewerFacade vf;
  int result = SUCCESS;
  std::string path = "./test_file/test_polygon.obj";

  vf.main_parcer(path, &result);

  EXPECT_EQ(result, FAILURE);
}

TEST(ViewerFacadeTest, test_11) {
  ViewerFacade vf;
  int result = SUCCESS;
  std::string path = "./test_file/test.obj";

  vf.main_parcer(path, &result);
  vf.s21_move(1.0, -1.0, 2.0);
  EXPECT_EQ(result, SUCCESS);
  EXPECT_DOUBLE_EQ(vf.getXfromVertexById(0), 1.0);
  EXPECT_DOUBLE_EQ(vf.getYfromVertexById(0), -0.5);
  EXPECT_DOUBLE_EQ(vf.getZfromVertexById(0), 2.0);

  EXPECT_DOUBLE_EQ(vf.getXfromVertexById(1), 0.0);
  EXPECT_DOUBLE_EQ(vf.getYfromVertexById(1), -1.5);
  EXPECT_DOUBLE_EQ(vf.getZfromVertexById(1), 1.0);

  EXPECT_DOUBLE_EQ(vf.getXfromVertexById(2), 2.0);
  EXPECT_DOUBLE_EQ(vf.getYfromVertexById(2), -1.5);
  EXPECT_DOUBLE_EQ(vf.getZfromVertexById(2), 1.0);
}

TEST(ViewerFacadeTest, test_12) {
  ViewerFacade vf;
  int result = SUCCESS;
  std::string path = "./test_file/test.obj";

  vf.main_parcer(path, &result);
  vf.s21_scale(2.0, 1.0);
  EXPECT_EQ(result, SUCCESS);

  EXPECT_DOUBLE_EQ(vf.getXfromVertexById(0), 0.0);
  EXPECT_DOUBLE_EQ(vf.getYfromVertexById(0), 1.0);
  EXPECT_DOUBLE_EQ(vf.getZfromVertexById(0), 0.0);

  EXPECT_DOUBLE_EQ(vf.getXfromVertexById(1), -2.0);
  EXPECT_DOUBLE_EQ(vf.getYfromVertexById(1), -1.0);
  EXPECT_DOUBLE_EQ(vf.getZfromVertexById(1), -2.0);

  EXPECT_DOUBLE_EQ(vf.getXfromVertexById(2), 2.0);
  EXPECT_DOUBLE_EQ(vf.getYfromVertexById(2), -1.0);
  EXPECT_DOUBLE_EQ(vf.getZfromVertexById(2), -2.0);
}

TEST(ViewerFacadeTest, test_13) {
  ViewerFacade vf;
  int result = SUCCESS;
  std::string path = "./test_file/test.obj";

  vf.main_parcer(path, &result);
  vf.s21_rotate(90, 0, 0, 1);
  EXPECT_EQ(result, SUCCESS);

  EXPECT_NEAR(vf.getXfromVertexById(0), -0.5, eps);
  EXPECT_NEAR(vf.getXfromVertexById(1), 0.5, eps);
  EXPECT_NEAR(vf.getYfromVertexById(1), -1, eps);
  EXPECT_NEAR(vf.getXfromVertexById(2), 0.5, eps);
  EXPECT_NEAR(vf.getYfromVertexById(2), 1.0, eps);
}

TEST(ViewerFacadeTest, test_14) {
  ViewerFacade vf;
  int result = SUCCESS;
  std::string path = "./test_file/test.obj";

  vf.main_parcer(path, &result);
  vf.s21_rotate(90, 0, 1, 0);
  EXPECT_EQ(result, SUCCESS);
  EXPECT_NEAR(vf.getXfromVertexById(0), 0.0, eps);
  EXPECT_NEAR(vf.getZfromVertexById(0), 0.0, eps);
  EXPECT_NEAR(vf.getXfromVertexById(1), -1.0, eps);
  EXPECT_NEAR(vf.getZfromVertexById(1), 1.0, eps);
  EXPECT_NEAR(vf.getXfromVertexById(2), -1.0, eps);
  EXPECT_NEAR(vf.getZfromVertexById(2), -1.0, eps);
}

TEST(ViewerFacadeTest, test_15) {
  ViewerFacade vf;
  int result = SUCCESS;
  std::string path = "./test_file/test.obj";

  vf.main_parcer(path, &result);
  vf.s21_rotate(90, 1, 0, 0);
  EXPECT_EQ(result, SUCCESS);

  EXPECT_NEAR(vf.getYfromVertexById(0), 0.0, eps);
  EXPECT_NEAR(vf.getZfromVertexById(0), 0.5, eps);
  EXPECT_NEAR(vf.getYfromVertexById(1), 1.0, eps);
  EXPECT_NEAR(vf.getZfromVertexById(1), -0.5, eps);
  EXPECT_NEAR(vf.getYfromVertexById(2), 1.0, eps);
  EXPECT_NEAR(vf.getZfromVertexById(2), -0.5, eps);
}

TEST(ViewerFacadeTest, test_16) {
  ViewerFacade vf;
  int result = SUCCESS;
  std::string path = "./test_file/error_1.obj";

  vf.main_parcer(path, &result);

  EXPECT_EQ(result, FAILURE);
}

TEST(ViewerFacadeTest, test_17) {
  ViewerFacade vf;
  int result = SUCCESS;
  std::string path = "./test_file/cessna.obj";

  vf.main_parcer(path, &result);
  EXPECT_EQ(result, SUCCESS);

  EXPECT_EQ(vf.getAmount_polygons(), 3897);
}

TEST(ViewerFacadeTest, test_18) {
  ViewerFacade vf;
  int result = SUCCESS;
  std::string path = "./test_file/cessna.obj";

  vf.main_parcer(path, &result);
  EXPECT_EQ(result, SUCCESS);

  EXPECT_EQ(vf.getSizeOfPolygonById(1), 4);
}

TEST(ViewerFacadeTest, test_19) {
  ViewerFacade vf;
  int result = SUCCESS;
  std::string path = "./test_file/cessna.obj";

  vf.main_parcer(path, &result);
  EXPECT_EQ(result, SUCCESS);

  EXPECT_EQ(vf.getElementOfPolygonById(0, 0), 3);
}
TEST(ViewerFacadeTest, test_20) {
  ViewerFacade vf;
  int result = SUCCESS;
  std::string path = "./test_file/cessna.obj";

  vf.main_parcer(path, &result);
  path = "./test_file/test.obj";

  vf.main_parcer(path, &result);

  EXPECT_EQ(result, SUCCESS);
}
}  // namespace s21

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
