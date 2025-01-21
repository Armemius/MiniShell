macro(add_shell_library lib_name dir)
  file(GLOB_RECURSE ${lib_name}_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/${dir}/*.hpp")
  file(GLOB_RECURSE ${lib_name}_LIB_SRC CONFIGURE_DEPENDS "${dir}/*.cpp")
  add_library(${lib_name} ${${lib_name}_LIB_SRC} ${${lib_name}_HEADER_LIST})
  target_include_directories(${lib_name} PUBLIC "${PROJECT_SOURCE_DIR}/include")
endmacro()

add_shell_library(shell-parser parser)
add_shell_library(shell-executor executor)
