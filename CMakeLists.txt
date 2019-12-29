cmake_minimum_required(VERSION 3.10)

project(analyzer)

aux_source_directory(parser PARSER_FILES)
aux_source_directory(src SRC_FILES)

add_subdirectory(3rdparty/antlr4-cpp-runtime/)

add_executable(${PROJECT_NAME} ${PARSER_FILES} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE
  antlr4_static
  z
  )
target_compile_options(${PROJECT_NAME} PRIVATE -Wno-attributes)
target_include_directories(${PROJECT_NAME} PRIVATE
  /home/zeya/Workspaces/commitdiff/3rdparty/antlr4-cpp-runtime/runtime/src/
  parser/
  )
