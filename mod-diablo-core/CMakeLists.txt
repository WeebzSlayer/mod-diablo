# Get the name of the current directory (mod-diablo-core)
get_filename_component(MOD_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Add the include directory to the path
set(DIABLO_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Collect all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create the module
add_library(modules-mod-diablo-core INTERFACE)

# Link the sources to the module
target_sources(modules-mod-diablo-core INTERFACE ${SOURCES})

# Include the headers
target_include_directories(modules-mod-diablo-core INTERFACE ${DIABLO_INCLUDE_DIR})

# Link the module to the AzerothCore hooks
target_link_libraries(modules-mod-diablo-core INTERFACE azerothcore-scripts)

# Install the configuration file
if (NOT EXISTS "${CMAKE_BINARY_DIR}/configs/diablo.conf")
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/conf/diablo.conf.dist"
        "${CMAKE_BINARY_DIR}/configs/diablo.conf"
        COPYONLY
    )
endif()

# Register the module within the AzerothCore build system
message("  -> Module: ${MOD_NAME} (Diablo Core System) loaded")