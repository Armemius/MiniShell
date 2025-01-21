add_executable(shell_test shell_test.cpp)
target_link_libraries(shell_test PRIVATE gtest_main)
add_test(NAME shell_test COMMAND shell_test)
