#include <controller/controller.hpp>
#include <iostream>
#include <parser/tokenize.hpp>

void minsh::controller::ShellController::run() {
  running = true;
  while (running) {
    std::string input;
    std::cout << "minsh> ";
    std::getline(std::cin, input);

    auto tokens = parser::tokenize(input);
    int code = execute(tokens);
  }
}

void minsh::controller::ShellController::addExecutor(
    const executor::executor_ptr& executor) {
  executors.push_back(executor);
}
int minsh::controller::ShellController::execute(
    const std::vector<std::string>& tokens) const {
  if (tokens.empty()) {
    return EXIT_SUCCESS;
  }

  for (const auto& executor : executors) {
    if (executor->canExecute(tokens)) {
      return executor->execute(tokens);
    }
  }

  std::cerr << "minsh: command not found: " << tokens[0] << std::endl;
  return EXIT_FAILURE;
}

void minsh::controller::ShellController::stop() { running = false; }

bool minsh::controller::ShellController::isRunning() const noexcept {
  return running;
}