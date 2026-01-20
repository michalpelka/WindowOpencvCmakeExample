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

# MSVC: sqlite amalgamation is huge
if (MSVC)
  target_compile_options(sqlite3 PRIVATE /bigobj /Zm300)
endif()

# ✅ Canonical target name expected by modern CMake users
add_library(SQLite::SQLite3 ALIAS sqlite3)