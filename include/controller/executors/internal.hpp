#pragma once

#include <controller/controller.hpp>
#include <controller/executor.hpp>
#include <functional>
#include <unordered_map>
#include <variant>

namespace minsh::executor {

typedef std::shared_ptr<controller::ShellController> controller_ptr;

typedef std::variant<std::function<int()>,
                     std::function<int(const std::vector<std::string> &)>,
                     std::function<int(const std::vector<std::string> &,
                                       const controller_ptr &)>>
    internal_executor_fn;

template <typename T>
concept InternalExecutorFn =
    (std::is_invocable_v<T> ||
     std::is_invocable_v<T, const std::vector<std::string> &> ||
     std::is_invocable_v<T, const std::vector<std::string> &,
                         const controller_ptr &>)&&requires {
      { std::declval<T>()() } -> std::convertible_to<int>;
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

  template <typename T>
  void addCommand(const std::string &name, T &&fn);
};

}  // namespace minsh::executor