cmake_minimum_required(VERSION 3.10)

project(commitdiff)

aux_source_directory(PARSER_FILES parser)
aux_source_directory(SRC_FILES    src)

add_executable(commitdiff ${PARSER_FILES} ${SRC_FILES})