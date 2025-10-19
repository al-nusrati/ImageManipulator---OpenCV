cmake_minimum_required(VERSION 3.10)
project(ImageManipulator)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Add executable
add_executable(ImageManipulator 
    main.cpp 
    ImageManipulator.cpp
)

# Link OpenCV libraries
target_link_libraries(ImageManipulator ${OpenCV_LIBS})

# Print OpenCV information
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")