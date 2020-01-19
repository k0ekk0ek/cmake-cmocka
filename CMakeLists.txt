cmake_minimum_required(VERSION 3.7)
project(
  cmake-cmocka
  LANGUAGES C
  VERSION 0.0.1
  DESCRIPTION "Simple project to demonstrate cmake-cmocka")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")

find_package(cmocka REQUIRED)
cmocka_add_tests(cmocka-test example.c)
