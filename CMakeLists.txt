cmake_minimum_required(VERSION 3.19)

if(DEFINED ENV{GITHUB_RUN_NUMBER})
    project(bulk VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
else()
    project(bulk)
endif()

set(CMAKE_CXX_STANDARD 20)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/source
)

file(GLOB SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/source/*.cpp"
        "${PROJECT_SOURCE_DIR}/*.cpp"
        )

add_executable(bulk ${SRCS} include/Observable.h)

install(TARGETS bulk RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT timoshenkonas@gmail.com)
include(CPack)

enable_testing()
add_subdirectory(test)