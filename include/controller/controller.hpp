#pragma once

#include <controller/executor.hpp>

namespace minsh::controller {

class ShellController final {
  bool running = false;

  std::vector<executor::executor_ptr> executors;

 public:
  ShellController() = default;

  ~ShellController() = default;

  void run();

  [[nodiscard]] bool isRunning() const noexcept;

  void addExecutor(const executor::executor_ptr& executor);

  [[nodiscard]] int execute(const std::vector<std::string>& tokens) const;

  void stop();
};

}  // namespace minsh::controller
