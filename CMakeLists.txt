cmake_minimum_required(VERSION 3.12)

project(box_raycasting)

set(CMAKE_CXX_STANDARD 23)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Locate OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(main src/main.cpp)
target_link_libraries(main ${OpenCV_LIBS})

# Link unit_tests with what we want to test and the GTest and pthread library
add_executable(unit_tests test/main.cpp test/test_image.cpp ${SOURCES})
target_link_libraries(unit_tests ${GTEST_LIBRARIES} pthread)
