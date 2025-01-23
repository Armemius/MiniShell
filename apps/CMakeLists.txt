add_executable(msh shell.cpp)
target_link_libraries(msh PRIVATE shell-parser shell-controller)