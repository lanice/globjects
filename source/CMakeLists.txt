# Generate meta-header
configure_file(globjects-version.h.in ${CMAKE_CURRENT_BINARY_DIR}/globjects-version.h)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Libraries
set(IDE_FOLDER "")
add_subdirectory(globjects)

# Examples
set(IDE_FOLDER "Examples")

if (NOT OPTION_GLES_BINDING)
    add_subdirectory(examples)
endif ()

# Tests
set(IDE_FOLDER "Tests")
if (NOT OPTION_GLES_BINDING)
    add_subdirectory(tests)
endif()
