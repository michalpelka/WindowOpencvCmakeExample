cmake_minimum_required(VERSION 3.28)
project(OpenCVExample LANGUAGES CXX C)
if(WIN32)
  # on Windows, download prebuilt OpenCV binaries
  include(3rd_binary/opencv/CMakeLists.txt)
endif()
message(STATUS "OpenCV_DIR: ${OpenCV_DIR}")
find_package(OpenCV REQUIRED)

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "" FORCE)

## Proj + SQLite tools
#if(WIN32)
  # on Windows, download prebuilt SqlLite binaries - Proj needs sqlite3.exe for some operations
  include(3rd_binary/sqlite_tools/CMakeLists.txt)

  # On Windows - Proj needs SQLite library as well - those are built from source
  include(3rd/sqlite/CMakeLists.txt)

#endif()
add_subdirectory(3rd/proj)


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
