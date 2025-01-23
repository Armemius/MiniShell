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

/**
 * \brief Executor for internal commands.
 *
 * This class defines an executor for internal commands.
 *
 */
class InternalExecutor final : public Executor {
  controller_ptr controller;  ///< The controller for the shell.

  std::unordered_map<std::string, internal_executor_fn>
      commands;  ///< The commands.

 public:
  /**
   * \brief Constructs an InternalExecutor.
   *
   * This function constructs an InternalExecutor.
   *
   * \param controller The controller for the shell.
   */
  explicit InternalExecutor(controller_ptr controller);

  /**
   * \brief Checks if the given tokens can be executed using internal commands.
   *
   * This function checks if the given tokens can be executed.
   *
   * \param tokens The tokens to be checked
   * \return True if the tokens can be executed, false otherwise.
   */
  [[nodiscard]] bool canExecute(
      const std::vector<std::string> &tokens) const override;

  /**
   * \brief Executes the given tokens using internal commands.
   *
   * This function executes the given tokens.
   *
   * \param tokens The tokens to be executed
   * \return The return code of the command.
   */
  [[nodiscard]] int execute(
      const std::vector<std::string> &tokens) const override;

  /**
   * \brief Adds a command to the executor.
   *
   * This function adds a command to the executor.
   *
   * \param name The name of the command.
   * \param fn The function to be executed.
   */
  template <typename T>
  void addCommand(const std::string &name, T &&fn);
};

}  // namespace minsh::executor