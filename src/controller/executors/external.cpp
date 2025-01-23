#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <controller/executors/external.hpp>
#include <cstdlib>

#include "fmt/compile.h"

int minsh::executor::ExternalExecutor::execute(
    const std::vector<std::string> &tokens) const {
  if (tokens.empty()) {
    return 0;
  }

  std::vector<char *> argv;
  for (const auto &arg : tokens) {
    argv.push_back(const_cast<char *>(arg.c_str()));
  }
  argv.push_back(nullptr);

  pid_t pid = fork();
  if (pid == 0) {
    if (execvp(argv[0], argv.data()) == -1) {
      perror("Error executing command");
    }
    exit(EXIT_FAILURE);
  }
  if (pid < 0) {
    perror("Fork failed");
  } else {
    waitpid(pid, nullptr, 0);
  }

  return 0;
}

bool minsh::executor::ExternalExecutor::canExecute(
    const std::vector<std::string> &tokens) const {
  if (tokens.empty()) {
    return false;
  }

  if (access(tokens[0].c_str(), X_OK) == 0) {
    return true;
  }

  const char *path = getenv("PATH");
  if (!path) {
    return false;
  }

  const std::string &command = tokens[0];
  std::string pathStr = path;
  size_t pos = 0;
  while ((pos = pathStr.find(':')) != std::string::npos) {
    std::string dir = pathStr.substr(0, pos);
    std::string fullPath = fmt::format("{}/{}", dir, command);
    if (access(fullPath.c_str(), X_OK) == 0) {
      return true;
    }
    pathStr.erase(0, pos + 1);
  }

  const std::string fullPath = fmt::format("{}/{}", pathStr, command);
  return access(fullPath.c_str(), X_OK) == 0;
}