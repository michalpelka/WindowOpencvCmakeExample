include(FetchContent)

# Pick a specific SQLite release (reproducible builds!)
set(SQLITE_VERSION "3460100") # = 3.46.1 (example)
set(SQLITE_ZIP "sqlite-amalgamation-${SQLITE_VERSION}.zip")

FetchContent_Declare(sqlite_amalgamation
  URL      https://www.sqlite.org/2024/${SQLITE_ZIP}
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(sqlite_amalgamation)

# sqlite_amalgamation_SOURCE_DIR will contain sqlite3.c + sqlite3.h
add_library(sqlite3 STATIC
  ${sqlite_amalgamation_SOURCE_DIR}/sqlite3.c
)

target_include_directories(sqlite3 PUBLIC
  ${sqlite_amalgamation_SOURCE_DIR}
)

add_library(sqlite3::sqlite3 ALIAS sqlite3)
