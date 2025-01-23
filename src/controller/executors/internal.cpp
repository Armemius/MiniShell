#include <controller/executors/internal.hpp>
#include <utility>

static int colonCommand(const std::vector<std::string>&,
                        const minsh::executor::controller_ptr&) {
  return EXIT_SUCCESS;
}

minsh::executor::InternalExecutor::InternalExecutor(controller_ptr controller)
    : controller(std::move(controller)) {
  addCommand(":", colonCommand);
}

bool minsh::executor::InternalExecutor::canExecute(
    const std::vector<std::string>& tokens) const {
  return commands.contains(tokens[0]);
}

int minsh::executor::InternalExecutor::execute(
    const std::vector<std::string>& tokens) const {
  if (commands.contains(tokens[0])) {
    return commands.at(tokens[0])(tokens, controller);
  }

  return EXIT_FAILURE;
}

template <minsh::executor::InternalExecutorFn T>
void minsh::executor::InternalExecutor::addCommand(const std::string& name,
                                                   T&& fn) {
  commands.emplace(name, std::forward<internal_executor_fn>(fn));
}
