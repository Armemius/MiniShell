#include <controller/executors/internal.hpp>
#include <iostream>
#include <utility>

static int nullCommand() { return EXIT_SUCCESS; }

static int exitCommand(const std::vector<std::string>&,
                       const minsh::executor::controller_ptr& controller) {
  controller->stop();
  return EXIT_SUCCESS;
}

static int changeDirectoryCommand(const std::vector<std::string>& tokens) {
  if (tokens.size() < 2) {
    std::cerr << "minsh: cd: missing operand" << std::endl;
    return EXIT_FAILURE;
  }

  if (chdir(tokens[1].c_str()) == -1) {
    std::cerr << "minsh: cd: " << tokens[1] << ": No such file or directory"
              << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

static int printWorkingDirectoryCommand() {
  char cwd[1024];
  if (getcwd(cwd, sizeof(cwd)) == nullptr) {
    std::cerr << "minsh: pwd: error getting current working directory"
              << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << cwd << std::endl;
  return EXIT_SUCCESS;
}

minsh::executor::InternalExecutor::InternalExecutor(controller_ptr controller)
    : controller(std::move(controller)) {
  addCommand(":", nullCommand);
  addCommand("exit", exitCommand);
  addCommand("cd", changeDirectoryCommand);
  addCommand("pwd", printWorkingDirectoryCommand);
}

bool minsh::executor::InternalExecutor::canExecute(
    const std::vector<std::string>& tokens) const {
  return commands.contains(tokens[0]);
}

int minsh::executor::InternalExecutor::execute(
    const std::vector<std::string>& tokens) const {
  if (commands.contains(tokens[0])) {
    const auto& cmd = commands.at(tokens[0]);

    if (std::holds_alternative<std::function<int()>>(cmd)) {
      return std::get<std::function<int()>>(cmd)();
    }
    if (std::holds_alternative<
            std::function<int(const std::vector<std::string>&)>>(cmd)) {
      return std::get<std::function<int(const std::vector<std::string>&)>>(cmd)(
          tokens);
    }
    if (std::holds_alternative<std::function<int(
            const std::vector<std::string>&, const controller_ptr&)>>(cmd)) {
      return std::get<std::function<int(const std::vector<std::string>&,
                                        const controller_ptr&)>>(cmd)(
          tokens, controller);
    }
  }

  return EXIT_FAILURE;
}

template <typename T>
void minsh::executor::InternalExecutor::addCommand(const std::string& name,
                                                   T&& fn) {
  commands.emplace(name, std::forward<internal_executor_fn>(fn));
}
