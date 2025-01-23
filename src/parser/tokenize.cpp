#include <algorithm>
#include <iostream>
#include <parser/tokenize.hpp>
#include <regex>

std::vector<std::string> minsh::parser::tokenize(const std::string &input) {
  std::vector<std::string> tokens;
  const std::regex token_regex(
      R"((\"(?:\\.|[^\"])*\"|\'(?:\\.|[^\'])*\'|\S+))");
  const auto words_begin =
      std::sregex_iterator(input.begin(), input.end(), token_regex);
  const auto words_end = std::sregex_iterator();

  for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
    std::string token = i->str();

    if (token.front() == '\"' && token.back() == '\"' ||
        token.front() == '\'' && token.back() == '\'') {
      token = token.substr(1, token.size() - 2);
    }
    token = std::regex_replace(token, std::regex(R"(\\\\)"), "\\");
    token = std::regex_replace(token, std::regex(R"(\\\")"), "\"");
    token = std::regex_replace(token, std::regex(R"(\\\')"), "\'");

    tokens.push_back(token);
  }

  return tokens;
}