#include <chrono>
#include <controller/controller.hpp>
#include <iostream>
#include <optional>
#include <parser/tokenize.hpp>

void minsh::controller::ShellController::run() {
  running = true;
  std::optional<double> prev_time = std::nullopt;

  while (running) {
    if (char cwd[1024]; getcwd(cwd, sizeof(cwd)) != nullptr) {
      std::cout << "\033[0;36m" << cwd << "\033[0m";
      if (prev_time.has_value()) {
        std::cout << " took \033[0;33m" << prev_time.value() << "\033[0ms";
      }
      std::cout << std::endl << "\033[0;31m$\033[0m " << std::flush;
    } else {
      std::cout << "\033[0;31mminsh>\033[0m ";
      break;
    }

    std::string input;

    if (!std::getline(std::cin, input)) {
      stop();
      break;
    }

    auto tokens = parser::tokenize(input);
    if (tokens.empty()) {
      continue;
    }

    const auto start_time = std::chrono::high_resolution_clock::now();

    if (int code = execute(tokens); code != EXIT_SUCCESS) {
      std::cerr << "minsh: command failed with code " << code << std::endl;
    }

    const auto end_time = std::chrono::high_resolution_clock::now();

    prev_time = std::chrono::duration<double>(end_time - start_time).count();

    std::cout << std::endl;
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