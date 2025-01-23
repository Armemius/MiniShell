#include <controller/controller.hpp>
#include <controller/executors/external.hpp>
#include <iostream>
#include <parser/tokenize.hpp>

[[noreturn]] int main() {
  minsh::controller::ShellController controller;
  controller.addExecutor(std::make_shared<minsh::executor::ExternalExecutor>());
  controller.run();

  return 0;
}