cmake_minimum_required(VERSION 3.10.1)
project("slit")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set (SSEQ_TIDY_CHECK OFF CACHE BOOL "Enable clang-tidy checks")
set (SSEQ_USE_COTIRE OFF CACHE BOOL "Enable phc build")
set (SSEQ_BENCHMARKS OFF CACHE BOOL "Enable benchmarks")

if (SSEQ_USE_COTIRE)
  include(cotire)
else()
  macro(cotire name)
  endmacro()
endif()

if (SSEQ_BENCHMARKS)
  include ("${CMAKE_SOURCE_DIR}/cmake/external/GoogleBenchmarks.cmake")
endif()

string (APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,\
signed-integer-overflow,shift,bool,bounds,vptr,integer-divide-by-zero,\
float-cast-overflow,float-divide-by-zero,enum")
string (APPEND CMAKE_CXX_FLAGS_DEBUG " -O0")
string (APPEND CMAKE_CXX_FLAGS_DEBUG " -ggdb3")
string (APPEND CMAKE_CXX_FLAGS " -std=c++1z")
string (APPEND CMAKE_CXX_FLAGS " -fno-omit-frame-pointer")
string (APPEND CMAKE_CXX_FLAGS " -Wall -Wextra -pedantic \
-Wsign-conversion -Wold-style-cast \
-Wno-c++98-c++11-compat -Wno-c++98-compat -Wno-c++98-compat-pedantic \
-Wno-padded -Wno-shadow -Wno-exit-time-destructors -Wno-global-constructors")
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  string (APPEND CMAKE_CXX_FLAGS " -fcolor-diagnostics")
  string (APPEND CMAKE_CXX_FLAGS " -Wextra-semi -Weverything -Wshorten-64-to-32")
  string (APPEND CMAKE_CXX_FLAGS_DEBUG " -fno-limit-debug-info")
else()
  message(STATUS "Not compiling with clang, disabling colored diagnostics")
endif()

if (SSEQ_TIDY_CHECK)
  set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*,\
  -google-readability-namespace-comments,-llvm-include-order,\
  -llvm-namespace-comment,-cppcoreguidelines-pro-bounds-*,\
  -clang-diagnostic-unused-command-line-argument")
endif()

#add_subdirectory(lib)
#add_subdirectory(test)
add_subdirectory(tools)
if (SSEQ_BENCHMARKS)
  add_subdirectory(benchmark)
endif()


set (DOXYGEN_EXCLUDE_PATTERNS ${CMAKE_BINARY_DIR}/tests/catch.hpp)
cmake_policy(SET CMP0057 NEW)
find_package(Doxygen OPTIONAL_COMPONENTS dot mscgen dia)
if(DOXYGEN_FOUND)
  doxygen_add_docs(doxygen ${CMAKE_SOURCE_DIR} "Generate doxygen")
endif(DOXYGEN_FOUND)

