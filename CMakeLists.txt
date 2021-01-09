cmake_minimum_required(VERSION 3.0.0)
project(SimpleRSS VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

find_package(wxWidgets REQUIRED COMPONENTS core base gl xml net adv)
include(${wxWidgets_USE_FILE})

find_package(Asio REQUIRED)
include_directories(${ASIO_INCLUDE_DIR})

find_package(RapidXML REQUIRED)
include_directories(${RAPIDXML_INCLUDE_DIR})

add_subdirectory(src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
