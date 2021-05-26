cmake_minimum_required(VERSION 3.12)


IF (POLICY CMP0078)
CMAKE_POLICY(
    SET CMP0078 NEW
    )
ENDIF()

IF (POLICY CMP0086)
CMAKE_POLICY(
    SET CMP0086 NEW
    )
ENDIF()

project(pylibarchive
  VERSION 1.0.0
  LANGUAGES C CXX)

FIND_PACKAGE(SWIG 4.0 COMPONENTS python)
INCLUDE(UseSWIG)

ADD_SUBDIRECTORY(libzip)
ADD_SUBDIRECTORY(third_party/lib7zip)

swig_add_library(pylibarchive
    TYPE STATIC
    LANGUAGE PYTHON
    SOURCES libzip.i)

