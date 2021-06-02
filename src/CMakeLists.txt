if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(warnings -Wall -Wextra -Werror -Wno-unused-parameter)
  set(cxx_warnings -Wno-class-memaccess)
  set(no_undefined -Wl,--no-undefined)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(warnings -Wall -Wextra -Werror -Wno-inconsistent-missing-override -Wno-unused-parameter)
  set(cxx_warnings "")
  set(no_undefined -Wl,-undefined,error)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings /W4 /WX /EHsc)
    set(no_undefined "")
    set(cxx_warnings "")
endif()

SET(CXX_STANDARD_REQUIRED OFF)
SET(CXX_EXTENSION NO)

if (NOT CONFIGURED_ONCE)
ADD_COMPILE_OPTIONS(-fPIC -std=c++14 ${warnings} ${cxx_warnings})
ADD_LINK_OPTIONS(${no_undefined})
endif()

ADD_LIBRARY(libarchive STATIC
  libarchive.h libarchive.cpp
  libarchive_internal.h
  libarchive_internal_stream.h libarchive_internal_stream.cpp)

TARGET_INCLUDE_DIRECTORIES(libarchive PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/../third_party/lib7zip/src")

TARGET_INCLUDE_DIRECTORIES(libarchive PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}")

SET_TARGET_PROPERTIES(libarchive PROPERTIES LINKER_LANGUAGE CXX)
