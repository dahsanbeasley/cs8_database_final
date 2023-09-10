project(barkeshli_s21 CXX)

# CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# ------------------------------------
# place binaries and libraries according to GNU standards
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()
#. . . . . . . . . . . . . . . . . . . .
include(cmake/googletest.cmake)
fetch_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_BINARY_DIR}/googletest
    )



# ------------------------------------------------------------------------------------------
#                                    DO NOT EDIT 
#                               ANYTHING ABOVE THIS LINE
# ------------------------------------------------------------------------------------------


# ADD_SUBDIRECTORY(googletest)

ADD_EXECUTABLE(main
    main.cpp
    includes/token/token.cpp
    includes/tokenizer/state_machine_functions.cpp
    includes/tokenizer/stokenize.cpp
    includes/tokenizer/ftokenize.cpp
)

ADD_EXECUTABLE(basic_test
    _tests/_test_files/basic_test.cpp
    includes/token/token.cpp
    includes/tokenizer/state_machine_functions.cpp
    includes/token/child_tokens.cpp
    includes/tokenizer/stokenize.cpp
    includes/binary_files/utilities.cpp
    includes/binary_files/file_record.cpp
    includes/table/table.cpp
    includes/shunting_yard/shunting_yard.cpp
    includes/rpn/rpn.cpp
    includes/parser/parser.cpp
    includes/sql/sql.cpp
)

ADD_EXECUTABLE(testB
    _tests/_test_files/testB.cpp
    includes/token/token.cpp
    includes/tokenizer/state_machine_functions.cpp
    includes/token/child_tokens.cpp
    includes/tokenizer/stokenize.cpp
    includes/binary_files/utilities.cpp
    includes/binary_files/file_record.cpp
    includes/table/table.cpp
    includes/shunting_yard/shunting_yard.cpp
    includes/rpn/rpn.cpp
    includes/parser/parser.cpp
    includes/sql/sql.cpp
)

TARGET_LINK_LIBRARIES(basic_test gtest)
TARGET_LINK_LIBRARIES(testB gtest)

