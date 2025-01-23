#pragma once

#include <controller/executor.hpp>

namespace minsh::executor {

class ExternalExecutor final : public Executor {
 public:
  [[nodiscard]] bool canExecute(
      const std::vector<std::string> &tokens) const override;

  [[nodiscard]] int execute(
      const std::vector<std::string> &tokens) const override;
};

}  // namespace minsh::executor