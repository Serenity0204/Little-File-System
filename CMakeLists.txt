cmake_minimum_required(VERSION 3.14 FATAL_ERROR) #FetchContent_MakeAvailable
project(Little_File_System)

#. . . . . . . . . . . . . . . . . . . .
include(GNUInstallDirs)
if(MSVC)
    add_compile_options(/W4)
    add_link_options(/W4)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()


# place binaries and libraries according to GNU standards
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})



if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()
#. . . . . . . . . . . . . . . . . . . .

# ------------------------------------
# ------------------------------------
find_package(GTest QUIET)
if (NOT ${GTest_FOUND}) # GTest not found, FetchContent!
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.13.0)
FetchContent_MakeAvailable(googletest)
endif()
    
# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# ------------------------------------



set(SFML_VERSION "2.6.0")

# Declare SFML as an external project
FetchContent_Declare(
  sfml
  URL https://www.sfml-dev.org/files/SFML-${SFML_VERSION}-sources.zip
)

# Build SFML as part of the project
FetchContent_MakeAvailable(sfml)

# Set the C++ standard for SFML
target_compile_features(sfml-graphics PUBLIC cxx_std_11)
target_compile_features(sfml-window PUBLIC cxx_std_11)
target_compile_features(sfml-system PUBLIC cxx_std_11)


#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
#   Grab all cpp files from includes folder
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
set(INCLUDES_FOLDER includes)
FILE(GLOB_RECURSE SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS "${INCLUDES_FOLDER}/*.cpp")
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 



ADD_EXECUTABLE(test_file_folder_io
    _tests/_test_files/test_file_folder_io.cpp
    ${SOURCE_FILES}
)


ADD_EXECUTABLE(main
    main.cpp
    ${SOURCE_FILES}
)

ADD_EXECUTABLE(remove_root_dir
    remove_root_dir.cpp
    ${SOURCE_FILES}
)

ADD_EXECUTABLE(test_parser
    _tests/_test_files/test_parser.cpp
    ${SOURCE_FILES}
)

ADD_EXECUTABLE(test_directory_tree
    _tests/_test_files/test_directory_tree.cpp
    ${SOURCE_FILES}
)




## gtest
TARGET_LINK_LIBRARIES(main GTest::gtest_main)
TARGET_LINK_LIBRARIES(test_file_folder_io GTest::gtest_main)
TARGET_LINK_LIBRARIES(test_parser GTest::gtest_main)
TARGET_LINK_LIBRARIES(test_directory_tree GTest::gtest_main)
TARGET_LINK_LIBRARIES(remove_root_dir GTest::gtest_main)

## sfml
TARGET_LINK_LIBRARIES(main sfml-graphics sfml-window sfml-system)
TARGET_LINK_LIBRARIES(test_file_folder_io sfml-graphics sfml-window sfml-system)
TARGET_LINK_LIBRARIES(test_parser sfml-graphics sfml-window sfml-system)
TARGET_LINK_LIBRARIES(test_directory_tree sfml-graphics sfml-window sfml-system)
TARGET_LINK_LIBRARIES(remove_root_dir sfml-graphics sfml-window sfml-system)

## copy resources file to build
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/bin)





