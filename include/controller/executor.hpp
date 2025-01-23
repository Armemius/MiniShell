#pragma once

#include <string>
#include <vector>

namespace minsh::executor {

class Executor {
 public:
  Executor() = default;

  virtual ~Executor() = default;

  [[nodiscard]] virtual bool canExecute(
      const std::vector<std::string> &tokens) const = 0;

  [[nodiscard]] virtual int execute(
      const std::vector<std::string> &tokens) const = 0;
};

}  // namespace minsh::executor