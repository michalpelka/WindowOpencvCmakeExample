cmake_minimum_required(VERSION 3.28)
project(OpenCVExample LANGUAGES CXX)
if(WIN32)
  # on Windows, download prebuilt OpenCV binaries
  include(3rd_binary/opencv/CMakeLists.txt)
endif()
message(STATUS "OpenCV_DIR: ${OpenCV_DIR}")
find_package(OpenCV REQUIRED)

message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libs: ${OpenCV_LIBS}")

add_executable(opencv_example sample.cpp)

# Link OpenCV libs
target_link_libraries(opencv_example PRIVATE ${OpenCV_LIBS})

# Copy runtime DLLs automatically on Windows
if(WIN32)
  add_custom_command(TARGET opencv_example POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:opencv_example>
            $<TARGET_FILE_DIR:opencv_example>
    COMMAND_EXPAND_LISTS
    COMMENT "Copying runtime dependencies to output directory"
  )
endif()

# Install
install(TARGETS opencv_example RUNTIME DESTINATION .)
install(FILES $<TARGET_RUNTIME_DLLS:opencv_example> DESTINATION .)

# Package
set(CPACK_GENERATOR "ZIP")
include(CPack)
