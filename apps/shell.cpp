#include <controller/controller.hpp>
#include <controller/executors/external.hpp>
#include <iostream>
#include <parser/tokenize.hpp>

#include "controller/executors/internal.hpp"

int main() {
  auto controllerPtr = std::make_shared<minsh::controller::ShellController>();
  controllerPtr->addExecutor(
      std::make_shared<minsh::executor::InternalExecutor>(controllerPtr));
  controllerPtr->addExecutor(
      std::make_shared<minsh::executor::ExternalExecutor>());
  controllerPtr->run();

  return 0;
}