include(FetchContent)
FetchContent(sqlite_amalgamation)
MakeAvailable(sqlite_amalgamation)

add_library(sqlite3 STATIC
  ${sqlite_amalgamation_SOURCE_DIR}/sqlite3.c
)

target_include_directories(sqlite3 PUBLIC
  $<BUILD_INTERFACE:${sqlite_amalgamation_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)

if (MSVC)
  target_compile_options(sqlite3 PRIVATE /bigobj /Zm300)
endif()

add_library(SQLite::SQLite3 ALIAS sqlite3)

install(TARGETS sqlite3
  EXPORT targets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(FILES
  "${sqlite_amalgamation_SOURCE_DIR}/sqlite3.h"
  DESTINATION include
)
