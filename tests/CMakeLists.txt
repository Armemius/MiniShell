add_executable(shell_test shell_test.cpp)
target_link_libraries(shell_test PRIVATE gtest_main shell-controller)
add_test(NAME shell_test COMMAND shell_test)

add_executable(parser_test parser_test.cpp)
target_link_libraries(parser_test PRIVATE gtest_main shell-parser)
add_test(NAME parser_test COMMAND parser_test)
