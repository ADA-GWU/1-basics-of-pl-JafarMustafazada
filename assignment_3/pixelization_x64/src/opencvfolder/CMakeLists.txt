
cmake_minimum_required(VERSION 3.15)
project(OpenCV1)

# Add an interface library
add_library(OpenCV1 INTERFACE)
target_include_directories(OpenCV1 INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Glob .lib files for linking
file(GLOB OpenCV_LIB_FILES "${CMAKE_CURRENT_SOURCE_DIR}/lib/*.lib")

# Glob .dll files for runtime
file(GLOB OpenCV_DLL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/bin/*.dll")

# Link all .lib files
target_link_libraries(OpenCV1 INTERFACE "${OpenCV_LIB_FILES}")

# Copy all .dll files
foreach(dll_file IN LISTS OpenCV_DLL_FILES)
    file(COPY "${dll_file}" DESTINATION "${CMAKE_BINARY_DIR}/bin/${CMAKE_CONFIGURATION_TYPES}")
endforeach()
