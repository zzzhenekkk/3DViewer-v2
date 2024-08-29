#include "test.h"

class AffineTest : public ::testing::Test {
 protected:
  std::vector<float> vertices;

  void SetUp() override {
    // Initialize with some test vertices that can be reused in multiple tests
    vertices = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
  }
};

// Тест нормализации вершин
TEST_F(AffineTest, NormalizeTest) {
  s21::Affine::normalize(vertices);
  EXPECT_NEAR(vertices[0], 1 / SCALE_FACTOR,
              1e-6);  // Ожидается, что длина вектора будет приближена к 1 после
                      // нормализации
}

// Тесты для операций поворота
TEST_F(AffineTest, RotateXTest) {
  float angle = M_PI / 2;  // 90 degrees
  s21::Affine::rotateX(vertices, angle);
  EXPECT_NEAR(vertices[4], 0.0, 1e-6);
  EXPECT_NEAR(vertices[5], -1.0, 1e-6);
  EXPECT_NEAR(vertices[7], 1.0, 1e-6);
}

TEST_F(AffineTest, RotateYTest) {
  float angle = M_PI / 2;  // 90 degrees
  s21::Affine::rotateY(vertices, angle);
  EXPECT_NEAR(vertices[0], 0.0, 1e-6);
  EXPECT_NEAR(vertices[2], -1.0, 1e-6);
  EXPECT_NEAR(vertices[6], 1.0, 1e-6);
}

TEST_F(AffineTest, RotateZTest) {
  float angle = M_PI / 2;  // 90 degrees
  s21::Affine::rotateZ(vertices, angle);
  EXPECT_NEAR(vertices[0], 0.0, 1e-6);
  EXPECT_NEAR(vertices[1], -1.0, 1e-6);
  EXPECT_NEAR(vertices[3], 1.0, 1e-6);
}

// Тест изменения масштаба
TEST_F(AffineTest, ScaleChangeTest) {
  float scale_factor = 2.0;
  s21::Affine::changeScale(vertices, scale_factor);
  EXPECT_FLOAT_EQ(vertices[0], 2.0);  // Проверка изменения масштаба
}

// Тест сдвига вершин
TEST_F(AffineTest, ShiftTest) {
  double shiftX = 1.0, shiftY = 2.0, shiftZ = 3.0;
  s21::Affine::shift(vertices, shiftX, shiftY, shiftZ);
  EXPECT_FLOAT_EQ(
      vertices[0],
      2.0);  // Ожидается, что x-координата первой вершины увеличится на shiftX
  EXPECT_FLOAT_EQ(vertices[1],
                  2.0);  // Ожидается, что y-координата увеличится на shiftY
  EXPECT_FLOAT_EQ(vertices[2],
                  3.0);  // Ожидается, что z-координата увеличится на shiftZ
}

// проверка установки центра
TEST_F(AffineTest, CentrTest) {
  vertices = {1.0, 1.0, 1.0, 2.0, 2.0, 2.0, 3.0, 3.0, 3.0};
  s21::Affine::centralize(vertices);
  std::vector<float> expected_vertices = {-1.0, -1.0, -1.0, 0.0, 0.0,
                                          0.0,  1.0,  1.0,  1.0};
  EXPECT_EQ(vertices, expected_vertices);
}

// проверка считывания объекта из файла
TEST(Parser, CubeModel) {
  std::filesystem::path testFilePath = std::filesystem::absolute(__FILE__);

  std::filesystem::path modelPath =
      testFilePath.parent_path().parent_path().parent_path() / "models" /
      "cube.obj";

  s21::ModelFacade ModelFacade;
  int status = ModelFacade.loadModel(modelPath.string());

  EXPECT_EQ(status, 1);
}

// неправильный путь к файлу
TEST(Parser, WrongPath) {
  std::filesystem::path testFilePath = std::filesystem::absolute(__FILE__);

  std::filesystem::path modelPath =
      testFilePath.parent_path().parent_path().parent_path() / "models" /
      "cubes.obj";

  s21::ModelFacade ModelFacade;
  int status = ModelFacade.loadModel(modelPath.string());

  EXPECT_EQ(status, 0);
}

// неправильный файл
TEST(Parser, BadModel) {
  std::filesystem::path testFilePath = std::filesystem::absolute(__FILE__);

  std::filesystem::path modelPath =
      testFilePath.parent_path().parent_path().parent_path() / "models" /
      "bad_model.obj";

  s21::ModelFacade ModelFacade;
  int status = ModelFacade.loadModel(modelPath.string());

  EXPECT_EQ(status, 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}