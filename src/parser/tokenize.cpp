#include <parser/tokenize.hpp>

#include <sstream>

std::vector<std::string> minsh::parser::tokenize(const std::string &input) {
  std::vector<std::string> tokens;
  std::istringstream stream(input);
  std::string token;

  while (stream >> token) {
    tokens.push_back(token);
  }

  return tokens;
}