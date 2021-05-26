cmake_minimum_required(VERSION 3.16 )
project(entcosy VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
SET(CMAKE_CXX_FLAGS "-Wno-error=implicit-fallthrough -Wno-error=class-memaccess -Wno-error=catch-value -Wno-error=unused-variable")


# load 3rdparty library
set(THIRDPARTY_DIR ${CMAKE_CURRENT_LIST_DIR}/3rdparty)
include(FetchContent)
set(CEREAL_DIR "${THIRDPARTY_DIR}/cereal")
set(RTTR_DIR "${THIRDPARTY_DIR}/rttr")

FetchContent_Declare(
    cereal
    SOURCE_DIR ${CEREAL_DIR}
)
FetchContent_Declare(
    rttr
    SOURCE_DIR ${RTTR_DIR}
)
SET(BUILD_UNIT_TESTS OFF CACHE INTERNAL "cached for turn off unit tests")
SET(BUILD_INSTALLER OFF CACHE INTERNAL "cached for turn off installer")
SET(BUILD_PACKAGE OFF CACHE INTERNAL "cached for turn off package")
SET(BUILD_EXAMPLES OFF CACHE INTERNAL "cached for turn off package")
SET(BUILD_DOCUMENTATION OFF CACHE INTERNAL "cached for add subdir")
SET(BUILD_STATIC ON CACHE INTERNAL "cached for build static lib")
SET(JUST_INSTALL_CEREAL ON CACHE INTERNAL "cached for build cereal only")
FetchContent_MakeAvailable(cereal rttr)

FetchContent_GetProperties(rttr)
message("halo halo bandung ${rttr_BINARY_DIR}")

set(SRC_DIR src)
add_library(entcosy INTERFACE)
target_include_directories(entcosy INTERFACE 
    ${CMAKE_CURRENT_LIST_DIR}/${SRC_DIR}
    ${CEREAL_DIR}/include
    ${CEREAL_DIR}/include/cereal/external
    ${RTTR_DIR}/src
    ${RTTR_DIR}/3rd_party/catch-1.12.0
    ${RTTR_DIR}/3rd_party/nonius-1.1.2
    ${RTTR_DIR}/3rd_party/rapidjson-1.1.0
    ${rttr_BINARY_DIR}/src
)
target_link_libraries(entcosy INTERFACE cereal rttr_core)
set_property(TARGET entcosy PROPERTY CXX_STANDARD 17)

set(EXAMPLE_DIR ${SRC_DIR}/example)
add_executable(example ${EXAMPLE_DIR}/main.cpp)
target_link_libraries(example PUBLIC entcosy)