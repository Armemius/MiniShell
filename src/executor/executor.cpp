#include <executor/executor.hpp>

#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int minsh::executor::execute(const std::vector<std::string> &tokens) {
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
  } else if (pid < 0) {
    perror("Fork failed");
  } else {
    waitpid(pid, nullptr, 0);
  }

  return 0;
}