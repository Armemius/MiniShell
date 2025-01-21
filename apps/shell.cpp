#include <iostream>

#include <executor/executor.hpp>
#include <parser/tokenize.hpp>

int main() {

  while (true) {
    std::string input;
    std::cout << "minsh> ";
    std::getline(std::cin, input);

    auto tokens = minsh::parser::tokenize(input);
    minsh::executor::execute(tokens);
  }

  return 0;
}