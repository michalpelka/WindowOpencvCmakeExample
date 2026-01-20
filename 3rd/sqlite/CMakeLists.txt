include(FetchContent)

set(SQLITE_VERSION "3460100") # 3.46.1
set(SQLITE_YEAR "2024")

FetchContent_Declare(sqlite_amalgamation
  URL "https://www.sqlite.org/${SQLITE_YEAR}/sqlite-amalgamation-${SQLITE_VERSION}.zip"
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(sqlite_amalgamation)

add_library(sqlite3 STATIC
  ${sqlite_amalgamation_SOURCE_DIR}/sqlite3.c
)

target_include_directories(sqlite3 PUBLIC
  ${sqlite_amalgamation_SOURCE_DIR}
)

if (MSVC)
  target_compile_options(sqlite3 PRIVATE /bigobj /Zm300)
endif()

set(SQLite3_INCLUDE_DIR
    "${sqlite_amalgamation_SOURCE_DIR}"
    CACHE PATH "SQLite3 include dir"
    FORCE
)

set(SQLite3_LIBRARY
    "$<TARGET_FILE:sqlite3>"
    CACHE FILEPATH "SQLite3 library file"
    FORCE
)

add_library(SQLite::SQLite3 ALIAS sqlite3)
