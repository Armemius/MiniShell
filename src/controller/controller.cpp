#include <chrono>
#include <controller/controller.hpp>
#include <iostream>
#include <optional>
#include <parser/tokenize.hpp>

#include "fmt/compile.h"

std::string formatTime(const double duration) {
  constexpr double NS_THRESHOLD = 1e-6;
  constexpr double US_THRESHOLD = 1e-3;
  constexpr double MS_THRESHOLD = 1;
  constexpr double M_THRESHOLD = 60;
  constexpr double H_THRESHOLD = 60 * M_THRESHOLD;
  constexpr double D_THRESHOLD = 24 * H_THRESHOLD;

  if (duration < NS_THRESHOLD) {
    return fmt::format("{}ns", static_cast<int>(duration * 1e9));
  }
  if (duration < US_THRESHOLD) {
    return fmt::format("{}us", static_cast<int>(duration * 1e6));
  }
  if (duration < MS_THRESHOLD) {
    return fmt::format("{}ms", static_cast<int>(duration * 1e3));
  }
  if (duration > D_THRESHOLD) {
    return fmt::format("{}D {}", static_cast<int>(duration / D_THRESHOLD),
                       formatTime(std::fmod(duration, D_THRESHOLD)));
  }
  if (duration > H_THRESHOLD) {
    return fmt::format("{}H {}", static_cast<int>(duration / H_THRESHOLD),
                       formatTime(std::fmod(duration, H_THRESHOLD)));
  }
  if (duration > M_THRESHOLD) {
    return fmt::format("{}m {}", static_cast<int>(duration / M_THRESHOLD),
                       formatTime(std::fmod(duration, M_THRESHOLD)));
  }
  return fmt::format("{}s", static_cast<int>(duration));
}

void minsh::controller::ShellController::run() {
  running = true;
  std::optional<double> prev_time = std::nullopt;
  int prev_code = EXIT_SUCCESS;

  while (running) {
    if (char cwd[1024]; getcwd(cwd, sizeof(cwd)) != nullptr) {
      std::cout << "\033[0;36m" << cwd << "\033[0m";
      if (prev_time.has_value()) {
        std::cout << " took \033[0;33m" << formatTime(prev_time.value())
                  << "\033[0m";
      }
    }
    if (prev_code != EXIT_SUCCESS) {
      std::cout << std::endl << "\033[0;31m$\033[0m ";
    } else {
      std::cout << std::endl << "\033[0;32m$\033[0m ";
    }

    std::string input;

    if (!std::getline(std::cin, input)) {
      stop();
      break;
    }

    auto tokens = parser::tokenize(input);

    const auto start_time = std::chrono::high_resolution_clock::now();

    prev_code = execute(tokens);

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