#include <controller/executors/external.hpp>
#include <iostream>
#include <parser/tokenize.hpp>

[[noreturn]] int main() {
  while (true) {
    std::string input;
    std::cout << "minsh> ";
    std::getline(std::cin, input);

    auto tokens = minsh::parser::tokenize(input);
    auto externalExecutor = minsh::executor::ExternalExecutor();

    externalExecutor.execute(tokens);
  }

  return 0;
}