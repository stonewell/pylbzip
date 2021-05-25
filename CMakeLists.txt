cmake_minimum_required(VERSION 3.8)

project(pylibzip
  VERSION 1.0.0
  LANGUAGES C)

FIND_PACKAGE(SWIG 4.0 COMPONENTS python)
INCLUDE(UseSWIG)

ADD_SUBDIRECTORY(libzip)

swig_add_library(pylibzip
    TYPE STATIC
    LANGUAGE PYTHON
    SOURCES libzip.i)

