cmake_minimum_required(VERSION 3.28)
project(OpenCVExample LANGUAGES CXX C)
if(WIN32)
  # on Windows, download prebuilt OpenCV binaries
  include(3rd_binary/opencv/CMakeLists.txt)
endif()
message(STATUS "OpenCV_DIR: ${OpenCV_DIR}")
find_package(OpenCV REQUIRED)

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "" FORCE)

## Sqlite, both precompiled tools and library for PROJ
if(WIN32)
  # on Windows, download prebuilt SqlLite binaries - Proj needs sqlite3.exe for some operations during compulation,
  # we cannot build it from source, since it requires to be avialable at configuration time / compilation time.
  include(3rd_binary/sqlite_tools/CMakeLists.txt)

  # On Windows - Proj needs SQLite library as well - those are built from source
  include(3rd/sqlite/CMakeLists.txt)
endif()

# Proj
if (MSVC)
  add_compile_options(/bigobj /Zm300)
endif()

set(ENABLE_TIFF OFF CACHE BOOL "" FORCE)
set(ENABLE_CURL OFF CACHE BOOL "" FORCE)
set(BUILD_PROJSYNC OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
add_subdirectory(3rd/proj)
include_directories(3rd/proj/src)
include_directories(3rd/proj/include)


message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libs: ${OpenCV_LIBS}")

add_executable(opencv_example sample.cpp)

# Link OpenCV libs
target_link_libraries(opencv_example PRIVATE ${OpenCV_LIBS})

add_executable(proj_example proj_example.cpp)
target_link_libraries(proj_example PRIVATE  PROJ::proj)



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
