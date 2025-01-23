#pragma once

#include <controller/executor.hpp>

namespace minsh::executor {

class ExternalExecutor final : public Executor {
 public:
  /**
   * \brief Checks if the given tokens can be executed using commands provided
   * by the system.
   *
   * This function checks if the given tokens can be executed.
   *
   * \param tokens The tokens to be checked
   * \return True if the tokens can be executed, false otherwise.
   */
  [[nodiscard]] bool canExecute(
      const std::vector<std::string> &tokens) const override;

  /**
   * \brief Executes the given tokens using commands provided by the system.
   *
   * This function executes the given tokens.
   *
   * \param tokens The tokens to be executed
   * \return The return code of the command.
   */
  [[nodiscard]] int execute(
      const std::vector<std::string> &tokens) const override;
};

}  // namespace minsh::executor