// пасрер будет реализован с помощью утилитного паттерна
#include "parser.h"

#include <clocale>
#include <sstream>

namespace s21 {

void Parser::parse(std::string path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error("Unable to open the file: " + path);
  }
  std::string line;
  // int i =0;

  while (getline(file, line)) {
    const char* c_line = line.c_str();
    if (strncmp(c_line, "v ", 2) == 0) {
      parseV(c_line);
    }
    if (strncmp(c_line, "f ", 2) == 0) {
      parseF(c_line);
    }
    // ++i;
  }
}

void Parser::parseF(const std::string& line) {
  Model& model = Model::getInstance();
  std::vector<unsigned int> vectorPoligon;
  std::istringstream iss(line);
  std::string prefix;
  std::string vertexIndex;

  iss >> prefix;  // Считываем и игнорируем префикс 'f'

  while (iss >> vertexIndex) {
    size_t pos =
        vertexIndex.find('/');  // Находим позицию первого слеша, если есть
    int index = std::stoi(
        vertexIndex.substr(0, pos));  // Преобразуем подстроку до слеша в число

    vectorPoligon.push_back(index);
  }

  if (iss.fail() && !iss.eof()) {
    throw std::invalid_argument("No correct polygon");
  }
  model.addPolygon(vectorPoligon);
}

void Parser::parseV(const char* c_line) {
  Model& model = Model::getInstance();
  float a = 0, b = 0, c = 0;
  if (sscanf(c_line, "v %f %f %f", &a, &b, &c) == 3) {
    model.addVertex(a, b, c);
  } else {
    throw std::runtime_error("No correct vertexes");
  }
}

}  // namespace s21
