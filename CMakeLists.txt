cmake_minimum_required(VERSION 3.17)
project(Spiral VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)

# Find antlr3config.h path, it's normally under the /usr/local/include.(macOS)
# NOTICE: In normally, the path /usr/local/include will not added to include path on macOS.
#         So if not use the under line, the compilation will fail.
find_path(ANTLR3_CONFIG_INCLUDE_DIR NAMES antlr3config.h)

set(EXECUTABLE_NAME spiral)

set(SOURCES
        ${PROJECT_SOURCE_DIR}/main.cpp
        ${PROJECT_SOURCE_DIR}/ExprCppTreeLexer.c
        ${PROJECT_SOURCE_DIR}/ExprCppTreeParser.c
        )

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(${EXECUTABLE_NAME} ${SOURCES})

target_include_directories(${EXECUTABLE_NAME}
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${ANTLR3_CONFIG_INCLUDE_DIR}
        )

target_link_directories(${EXECUTABLE_NAME}
        PRIVATE
        ${PROJECT_SOURCE_DIR}/libs
        )

target_link_libraries(${EXECUTABLE_NAME}
        PRIVATE
        antlr3c
        )

