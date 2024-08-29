#ifndef PARSER_H
#define PARSER_H

#include <string.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../model.h"

namespace s21 {

/**
 * @brief Класс для парсинга файлов моделей.
 *
 * Этот класс предоставляет статический метод для парсинга файлов моделей,
 * содержащих информацию о полигонах и вершинах.
 */
class Parser {
 public:
  friend class ParserTest;
  /**
   * @brief Конструктор класса Parser запрещен.
   */
  Parser() = delete;

  /**
   * @brief Парсит файл модели по указанному пути.
   *
   * @param path Путь к файлу модели.
   */
  static void parse(std::string path);

 private:
  /**
   * @brief Конструктор копирования класса Parser запрещен.
   */
  Parser(const Parser &) = delete;

  /**
   * @brief Оператор присваивания класса Parser запрещен.
   */
  Parser &operator=(const Parser &) = delete;

  /**
   * @brief Парсит строку, содержащую информацию о полигонах.
   *
   * @param line Строка с информацией о полигонах.
   */
  static void parseF(const std::string &line);

  /**
   * @brief Парсит строку, содержащую информацию о вершинах.
   *
   * @param c_line Строка с информацией о вершинах.
   */
  static void parseV(const char *c_line);
};

}  // namespace s21
#endif
