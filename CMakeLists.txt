#
# Copyright (c) 2019 AT&T Intellectual Property.
# Copyright (c) 2018-2019 Nokia.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

cmake_minimum_required (VERSION 3.5)

file(
  DOWNLOAD https://raw.githubusercontent.com/hunter-packages/gate/master/cmake/HunterGate.cmake
  ${CMAKE_BINARY_DIR}/HunterGate.cmake)

include("${CMAKE_BINARY_DIR}/HunterGate.cmake")

HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.5.tar.gz"
    SHA1 "2c5c6fc1cf609d0856695d60f147594daf4e6b3e"
)

project(tracelibcpp LANGUAGES CXX C)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/cxx1.cmake)

set (tracelibcpp_VERSION_MAJOR "0")
set (tracelibcpp_VERSION_MINOR "0")
set (tracelibcpp_VERSION_MICRO "1")
set (tracelibcpp_VERSION_STRING
    "${tracelibcpp_VERSION_MAJOR}.${tracelibcpp_VERSION_MINOR}.${tracelibcpp_VERSION_MICRO}")

# Add jaeger
hunter_add_package(jaegertracing)
find_package(jaegertracing CONFIG REQUIRED)

# Unit testing support of off by default
# Enable it with cmake -DWITH_TESTING=ON <srcdir>
option(WITH_TESTING "Include using testing support" OFF)

include_directories ("${PROJECT_SOURCE_DIR}/include/tracelibcpp")

add_library(tracelibcpp SHARED
    src/tracelib.cpp
)

option(WITH_VERSION "Support for library versioning" ON)

if (WITH_VERSION)
    set_target_properties(tracelibcpp PROPERTIES VERSION ${tracelibcpp_VERSION_STRING}
                                  SOVERSION ${tracelibcpp_VERSION_MAJOR})
endif (WITH_VERSION)

# Library versions are on by default
# i.e. so versions
option(WITH_VERSION "Support for library versioning" ON)

if (WITH_VERSION)
set_target_properties(tracelibcpp PROPERTIES VERSION ${tracelibcpp_VERSION_STRING}
                                  SOVERSION ${tracelibcpp_VERSION_MAJOR})
endif (WITH_VERSION)

target_link_libraries(tracelibcpp PUBLIC jaegertracing::jaegertracing-static)

include(GNUInstallDirs)
if (NOT DEFINED LIB_INSTALL_DIR)
    set(LIB_INSTALL_DIR lib)
endif()

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/tracelibcpp
        DESTINATION include
        COMPONENT DEVEL)

install(TARGETS tracelibcpp
        COMPONENT DIST
        LIBRARY DESTINATION ${LIB_INSTALL_DIR}
        NAMELINK_SKIP
        )

install(TARGETS tracelibcpp
        COMPONENT DEVEL
        LIBRARY DESTINATION ${LIB_INSTALL_DIR}
        NAMELINK_ONLY
        )

# Add google test
if (WITH_TESTING)
  hunter_add_package(GTest)
  find_package(GTest CONFIG REQUIRED)
  add_executable(testrunner
      tst/testcreate.cpp
  )
  target_link_libraries(testrunner GTest::main) # GTest::gtest will be linked automatically
  target_link_libraries(testrunner GTest::gtest)
  target_link_libraries(testrunner tracelibcpp)
  add_test(UnitTest testrunner)
  add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS testrunner)
  ENABLE_TESTING()
endif (WITH_TESTING)
