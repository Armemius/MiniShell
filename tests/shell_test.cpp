#include <gtest/gtest.h>

#include <controller/controller.hpp>
#include <controller/executors/external.hpp>
#include <controller/executors/internal.hpp>

TEST(ShellTest, TestEmpty) {
  const auto controllerPtr =
      std::make_shared<minsh::controller::ShellController>();

  int code = controllerPtr->execute({});
  EXPECT_EQ(code, EXIT_FAILURE);

  code = controllerPtr->execute({""});
  EXPECT_EQ(code, EXIT_FAILURE);
}

TEST(ShellTest, TestInternal) {
  const auto controllerPtr =
      std::make_shared<minsh::controller::ShellController>();

  controllerPtr->addExecutor(
      std::make_shared<minsh::executor::InternalExecutor>(controllerPtr));

  int code = controllerPtr->execute({"cd"});
  EXPECT_EQ(code, EXIT_FAILURE);

  code = controllerPtr->execute({"cd", "nonexistent"});
  EXPECT_EQ(code, EXIT_FAILURE);

  code = controllerPtr->execute({"cd", "/tmp"});
  EXPECT_EQ(code, EXIT_SUCCESS);

  code = controllerPtr->execute({"cd", "/nonexistent"});
  EXPECT_EQ(code, EXIT_FAILURE);

  code = controllerPtr->execute({"cd", "/tmp"});
  EXPECT_EQ(code, EXIT_SUCCESS);

  code = controllerPtr->execute({"cd", "/tmp"});
  EXPECT_EQ(code, EXIT_SUCCESS);

  code = controllerPtr->execute({"cd", "/nonexistent"});
  EXPECT_EQ(code, EXIT_FAILURE);

  code = controllerPtr->execute({"cd", "/tmp"});
  EXPECT_EQ(code, EXIT_SUCCESS);

  code = controllerPtr->execute({"cd", "/tmp"});
  EXPECT_EQ(code, EXIT_SUCCESS);

  code = controllerPtr->execute({"cd", "/nonexistent"});
  EXPECT_EQ(code, EXIT_FAILURE);

  code = controllerPtr->execute({"cd", "/tmp"});
  EXPECT_EQ(code, EXIT_SUCCESS);

  code = controllerPtr->execute({"cd", "/tmp"});
  EXPECT_EQ(code, EXIT_SUCCESS);

  code = controllerPtr->execute({"cd", "/nonexistent"});
  EXPECT_EQ(code, EXIT_FAILURE);

  code = controllerPtr->execute({"cd", "/tmp"});
  EXPECT_EQ(code, EXIT_SUCCESS);

  code = controllerPtr->execute({"cd", "/tmp"});
  EXPECT_EQ(code, EXIT_SUCCESS);

  code = controllerPtr->execute({"cd", "/nonexistent"});
  EXPECT_EQ(code, EXIT_FAILURE);

  code = controllerPtr->execute({"cd", "/tmp"});
  EXPECT_EQ(code, EXIT_SUCCESS);

  code = controllerPtr->execute({"cd", "/tmp"});
  EXPECT_EQ(code, EXIT_SUCCESS);

  code = controllerPtr->execute({"cd", "/nonexistent"});
  EXPECT_EQ(code, EXIT_FAILURE);

  code = controllerPtr->execute({"cd", "/tmp"});
  EXPECT_EQ(code, EXIT_SUCCESS);

  code = controllerPtr->execute({"cd", "/tmp"});
  EXPECT_EQ(code, EXIT_SUCCESS);

  code = controllerPtr->execute({"cd", "/tmp", "/tmp"});
  EXPECT_EQ(code, EXIT_FAILURE);

  code = controllerPtr->execute({":"});
  EXPECT_EQ(code, EXIT_SUCCESS);

  code = controllerPtr->execute({":", ":"});
  EXPECT_EQ(code, EXIT_SUCCESS);

  code = controllerPtr->execute({":", "some sample text bla bla"});
  EXPECT_EQ(code, EXIT_SUCCESS);

  code = controllerPtr->execute({":", "cd"});
  EXPECT_EQ(code, EXIT_SUCCESS);

  code = controllerPtr->execute({"pwd"});
  EXPECT_EQ(code, EXIT_SUCCESS);

  code = controllerPtr->execute({"pwd", "bla bla"});
  EXPECT_EQ(code, EXIT_FAILURE);
}

TEST(ShellTest, TestExternal) {
  const auto controllerPtr =
      std::make_shared<minsh::controller::ShellController>();

  controllerPtr->addExecutor(
      std::make_shared<minsh::executor::ExternalExecutor>());

  int code = controllerPtr->execute({"ls"});
  EXPECT_EQ(code, EXIT_SUCCESS);

  code = controllerPtr->execute({"ls", "-l"});
  EXPECT_EQ(code, EXIT_SUCCESS);

  code = controllerPtr->execute({"some nonexistent cmd", "-l", "-a"});
  EXPECT_NE(code, EXIT_SUCCESS);
}
