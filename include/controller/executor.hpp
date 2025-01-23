#pragma once

#include <memory>
#include <string>
#include <vector>

namespace minsh::executor {

/**
 * \brief Interface for classes that execute commands.
 *
 * This class defines the interface for classes that execute commands.
 *
 */
class Executor {
 public:
  Executor() = default;

  virtual ~Executor() = default;

  /**
   * \brief Determines if the executor can execute the given tokens.
   *
   * This function determines if the executor can execute the given tokens.
   *
   * \param tokens The tokens to be executed
   * \return True if the executor can execute the tokens, false otherwise.
   */
  [[nodiscard]] virtual bool canExecute(
      const std::vector<std::string> &tokens) const = 0;

  /**
   * \brief Executes the given tokens.
   *
   * This function executes the given tokens.
   *
   * \param tokens The tokens to be executed
   * \return The return code of the command.
   */
  [[nodiscard]] virtual int execute(
      const std::vector<std::string> &tokens) const = 0;
};

typedef std::shared_ptr<Executor> executor_ptr;

}  // namespace minsh::executor