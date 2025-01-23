#pragma once

#include <controller/executor.hpp>

namespace minsh::controller {

/**
 * \brief The main controller for the shell.
 *
 * This class is responsible for running the shell and managing the executors.
 */
class ShellController final {
  bool running = false;  ///< True if the shell is running, false otherwise.

  std::vector<executor::executor_ptr>
      executors;  ///< The executors for the shell.

 public:
  ShellController() = default;

  ~ShellController() = default;

  /**
   * \brief Runs the shell.
   *
   * This function runs the shell.
   *
   */
  void run();

  /**
   * \brief Determines if the shell is running.
   *
   * This function determines if the shell is running.
   *
   * \return True if the shell is running, false otherwise.
   */
  [[nodiscard]] bool isRunning() const noexcept;

  /**
   * \brief Adds an executor to the shell.
   *
   * This function adds an executor to the shell.
   *
   * \param executor The executor to be added.
   */
  void addExecutor(const executor::executor_ptr& executor);

  /**
   * \brief Executes the given tokens.
   *
   * This function executes the given tokens.
   *
   * \param tokens The tokens to be executed
   *
   * \return The return code of the command.
   */
  [[nodiscard]] int execute(const std::vector<std::string>& tokens) const;

  /**
   * \brief Stops the shell.
   *
   * This function stops the shell.
   *
   */
  void stop();
};

}  // namespace minsh::controller
