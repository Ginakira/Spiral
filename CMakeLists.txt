cmake_minimum_required(VERSION 3.17)
project(Spiral VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)

# Find antlr3config.h path, it's normally under the /usr/local/include.(macOS)
# NOTICE: In normally, the path /usr/local/include will not added to include path on macOS.
#         So if not use the under line, the compilation will fail.
find_path(ANTLR3_CONFIG_INCLUDE_DIR NAMES antlr3config.h)

set(EXECUTABLE_NAME spiral)

set(GRAMMAR_NAME Spiral)

set(GRAMMAR_FILES
        ${PROJECT_SOURCE_DIR}/third-party/${GRAMMAR_NAME}Lexer.c
        ${PROJECT_SOURCE_DIR}/third-party/${GRAMMAR_NAME}Parser.c
        )

set(SOURCES
        ${GRAMMAR_FILES}
        src/main.cpp
        src/spiral_type.cc
        src/spiral_parameter.cc
        src/spiral_tree.cc
        src/spiral_runtime.cc
        src/spiral_master.cc
        src/spiral_factory.cc
        src/spiral_visitor.cc
        src/spiral_handler.cc
        )

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(${EXECUTABLE_NAME} ${SOURCES})

target_include_directories(${EXECUTABLE_NAME}
        PRIVATE
        include
        third-party
        include/antlr
        ${ANTLR3_CONFIG_INCLUDE_DIR}
        )

target_link_directories(${EXECUTABLE_NAME}
        PRIVATE
        libs
        )

target_link_libraries(${EXECUTABLE_NAME}
        PRIVATE
        antlr3c
        )

# Generate antlr3 grammar file
add_custom_command(
        OUTPUT ${GRAMMAR_FILES}
        COMMAND java -jar ./antlr-3.4-complete.jar Spiral.g
        DEPENDS ${PROJECT_SOURCE_DIR}/third-party/Spiral.g
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/third-party
)