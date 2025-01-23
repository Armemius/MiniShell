#pragma once

#include <controller/controller.hpp>
#include <controller/executor.hpp>
#include <functional>
#include <unordered_map>

namespace minsh::executor {

typedef std::shared_ptr<controller::ShellController> controller_ptr;

typedef std::function<int(const std::vector<std::string> &,
                          const controller_ptr &)>
    internal_executor_fn;

template <typename T>
concept InternalExecutorFn = requires(T t) {
  {
    t(std::vector<std::string>{}, controller_ptr{})
  } -> std::convertible_to<int>;
};

class InternalExecutor final : public Executor {
  controller_ptr controller;

  std::unordered_map<std::string, internal_executor_fn> commands;

 public:
  explicit InternalExecutor(controller_ptr controller);

  [[nodiscard]] bool canExecute(
      const std::vector<std::string> &tokens) const override;

  [[nodiscard]] int execute(
      const std::vector<std::string> &tokens) const override;

  template <InternalExecutorFn T>
  void addCommand(const std::string &name, T &&fn);
};

}  // namespace minsh::executor