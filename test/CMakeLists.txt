set(Boost_USE_STATIC_LIBS OFF)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

include_directories(${Boost_INCLUDE_DIR})
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/source
)

file(GLOB SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/source/*.cpp"
        "./*.cpp"
        )

add_executable(test_bulk ${SRCS})
target_link_libraries(test_bulk ${Boost_LIBRARIES})

add_test(test_bulk test_bulk)