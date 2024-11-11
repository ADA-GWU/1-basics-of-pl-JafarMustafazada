cmake_minimum_required (VERSION 3.10)
project (pixelation1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Specify include directories
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

# Specify source files
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(pixelation1 ${MY_SOURCES})


# Specify output directories (optional)
set_target_properties(pixelation1 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    OUTPUT_NAME "pixelation1"
)


### external cmake ##################################################################################
add_subdirectory ("src/opencvfolder")


### external library ################################################################################
target_link_libraries(pixelation1 PRIVATE OpenCV1)

