cmake_minimum_required(VERSION 3.12)

project(box_raycasting)

set(CMAKE_CXX_STANDARD 23)

set(SOURCES src/io.cpp
            src/raycast.cpp
)
set(TESTS test/test_image.cpp
)

find_package(GTest REQUIRED)
find_package(OpenCV REQUIRED)
find_package (Eigen3 3.4 REQUIRED NO_MODULE)
include_directories(${GTEST_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

add_executable(main src/main.cpp ${SOURCES})
target_link_libraries(main ${OpenCV_LIBS} Eigen3::Eigen)

# Link unit_tests with what we want to test and the GTest and pthread library
add_executable(unit_tests test/main.cpp ${SOURCES} ${TESTS})
target_link_libraries(unit_tests ${OpenCV_LIBS} Eigen3::Eigen ${GTEST_LIBRARIES} pthread)
